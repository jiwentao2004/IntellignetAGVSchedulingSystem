#include "AString.h"
#include <sstream>
#include <codecvt>
#include <cstdarg>
#include <fstream>
#include <chrono>

using namespace chrono;


using WCHAR_GBK		= codecvt_byname<wchar_t, char, mbstate_t>;
using WCHAR_UTF8	= codecvt_utf8<wchar_t>;

// linux下为"zh_CN.GBK"
#define GBK_NAME ".936"


AString::AString()
{
	m_wstr = L"";
}

AString::AString(const char* _str,const char* encode)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8与unicode之间的转换器
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// 从gbk转换为unicode
		m_wstr = cvtGBK.from_bytes(_str).c_str();
	}
	else if (encode == Encode_UTF8)
	{
		// 从utf8转换为unicode
		m_wstr = cvtUTF8.from_bytes(_str).c_str();
	}
}

AString::AString(const wchar_t* _wstr)
{
	m_wstr = _wstr;
}

AString::AString(const string& _str, const char* encode)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8与unicode之间的转换器
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// 从gbk转换为unicode
		m_wstr = cvtGBK.from_bytes(_str).c_str();
	}
	else if (encode == Encode_UTF8)
	{
		// 从utf8转换为unicode
		m_wstr = cvtUTF8.from_bytes(_str).c_str();
	}
}

AString::AString(const wstring& _wstr)
{
	m_wstr = _wstr;
}

AString::~AString()
{
	m_wstr.clear();
}

string AString::toACSII() const
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	// 从unicode转换为gbk
	return cvtGBK.to_bytes(m_wstr.c_str()).c_str();
}

string AString::toUTF_8() const
{
	// utf8与之间的转换器
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	// 从unicode转换为utf8
	return cvtUTF8.to_bytes(m_wstr.c_str()).c_str();
}

wstring AString::toUNICODE() const
{
	return m_wstr.c_str();
}

AString& AString::append(const string& _Right, const char* encode)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8与unicode之间的转换器
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// 从gbk转换为unicode
		m_wstr.append(cvtGBK.from_bytes(_Right).c_str());
	}
	else if (encode == Encode_UTF8)
	{
		// 从utf8转换为unicode
		m_wstr.append(cvtUTF8.from_bytes(_Right).c_str());
	}

	return *this;
}

AString& AString::append(const wstring& _Right)
{
	m_wstr.append(_Right);

	return *this;
}

AString& AString::append(const AString& _Right)
{
	m_wstr.append(_Right.m_wstr);

	return *this;
}

void AString::toDebug()
{
	// 计算机当前时间
	auto start = system_clock::now();
	// 转换为C时间
	std::time_t cur_time = system_clock::to_time_t(start);
	
	// 时间字符串
	char cTimeArr[1024];
	// 格式化时间
	ctime_s(cTimeArr, 1024, &cur_time);
	// 文本字符串
	AString str = "";
	// 格式化文本
	str.Format("%s[Debug] %lld %s\n", cTimeArr, duration_cast<milliseconds>(start.time_since_epoch()).count()%1000,toACSII().c_str());

	// 输出至输入框
#ifdef _UNICODE
	OutputDebugString(str.m_wstr.c_str());
#else
	OutputDebugString(str.toACSII().c_str());
#endif

	// 打印文本
	printf(str.toACSII().c_str());

	return;
}

bool AString::toFile(const AString _file)
{
	// 文件输出流
	ofstream file;

	// 打开文件
	file.open(_file.toACSII().c_str());

	// 文件打开失败
	if (file.fail())
	{
		// open file failed
		throw("Write to file error:Open file failed!");
		return false;
	}

	// 写入文件
	file << this->toACSII();

	// 关闭文件
	file.close();

	return true;
}

bool AString::toLogFile(const AString _file)
{
	// 文件输出流
	ofstream file;

	// 打开文件
	file.open(_file.toACSII().c_str());

	// 文件打开失败
	if (file.fail())
	{
		// open file failed
		throw("Write to file error:Open file failed!");
		return false;
	}

	// 计算机当前时间
	auto start = system_clock::now();
	// 转换为C时间
	std::time_t cur_time = system_clock::to_time_t(start);

	// 时间字符串
	char cTimeArr[1024];
	// 格式化时间
	ctime_s(cTimeArr, 1024, &cur_time);
	// 文本字符串
	AString str = "";
	// 格式化文本
	str.Format("%s[Log] %s\n", cTimeArr, toACSII().c_str());

	// 写入文件
	file << str.toACSII();

	// 关闭文件
	file.close();

	// 输出至输入框
#ifdef _UNICODE
	OutputDebugString(str.m_wstr.c_str());
#else
	OutputDebugString(str.toACSII().c_str());
#endif

	// 打印文本
	printf(str.toACSII().c_str());

	return true;
}

