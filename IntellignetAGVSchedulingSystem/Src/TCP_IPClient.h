/*!
 * @file TCP_IPClient.h
 * @breief 描述TCP/IP客户端属性以及功能的文件
 * @date 2019-09-15
 * @author FanKaiyu
 * @version 1..0
*/
#pragma once
#include "TCP_IPBase.h"

class TCP_IPClient :
	public TCP_IPBase
{
public:
	TCP_IPClient();
	~TCP_IPClient();

private:
	/*!
	 * @brief 客户端在主动连接服务端时生成的SOCKET描述符
	 * 可通过关闭此变量使得connect函数提前结束并返回
	 * @date 2019-09-15
	*/
	SOCKET m_sockTmp;

	/*!
	 * @brief 服务端地址
	 * 
	 * 用以主动连接服务端
	 * 或接收服务端连接时与客户端匹对
	 * @date 2019-09-15
	*/
	sockaddr m_sockaddrSrv;

	/*!
	 * @brief 客户端地址
	 *
	 * 用以绑定SOCKET,以固定IP的方式与服务端连接
	 * @date 2019-09-15
	*/
	sockaddr m_sockaddrClnt;

private:
	/*!
	 * @brief 连接服务端
	 *
	 * 用以固定IP、端口的方式连接TCP服务端
	 * @date 2019-09-15
	 * @param sockaddr 客户端地址
	 * @param sockaddr 服务端地址
	 * @return bool 连接成功返回true,否则返回false
	*/
	inline bool Connect(const sockaddr& clienaddr,const sockaddr& srvaddr);

	/*!
	 * @brief 连接服务端
	 *
	 * 用以随机端口的方式连接TCP服务端
	 * @date 2019-09-15
	 * @param sockaddr 服务端地址
	 * @return bool 连接成功返回true,否则返回false
	*/
	inline bool Connect(const sockaddr& srvaddr);

	/*!
	 * @brief 连接服务端
	 * @date 2019-09-15
	 * @param sockaddr 服务器地址
	 * @return bool 连接成功返回true,否则返回false
	*/
	bool ConnectServer(const sockaddr& srvaddr);

	/*!
	 * @brief 连接客户端
	 * @date 2019-09-15
	 * @param sockaddr 客户端地址
	 * @return bool 连接成功返回true,否则返回false
	*/
	bool ConnectClient(const sockaddr& clntaddr);

public:
	/*!
	 * @brief 连接客户端
	 * @date 2019-09-15
	 * @param SOCKET 客户端socket描述符
	 * @return bool 连接成功返回true,否则返回false
	*/
	bool Connect(const SOCKET& sock);

	/*!
	 * @brief 连接服务端
	 * @date 2019-09-15
	 * @return bool 连接成功返回true,否则返回false
	*/
	bool Connect();
};

