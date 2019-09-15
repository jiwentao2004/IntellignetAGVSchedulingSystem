#include "TCP_IPBase.h"

TCP_IPBase::TCP_IPBase()
{
	m_socket = INVALID_SOCKET;
}

TCP_IPBase::~TCP_IPBase()
{
	CloseSocket();
}

sockaddr TCP_IPBase::GetLocalAddress()
{
	return GetLocalAddress(m_socket);
}

sockaddr TCP_IPBase::GetPeerAddress()
{
	return GetPeerAddress(m_socket);
}

sockaddr TCP_IPBase::GetLocalAddress(const SOCKET& sock)
{
	sockaddr addr;
	int addrlen = 0;
	if (getpeername(sock, &addr, &addrlen) == -1)
	{
		return addr;
	}

	return sockaddr();
}

sockaddr TCP_IPBase::GetPeerAddress(const SOCKET& sock)
{
	sockaddr addr;
	int addrlen = 0;
	if (getpeername(sock, &addr, &addrlen) == -1)
	{
		return addr;
	}

	return sockaddr();
}

bool TCP_IPBase::InitWSA()
{
	// 初始化套接字
	WORD sockVersion = MAKEWORD(2, 2);

	WSADATA datawsa;

	// WSAStartup异步套接字启动函数
	if (WSAStartup(sockVersion, &datawsa) != 0)
	{
		WSACleanup();

		return false;
	}

	return true;
}

SOCKET TCP_IPBase::CreateSocket(const ADDRESS_FAMILY sfamily)
{
	if (InitWSA() == false)
	{
		return INVALID_SOCKET;
	}

	SOCKET sock = INVALID_SOCKET;

	// 创建套接字
	sock = socket(sfamily, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
	{
		WSACleanup();

		return INVALID_SOCKET;
	}

	return sock;
}

bool TCP_IPBase::BindSocket(SOCKET& sock, const sockaddr& addr)
{
	// 绑定套接字
	if (bind(sock, &addr, sizeof(addr)) == SOCKET_ERROR)
	{
		WSACleanup();

		shutdown(sock, SD_BOTH);
		closesocket(sock);

		sock = INVALID_SOCKET;

		return false;
	}

	return true;
}

void TCP_IPBase::CloseSocket()
{
	return CloseSocket(m_socket);
}

void TCP_IPBase::CloseSocket(SOCKET& sock)
{
	if (sock != INVALID_SOCKET)
	{
		shutdown(sock, SD_BOTH);
		closesocket(sock);

		sock = INVALID_SOCKET;
	}

	return;
}
