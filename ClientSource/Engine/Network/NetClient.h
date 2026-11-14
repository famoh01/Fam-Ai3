#ifndef NET_CLIENT_H_
#define NET_CLIENT_H_

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
#include <boost/version.hpp>
#include <boost/asio.hpp>
#pragma pop_macro("B")
#pragma pop_macro("W")
#pragma pop_macro("D")
#pragma pop_macro("Q")
#pragma pop_macro("O")

#if BOOST_VERSION >= 106600
typedef boost::asio::io_context lc_asio_io_service;
#else
typedef boost::asio::io_service lc_asio_io_service;
#endif

class CNetSocket
{
public:
	CNetSocket(lc_asio_io_service& io);
	~CNetSocket();

	bool	isValid();

	bool	connect(std::string& IP, std::string& port);
	void	send(CNetworkMessage &nmMessage);
	void	recv();

private:
	boost::asio::ip::tcp::socket	_socket;
	bool	_bConnect;
};

class CNetClient
{
public:
	CNetClient();
	~CNetClient();

	bool init(std::string& ip, std::string& port);
	void send(CNetworkMessage& nmMessage);
	void recv();

	lc_asio_io_service& get_service()		{ return _io_service; }

private:
	lc_asio_io_service	_io_service;
	CNetSocket* _pSock;
};

#endif		// NET_CLIENT_H_