AString& AString::FromFile(const AString _file, const char* encode)
{
	// 文件输入流
	ifstream file;
	// 打开文件
	file.open(_file.toACSII().c_str());

	// 文件打开失败
	if (file.fail())
	{
		// open file failed
		throw("Read from file error:Open file failed!");
		m_wstr = L"";
		return *this;
	}

	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	// utf8与unicode之间的转换器
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		// 字符串输出流
		ostringstream ostring;
		// 读取文件
		ostring << file.rdbuf();

		// 从gbk转换为unicode
		m_wstr = cvtGBK.from_bytes(ostring.str().c_str()).c_str();
	}
	else if (encode == Encode_UTF8)
	{
		// 字符串输出流
		ostringstream ostring;
		// 读取文件
		ostring << file.rdbuf();

		// 从utf8转换为unicode
		m_wstr = cvtUTF8.from_bytes(ostring.str().c_str()).c_str();
	}
	else
	{
		// 宽字符串输出流
		wostringstream wostring;
		// 读取文件
		wostring << file.rdbuf();

		m_wstr = wostring.str().c_str();
	}

	// 关闭文件
	file.close();

	return *this;
}


Json::Value AString::toJson() const
{
	Json::CharReaderBuilder builder;
	Json::CharReader* JsonReader(builder.newCharReader());
	Json::Value JsonRoot;

	JSONCPP_STRING errs;
	string str = toACSII();
	const char* pstr = str.c_str();

	if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
	{
		// read json string failed
		throw("Loading arm action name error:" + errs);
  		return Json::Value();
	}

	delete JsonReader;

	return JsonRoot;
}

void AString::Clear()
{
	m_wstr.clear();
}

bool AString::Empty()
{
	return m_wstr.empty();;
}

wstring& AString::Str()
{
	return m_wstr;
}

bool AString::operator==(const string& _Right)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	// 从gbk转换为unicode
	return m_wstr == cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator==(const wstring& _Right)
{
	return m_wstr== _Right;
}

bool AString::operator==(const AString& _Right)
{
	return m_wstr == _Right.m_wstr;
}

bool AString::operator>(const string& _Right)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	// 从gbk转换为unicode
	return m_wstr > cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator>(const wstring& _Right)
{
	return m_wstr > _Right;
}

bool AString::operator>(const AString& _Right)
{
	return m_wstr > _Right.m_wstr;
}

bool AString::operator<(const string& _Right)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// 从gbk转换为unicode
	return m_wstr < cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator<(const wstring& _Right)
{
	return m_wstr < _Right;
}

bool AString::operator<(const AString& _Right)
{
	return m_wstr < _Right.m_wstr;
}

bool AString::operator!=(const string& _Right)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// 从gbk转换为unicode
	return m_wstr != cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator!=(const wstring& _Right)
{
	return m_wstr != _Right;
}

bool AString::operator!=(const AString& _Right)
{
	return m_wstr!= _Right.m_wstr;
}

bool AString::operator>=(const string& _Right)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// 从gbk转换为unicode
	return m_wstr >= cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator>=(const wstring& _Right)
{
	return m_wstr >= _Right;
}

bool AString::operator>=(const AString& _Right)
{
	return m_wstr >= _Right.m_wstr;
}

bool AString::operator<=(const string& _Right)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	// 从gbk转换为unicode
	return m_wstr <= cvtGBK.from_bytes(_Right.c_str());
}

bool AString::operator<=(const wstring& _Right)
{
	return m_wstr <= _Right;
}

bool AString::operator<=(const AString& _Right)
{
	return m_wstr <= _Right.m_wstr;
}

ostream& AString::operator<<(ostream& _Ostr)
{
	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	return _Ostr << cvtGBK.to_bytes(m_wstr.c_str());
}

wostream& AString::operator<<(wostream& _Ostr)
{
	return _Ostr << m_wstr;
}

wistream& AString::operator>>(wistream& _Istr)
{
	return _STD move(_Istr) >> m_wstr;
}

istream& AString::operator>>(istream& _Istr)
{
	string str;
	_STD move(_Istr) >> str;

	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	m_wstr = cvtGBK.from_bytes(str).c_str();

	return _Istr;
}

AString::operator bool()
{
	// 如果字符串不为空则转换为true,否则为false
	return !m_wstr.empty();
}

bool AString::operator==(const bool& _Right)
{
	// 如果字符串不为空则转换为true,否则为false
	return (!m_wstr.empty()) == _Right;
}

AString& AString::Format(const char* format, ...)
{
	m_wstr = L"";

	int old_size = strlen(format);
	
	va_list ap;

	va_start(ap, format);
	int new_size = _vscprintf(format, ap);
	if (new_size < 0)
	{
		return *this;
	}

	std::unique_ptr<char[]> buf(new char[new_size+1]);
	new_size = vsnprintf(buf.get(), new_size + 1, format, ap);
	va_end(ap);
	if (new_size < 0)
	{
		return *this;
	}

	// gbk与unicode之间的转换器
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	m_wstr = cvtGBK.from_bytes(std::string(buf.get()).c_str());

	return *this;
}

 AString& AString::Format(const wchar_t* format, ...)
{
	 m_wstr = L"";

	 va_list ap;

	 va_start(ap, format);
	 int new_size = _vscwprintf(format, ap);
	 if (new_size < 0)
	 {
		 return *this;
	 }

	 std::unique_ptr<wchar_t[]> buf(new wchar_t[new_size+1]);
	 new_size = _vsnwprintf_s(buf.get(), new_size + 1, new_size + 1,format, ap);
	 va_end(ap);
	 if (new_size < 0)
	 {
		 return *this;
	 }

	 m_wstr = buf.get();

	 return *this;
}
