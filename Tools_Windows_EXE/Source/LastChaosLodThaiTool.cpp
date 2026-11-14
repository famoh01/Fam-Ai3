// LastChaosLodThaiTool.cpp
// Converts UTF-8 Thai TSV <-> CP874 (TIS-620) Last Chaos String .lod files
// Compatible with Engine/Help/Loader.cpp & Engine/Interface/UIManager.cpp::LoadStringData

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>
#include <sstream>

// Convert UTF-8 string (including Thai U+0E01..U+0E5B) -> Windows-874 / TIS-620 bytes
std::string utf8_to_cp874(const std::string& utf8) {
    std::string out;
    out.reserve(utf8.size());
    size_t i = 0;
    while (i < utf8.size()) {
        uint8_t c = static_cast<uint8_t>(utf8[i]);
        if (c < 0x80) {
            out.push_back(static_cast<char>(c));
            i += 1;
        } else if ((c & 0xE0) == 0xC0 && i + 1 < utf8.size()) {
            uint32_t cp = ((c & 0x1F) << 6) | (static_cast<uint8_t>(utf8[i + 1]) & 0x3F);
            if (cp == 0x00A0) out.push_back(' ');
            else out.push_back('?');
            i += 2;
        } else if ((c & 0xF0) == 0xE0 && i + 2 < utf8.size()) {
            uint32_t cp = ((c & 0x0F) << 12) |
                          ((static_cast<uint8_t>(utf8[i + 1]) & 0x3F) << 6) |
                          (static_cast<uint8_t>(utf8[i + 2]) & 0x3F);
            if (cp >= 0x0E01 && cp <= 0x0E3A) {
                out.push_back(static_cast<char>((cp - 0x0E00) + 0xA0));
            } else if (cp >= 0x0E3F && cp <= 0x0E5B) {
                out.push_back(static_cast<char>((cp - 0x0E00) + 0xA0));
            } else if (cp == 0x2013 || cp == 0x2014) {
                out.push_back('-');
            } else if (cp == 0x2018 || cp == 0x2019) {
                out.push_back('\'');
            } else if (cp == 0x201C || cp == 0x201D) {
                out.push_back('"');
            } else if (cp == 0x2026) {
                out += "...";
            } else {
                out.push_back('?');
            }
            i += 3;
        } else if ((c & 0xF8) == 0xF0 && i + 3 < utf8.size()) {
            out.push_back('?');
            i += 4;
        } else {
            out.push_back(static_cast<char>(c));
            i += 1;
        }
    }
    return out;
}

// Convert Windows-874 / TIS-620 bytes -> UTF-8 string
std::string cp874_to_utf8(const std::string& cp874) {
    std::string out;
    out.reserve(cp874.size() * 3);
    for (size_t i = 0; i < cp874.size(); ++i) {
        uint8_t b = static_cast<uint8_t>(cp874[i]);
        if (b < 0x80) {
            if (b == '\t') out += "\\t";
            else if (b == '\n') out += "\\n";
            else if (b == '\r') continue;
            else out.push_back(static_cast<char>(b));
        } else if ((b >= 0xA1 && b <= 0xDA) || (b >= 0xDF && b <= 0xFB)) {
            uint32_t cp = 0x0E00 + (b - 0xA0);
            out.push_back(static_cast<char>(0xE0 | ((cp >> 12) & 0x0F)));
            out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
            out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
        } else {
            out.push_back('?');
        }
    }
    return out;
}

std::string unescape_tsv(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            if (s[i + 1] == 'n') { out.push_back('\n'); ++i; continue; }
            if (s[i + 1] == 't') { out.push_back('\t'); ++i; continue; }
        }
        out.push_back(s[i]);
    }
    return out;
}

struct Row {
    int32_t idx;
    std::vector<std::string> cols;
};

