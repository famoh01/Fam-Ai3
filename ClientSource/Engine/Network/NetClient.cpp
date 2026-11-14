#include <StdH.h>

#if		(_MSC_VER > 1200)

#include "NetClient.h"
#pragma push_macro("O")
#pragma push_macro("Q")
#pragma push_macro("D")
#pragma push_macro("W")
#pragma push_macro("B")
#undef O
#undef Q
#undef D
#undef W
#undef B
#include <boost/array.hpp>
#pragma pop_macro("B")
#pragma pop_macro("W")
#pragma pop_macro("D")
#pragma pop_macro("Q")
#pragma pop_macro("O")
#include <Engine/Network/NetworkMessage.h>
#include <Engine/Util.h>
#include <Engine/Network/CNetwork.h>

#define		BUFF_SIZE		10240

CNetSocket::CNetSocket(lc_asio_io_service& io)
	: _bConnect(false)
	, _socket(io)
{
}

CNetSocket::~CNetSocket()
{
	if (isValid() == true)
		_socket.close();
}

bool CNetSocket::isValid()
{
	if (!_socket.is_open() && _bConnect)   // 커넥트 된 이후 소켓이 닫혀버렸다면
	{
		_bConnect = false;					// 커넥트도 끊김 판정
		return false;
	}

	return true;
}

bool CNetSocket::connect( std::string& IP, std::string& port )
{
	boost::system::error_code error = boost::asio::error::host_not_found;
#if BOOST_VERSION >= 106600
	boost::asio::ip::tcp::resolver resolver(_socket.get_executor());
	boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(IP, port, error);
	if (!error)
	{
		_socket.close();
		boost::asio::connect(_socket, endpoints, error);
	}
#else
	boost::asio::ip::tcp::resolver resolver(_socket.get_io_service());
	boost::asio::ip::tcp::resolver::query query(IP, port);
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query, error);
	boost::asio::ip::tcp::resolver::iterator end;
	while (error && endpoint_iterator != end)
	{
		_socket.close();
		_socket.connect(*endpoint_iterator++, error);
	}
#endif
	if (error)
	{
		_bConnect = false;
		return false;
	}
	_bConnect = true;
	return true;
}

void CNetSocket::send(CNetworkMessage &nmMessage)
{
	if (isValid() == false)
		return;

	_pNetwork->Encrypt(nmMessage);

	CPacket packet;

	packet.WriteToPacket((void*)nmMessage.GetBuffer(), nmMessage.nm_slSize, 0, 0, 0, nmMessage.nm_slSize);

	extern CCommunicationInterface _cmiComm;

	_cmiComm.attachCRC(&packet);

	boost::system::error_code error;
	int len = boost::asio::write(_socket, boost::asio::buffer((void*)packet.pa_pubPacketData, packet.pa_slSize + sizeof(int)), error);
}

void CNetSocket::recv()
{
	if (isValid() == false)
		return;

	while(true)
	{
		// 읽어올 데이터를 저장할 array를 만든다.
		boost::array<char, BUFF_SIZE> buf;
		boost::system::error_code error;
		// read_some함수를 호출해 128만큼의 버퍼에 채워달라고 요청한다.
		// ( len <=128 일것이다. )
		size_t len = _socket.read_some(boost::asio::buffer(buf), error);

		break;
	}
}

//-----------------------------------------------------------------

CNetClient::CNetClient()
	: _pSock(NULL)
{

}

CNetClient::~CNetClient()
{
	SAFE_DELETE(_pSock);
}

bool CNetClient::init(std::string& ip, std::string& port)
{
	_pSock = new CNetSocket(_io_service);
	
	return _pSock->connect(ip, port);
}

void CNetClient::send( CNetworkMessage& nmMessage )
{
	if (_pSock == NULL)
		return;

	_pSock->send(nmMessage);
}

void CNetClient::recv()
{
	if (_pSock == NULL)
		return;

	_pSock->recv();
}

#endif	// (_MSC_VER > 1200)

