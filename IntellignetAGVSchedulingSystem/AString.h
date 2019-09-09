/*!
 * @file AString.h
 * @brief 调度系统的自定义的字符串文件格式
 * @date 2019-09-09
 * @author FanKaiyu
 * @version 1.0
*/
#pragma once
#include <string>
#include <Windows.h>
#include "../IntellignetAGVSchedulingSystem/Include/json/json.h"

using namespace std;

#define Encode_ACSII "ACSII"
#define Encode_UTF8 "utf-8"
#define Encode_UNICODE "UNICODE"

/*!
 * @class AString
 * @brief 对wstring对象进行扩充，补充常用的功能以及函数
*/
class AString:
	public wstring
{
public:
	AString();
	AString(const char*, const char* encode = Encode_ACSII);
	AString(const wchar_t*);
	AString(const string&, const char* encode = Encode_ACSII);
	AString(const wstring&);
	~AString();

public:
	/*!
	 * @brief 输出ACSII格式的字符串
	 * @date 2019-09-09
	*/
	string toACSII() const;

	/*!
	 * @breif 输出UTF-8格式的字符串
	 * @date 2019-09-09
	*/
	string toUTF_8() const;

	/*!
	 * @brief 输出UNICODE格式的字符串
	 * @date 2019-09-09
	*/
	wstring toUNICODE() const;
	
	/*!
	 * @brief 添加字符串
	 * @date 2019-09-09
	 * @param string& 要添加的字符串
	 * @param const char* 编码格式
	*/
	AString& append(const string& _Right, const char* encode = Encode_ACSII);

	/*!
	 * @brief 打印至控制台
	 * @date 2019-09-09
	*/
	void toDebug();

	/*!
	 * @brief 写入至文件
	 * @date 2019-09-09
	 * @param AString 文件目录
	 * @return bool 写入成功返回true,否则返回false
	*/
	bool toFile(const AString);

	/*!
	 * @brief 从文件中读取内容
	 * @date 2019-09-09
	 * @param AStrig 文件目录
	 * @return bool 读取成功返回true,否则返回false
	*/
	bool FromFile(const AString);

	/*!
	 * @brief 格式化字符串
	 * @date 2019-09-09
	 * @param const char* 字符串格式化样式
	 * @param ...	需要格式化的参数
	*/
	AString& Format(const char* format,...);
	AString& Format(const wchar_t* format, ...);

	/*!
	 * @brief 转换为JSON对象
	 * @date 2019-09-09
	 * @return Json::Value 返回JSON对象
	*/
	Json::Value toJson() const;

	/*!
	 * @brief 转换为LPCTSTR字符串
	 * @date 2019-09-09
	*/
	LPCTSTR toLPCTSTR() const;
};

