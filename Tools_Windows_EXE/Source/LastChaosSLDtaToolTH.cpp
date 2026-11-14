// LastChaosSLDtaToolTH.cpp
// Exact binary encoder & decoder for Last Chaos Bin/sl.dta
// Matches Engine/Network/CommunicationInterface.cpp lines 2235-2275 byte-for-byte.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>

struct ServerEntry {
    std::string name;
    std::string ip;
    std::string port;
    std::string fullUsers;
    std::string busyUsers;
};

bool encode_sldta(const char* outPath, const std::vector<ServerEntry>& servers) {
    FILE* fp = fopen(outPath, "wb");
    if (!fp) return false;

    // 6-byte header read by: for (i = 0; i < 6; i++) fread(&key, 1, 1, fp);
    const uint8_t hdr[6] = {'L', 'C', 'T', 'H', 'A', 'I'};
    fwrite(hdr, 1, 6, fp);

    int32_t iKey = 0x13572468;
    uint8_t key = 0x5A;
    fwrite(&iKey, sizeof(int32_t), 1, fp);
    fwrite(&key, 1, 1, fp);

    int32_t serverNum = static_cast<int32_t>(servers.size());
    int32_t encServerNum = serverNum + iKey;
    fwrite(&encServerNum, sizeof(int32_t), 1, fp);
    iKey = encServerNum;

    for (size_t i = 0; i < servers.size(); ++i) {
        char buf[256];
        snprintf(buf, sizeof(buf), "%s %s %s %s %s",
                 servers[i].name.c_str(),
                 servers[i].ip.c_str(),
                 servers[i].port.c_str(),
                 servers[i].fullUsers.c_str(),
                 servers[i].busyUsers.c_str());

        int32_t count = static_cast<int32_t>(strlen(buf));
        int32_t encCount = count + iKey;
        fwrite(&encCount, sizeof(int32_t), 1, fp);
        iKey = encCount;

        for (int32_t idx = 0; idx < count; ++idx) {
            uint8_t plain = static_cast<uint8_t>(buf[idx]);
            uint8_t data = static_cast<uint8_t>((plain + key) & 0xFF);
            fwrite(&data, 1, 1, fp);
            key = data;
        }
    }

    fclose(fp);
    return true;
}

bool decode_sldta(const char* inPath, std::vector<ServerEntry>& outServers) {
    FILE* fp = fopen(inPath, "rb");
    if (!fp) return false;

    uint8_t key = 0;
    for (int i = 0; i < 6; ++i) {
        if (fread(&key, 1, 1, fp) != 1) { fclose(fp); return false; }
    }
    int32_t iKey = 0, iKeyTemp = 0, serverNum = 0;
    if (fread(&iKey, sizeof(int32_t), 1, fp) != 1) { fclose(fp); return false; }
    if (fread(&key, 1, 1, fp) != 1) { fclose(fp); return false; }
    if (fread(&serverNum, sizeof(int32_t), 1, fp) != 1) { fclose(fp); return false; }

    iKeyTemp = serverNum;
    serverNum -= iKey;
    iKey = iKeyTemp;

    if (serverNum < 0 || serverNum > 100) { fclose(fp); return false; }

    for (int i = 0; i < serverNum; ++i) {
        int32_t count = 0;
        if (fread(&count, sizeof(int32_t), 1, fp) != 1) { fclose(fp); return false; }
        iKeyTemp = count;
        count -= iKey;
        iKey = iKeyTemp;
        if (count <= 0 || count >= 255) { fclose(fp); return false; }

        char buf[256];
        for (int idx = 0; idx < count; ++idx) {
            uint8_t data = 0;
            if (fread(&data, 1, 1, fp) != 1) { fclose(fp); return false; }
            buf[idx] = static_cast<char>(data - key);
            key = data;
        }
        buf[count] = '\0';

        char sName[64] = {}, sAddr[64] = {}, sPort[32] = {}, sFull[32] = {}, sBusy[32] = {};
        sscanf(buf, "%63s %63s %31s %31s %31s", sName, sAddr, sPort, sFull, sBusy);
        outServers.push_back({sName, sAddr, sPort, sFull, sBusy});
    }

    fclose(fp);
    return true;
}

int main(int argc, char** argv) {
    printf("============================================================\n");
    printf("  Last Chaos Thailand - sl.dta Server List Encryptor/Decryptor\n");
    printf("============================================================\n");

    if (argc >= 3 && strcmp(argv[1], "--decode") == 0) {
        std::vector<ServerEntry> list;
        if (!decode_sldta(argv[2], list)) {
            printf("[ERROR] Failed to decode %s\n", argv[2]);
            return 1;
        }
        printf("[OK] Decoded %zu server(s) from %s:\n", list.size(), argv[2]);
        for (size_t i = 0; i < list.size(); ++i) {
            printf("  #%zu: Name=%s  IP=%s  Port=%s  Full=%s  Busy=%s\n",
                   i + 1, list[i].name.c_str(), list[i].ip.c_str(),
                   list[i].port.c_str(), list[i].fullUsers.c_str(), list[i].busyUsers.c_str());
        }
        return 0;
    }

    if (argc >= 6 && strcmp(argv[1], "--encode") == 0) {
        const char* outPath = argv[2];
        ServerEntry e;
        e.name = argv[3];
        e.ip = argv[4];
        e.port = argv[5];
        e.fullUsers = (argc >= 7) ? argv[6] : "200";
        e.busyUsers = (argc >= 8) ? argv[7] : "150";
        if (!encode_sldta(outPath, {e})) {
            printf("[ERROR] Cannot write %s\n", outPath);
            return 1;
        }
        printf("[OK] Generated %s -> %s (%s:%s)\n", outPath, e.name.c_str(), e.ip.c_str(), e.port.c_str());
        return 0;
    }

    // Interactive mode when double-clicked on Windows
    char ip[64] = "127.0.0.1";
    char port[32] = "4001";
    char name[64] = "LastChaos_TH";
    printf("\nUsage:\n");
    printf("  LastChaosSLDtaToolTH.exe --encode sl.dta LastChaos_TH 127.0.0.1 4001 200 150\n");
    printf("  LastChaosSLDtaToolTH.exe --decode sl.dta\n\n");
    printf("Interactive Mode - Enter Server IP [default 127.0.0.1]: ");
    char line[128];
    if (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) > 0) strncpy(ip, line, sizeof(ip) - 1);
    }
    printf("Enter Login Port [default 4001]: ");
    if (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) > 0) strncpy(port, line, sizeof(port) - 1);
    }
    if (encode_sldta("sl.dta", {{name, ip, port, "200", "150"}})) {
        printf("\n[SUCCESS] Created sl.dta (%s -> %s:%s)! Copy sl.dta to your game Bin\\ folder.\n", name, ip, port);
    }
    printf("Press Enter to exit...");
    fgets(line, sizeof(line), stdin);
    return 0;
}
