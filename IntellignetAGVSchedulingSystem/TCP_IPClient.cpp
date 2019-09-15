#include "TCP_IPClient.h"

TCP_IPClient::TCP_IPClient()
{
	m_sockTmp = INVALID_SOCKET;
	m_sockaddrSrv = sockaddr();
	m_sockaddrClnt = sockaddr();
}

TCP_IPClient::~TCP_IPClient()
{
}

inline bool TCP_IPClient::Connect(const sockaddr& clienaddr, const sockaddr& srvaddr)
{
	m_sockTmp = CreateSocket();

	if (m_sockTmp == INVALID_SOCKET)
	{
		return false;
	}

	if (BindSocket(m_sockTmp, clienaddr) == false)
	{
		return false;
	}

	return ConnectServer(srvaddr);
}

inline bool TCP_IPClient::Connect(const sockaddr& srvaddr)
{
	m_sockTmp = CreateSocket();

	if (m_sockTmp == INVALID_SOCKET)
	{
		return false;
	}

	return  ConnectServer(srvaddr);
}

bool TCP_IPClient::ConnectServer(const sockaddr& srvaddr)
{
	// 连接服务器
	if (connect(m_socket, & srvaddr, sizeof(srvaddr)) == SOCKET_ERROR)
	{
		WSACleanup();

		CloseSocket(m_sockTmp);

		return false;
	}

	m_socket = m_sockTmp;

	return true;
}

bool TCP_IPClient::ConnectClient(const sockaddr& clntaddr)
{
	// 匹配协议类型
	if (m_sockaddrSrv.sa_family != clntaddr.sa_family)
	{
		return false;
	}

	switch (clntaddr.sa_family)
	{
	case AF_INET:
	{
		// 端口号不为随机，或端口号不匹配
		if (
			((sockaddr_in*)& m_sockaddrSrv)->sin_port != INADDR_ANY
			&& (((sockaddr_in*)& m_sockaddrSrv)->sin_port != ((sockaddr_in*)& clntaddr)->sin_port)
			)
		{
			return false;
		}

		// IP地址不匹配
		if (
			((sockaddr_in*)& m_sockaddrSrv)->sin_addr.S_un.S_addr != ((sockaddr_in*)& clntaddr)->sin_addr.S_un.S_addr
			)
		{
			return false;
		}

		break;
	}
	case AF_INET6:
	{
		// 端口号不为随机，或端口号不匹配
		if (
			((sockaddr_in6*)& m_sockaddrSrv)->sin6_port != INADDR_ANY
			&& (((sockaddr_in6*)& m_sockaddrSrv)->sin6_port != ((sockaddr_in6*)& clntaddr)->sin6_port)
			)
		{
			return false;
		}

		// IP地址不匹配
		for (int i = 0; i < 16; ++i)
		{
			if (
				((sockaddr_in6*)& m_sockaddrSrv)->sin6_addr.u.Byte[i] != ((sockaddr_in6*)& clntaddr)->sin6_addr.u.Byte[i]
				)
			{
				return false;
			}
		}
		
		break;
	}
	default:
		return false;
	}

	return true;
}

bool TCP_IPClient::Connect(const SOCKET& sock)
{
	sockaddr addr = GetPeerAddress(sock);

	if (ConnectClient(addr) == false)
	{
		return false;
	}

	m_socket = sock;

	return true;
}