bool compile_tsv_to_lod(const char* inTsv, const char* outLod, int strCnt) {
    FILE* fin = fopen(inTsv, "rb");
    if (!fin) return false;

    std::vector<Row> rows;
    int32_t maxIdx = 0;
    char lineBuf[16384];
    bool firstLine = true;
    while (fgets(lineBuf, sizeof(lineBuf), fin)) {
        std::string line(lineBuf);
        if (firstLine && line.size() >= 3 &&
            (uint8_t)line[0] == 0xEF && (uint8_t)line[1] == 0xBB && (uint8_t)line[2] == 0xBF) {
            line = line.substr(3);
        }
        firstLine = false;
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
        if (line.empty() || line[0] == '#') continue;

        std::vector<std::string> parts;
        size_t start = 0;
        while (true) {
            size_t tab = line.find('\t', start);
            if (tab == std::string::npos) {
                parts.push_back(line.substr(start));
                break;
            }
            parts.push_back(line.substr(start, tab - start));
            start = tab + 1;
        }
        if (parts.empty()) continue;
        Row r;
        r.idx = atoi(parts[0].c_str());
        if (r.idx > maxIdx) maxIdx = r.idx;
        for (int c = 0; c < strCnt; ++c) {
            std::string utf8Col = (c + 1 < (int)parts.size()) ? unescape_tsv(parts[c + 1]) : " ";
            std::string cp874 = utf8_to_cp874(utf8Col);
            if (cp874.empty()) cp874 = " ";
            r.cols.push_back(cp874);
        }
        rows.push_back(r);
    }
    fclose(fin);

    FILE* fout = fopen(outLod, "wb");
    if (!fout) return false;

    int32_t nRow = static_cast<int32_t>(rows.size());
    int32_t nMax = maxIdx;
    fwrite(&nRow, sizeof(int32_t), 1, fout);
    fwrite(&nMax, sizeof(int32_t), 1, fout);

    for (size_t i = 0; i < rows.size(); ++i) {
        fwrite(&rows[i].idx, sizeof(int32_t), 1, fout);
        for (int c = 0; c < strCnt; ++c) {
            int32_t len = static_cast<int32_t>(rows[i].cols[c].size());
            fwrite(&len, sizeof(int32_t), 1, fout);
            if (len > 0) {
                fwrite(rows[i].cols[c].data(), len, 1, fout);
            }
        }
    }
    fclose(fout);
    printf("[OK] Compiled %d Thai strings (MaxIndex=%d, Columns=%d) -> %s\n", nRow, nMax, strCnt, outLod);
    return true;
}

bool export_lod_to_tsv(const char* inLod, const char* outTsv, int strCnt) {
    FILE* fin = fopen(inLod, "rb");
    if (!fin) return false;
    int32_t nRow = 0, nMax = 0;
    if (fread(&nRow, sizeof(int32_t), 1, fin) != 1 || fread(&nMax, sizeof(int32_t), 1, fin) != 1) {
        fclose(fin);
        return false;
    }

    FILE* fout = fopen(outTsv, "wb");
    if (!fout) { fclose(fin); return false; }
    // Write UTF-8 BOM so Windows Notepad / Excel opens Thai text cleanly
    const uint8_t bom[3] = {0xEF, 0xBB, 0xBF};
    fwrite(bom, 1, 3, fout);
    fprintf(fout, "# Last Chaos Thai .lod String Table (UTF-8 TSV -> CP874/TIS-620)\r\n");

    std::vector<char> buff(16384);
    for (int32_t i = 0; i < nRow; ++i) {
        int32_t idx = 0;
        if (fread(&idx, sizeof(int32_t), 1, fin) != 1) break;
        fprintf(fout, "%d", idx);
        for (int c = 0; c < strCnt; ++c) {
            int32_t len = 0;
            if (fread(&len, sizeof(int32_t), 1, fin) != 1) break;
            std::string col;
            if (len > 0 && len < 16000) {
                fread(buff.data(), len, 1, fin);
                col.assign(buff.data(), len);
            }
            std::string utf8 = cp874_to_utf8(col);
            fprintf(fout, "\t%s", utf8.c_str());
        }
        fprintf(fout, "\r\n");
    }
    fclose(fout);
    fclose(fin);
    printf("[OK] Exported %d strings (MaxIndex=%d) from %s -> %s\n", nRow, nMax, inLod, outTsv);
    return true;
}

int main(int argc, char** argv) {
    printf("==================================================================\n");
    printf("  Last Chaos Thailand - .lod String Compiler (UTF-8 <-> CP874 TH)\n");
    printf("==================================================================\n");
    if (argc >= 4 && strcmp(argv[1], "--compile") == 0) {
        int cols = (argc >= 5) ? atoi(argv[4]) : 1;
        return compile_tsv_to_lod(argv[2], argv[3], cols) ? 0 : 1;
    }
    if (argc >= 4 && strcmp(argv[1], "--export") == 0) {
        int cols = (argc >= 5) ? atoi(argv[4]) : 1;
        return export_lod_to_tsv(argv[2], argv[3], cols) ? 0 : 1;
    }
    printf("Usage:\n");
    printf("  LastChaosLodThaiTool.exe --compile strClient_th_utf8.tsv strClient_th.lod [columns=1]\n");
    printf("  LastChaosLodThaiTool.exe --export  strClient_th.lod strClient_th_utf8.tsv [columns=1]\n");
    printf("Column counts: strClient=1, strItem=2, strNPCName=2, strSkill=3, strQuest=4\n");
    return 0;
}
