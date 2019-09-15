/*!
 * @file TCP_IPBase.h
 * @brief TCP/IP通信的基类文件
 * @date 2019-09-12
 * @author FanKaiyu
 * @version 1.0
*/
#pragma once
#include <string>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <WinDNS.h>

#pragma comment(lib, "WS2_32")

class TCP_IPBase
{
public:
	TCP_IPBase();
	~TCP_IPBase();

protected:
	// 套接字
	SOCKET m_socket;

protected:
	/*!
	 * @brief 获取本地协议地址
	 * @date 2019-09-12
	 * @return sockaddr 返回本地协议地址
	*/
	inline sockaddr GetLocalAddress();

	/*!
	 * @brief 获取远程协议地址
	 * @date 2019-09-12
	 * @return sockaddr 返回远程协议地址
	*/
	inline sockaddr GetPeerAddress(); 

	/*!
	 * @brief 获取本地协议地址
	 * @date 2019-09-15
	 * @param SOCKET& socket描述符
	 * @return sockaddr 返回本地协议地址
	*/
	sockaddr GetLocalAddress(const SOCKET& sock);

	/*!
	 * @brief 获取远程协议地址
	 * @date 2019-09-15
	 * @param SOCKET& socket描述符
	 * @return sockaddr 返回远程协议地址
	*/
	sockaddr GetPeerAddress(const SOCKET& sock);

	/*!
	 * @brief 初始化套接字库
	 * @date 2019-09-15
	 * @return bool 初始化成功返回true,否则返回false
	*/
	bool InitWSA();

	/*!
	 * @brief 创建套接字
	 * @date 2019-09-15
	*/
	SOCKET CreateSocket();

	/*!
	 * @brief 绑定套接字
	 * @date 2019-09-15
	 * @param SOCKET& 要绑定的套接字 
	 * @param sockaddr_in& 绑定的地址,协议IPV4
	 * @return bool 绑定成功返回true,否则返回false
	*/
	bool BindSocket(SOCKET& sock,const sockaddr& addr);

	/*!
	 * @brief 关闭套接字
	 * @date 2019-09-15
	*/
	inline void CloseSocket();

	/*!
	 * @brief 关闭套接字
	 * @date 2019-09-15
	 * @param SOCKET& 要关闭的套接字
	*/
	void CloseSocket(SOCKET& sock);
};

