#include "AString.h"
#include <sstream>
#include <codecvt>
#include <cstdarg>
#include <fstream>
#include <chrono>

using namespace chrono;


using WCHAR_GBK		= codecvt_byname<wchar_t, char, mbstate_t>;
using WCHAR_UTF8	= codecvt_utf8<wchar_t>;

// linuxÏÂÎª"zh_CN.GBK"
#define GBK_NAME ".936"


AString::AString()
{
}

AString::AString(const char* _str,const char* encode)
{
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		wstring::operator=(cvtGBK.from_bytes(_str).c_str());
	}
	else if (encode == Encode_UTF8)
	{
		wstring::operator=(cvtUTF8.from_bytes(_str).c_str());
	}
}

AString::AString(const wchar_t* _wstr)
{
	wstring::operator=(_wstr);
}

AString::AString(const string& _str, const char* encode)
{
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		wstring::operator=(cvtGBK.from_bytes(_str).c_str());
	}
	else if (encode == Encode_UTF8)
	{
		wstring::operator=(cvtUTF8.from_bytes(_str).c_str());
	}
}

AString::AString(const wstring& _wstr)
{
	wstring::operator=(_wstr.c_str());
}

AString::~AString()
{
	clear();
}

string AString::toACSII() const
{
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));

	return cvtGBK.to_bytes(c_str()).c_str();
}

string AString::toUTF_8() const
{
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	return cvtUTF8.to_bytes(c_str()).c_str();
}

wstring AString::toUNICODE() const
{
	return c_str();
}

AString& AString::append(const string& _Right, const char* encode)
{
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		wstring::append(cvtGBK.from_bytes(_Right).c_str());
	}
	else if (encode == Encode_UTF8)
	{
		wstring::append(cvtUTF8.from_bytes(_Right).c_str());
	}

	return *this;
}

void AString::toDebug()
{
	auto start = system_clock::now();
	std::time_t cur_time = system_clock::to_time_t(start);
	
	char cTimeArr[1024];
	ctime_s(cTimeArr, 1024, &cur_time);
	AString str = "";
	str.Format("%s[Debug] %lld %s\n", cTimeArr, duration_cast<milliseconds>(start.time_since_epoch()).count()%1000,toACSII().c_str());

#ifdef _UNICODE
	OutputDebugString(str.c_str());
#else
	OutputDebugString(str.toACSII().c_str());
#endif

	return;
}

bool AString::toFile(const AString _file)
{
	ofstream file;
	file.open(_file.toACSII().c_str());

	if (file.fail())
	{
		// open file failed
		throw("Write to file error:Open file failed!");
		return false;
	}

	file << this->toACSII();

	file.close();

	return true;
}

bool AString::toLogFile(const AString _file)
{
	ofstream file;
	file.open(_file.toACSII().c_str());

	if (file.fail())
	{
		// open file failed
		throw("Write to file error:Open file failed!");
		return false;
	}

	auto start = system_clock::now();
	std::time_t cur_time = system_clock::to_time_t(start);

	char cTimeArr[1024];
	ctime_s(cTimeArr, 1024, &cur_time);
	AString str = "";
	str.Format("%s[Log] %lld %s\n", cTimeArr, duration_cast<milliseconds>(start.time_since_epoch()).count() % 1000, toACSII().c_str());

	file << str.toACSII();

	file.close();

#ifdef _UNICODE
	OutputDebugString(str.c_str());
#else
	OutputDebugString(str.toACSII().c_str());
#endif

	return true;
}

AString& AString::FromFile(const AString _file, const char* encode)
{
	ifstream file;
	file.open(_file.toACSII().c_str());

	if (file.fail())
	{
		// open file failed
		throw("Read from file error:Open file failed!");
		return *this = L"";
	}

	ostringstream ostring;
	ostring << file.rdbuf();

	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	wstring_convert<WCHAR_UTF8> cvtUTF8;

	if (encode == Encode_ACSII)
	{
		*this = cvtGBK.from_bytes(ostring.str().c_str()).c_str();
	}
	else if (encode == Encode_UTF8)
	{
		*this = cvtUTF8.from_bytes(ostring.str().c_str()).c_str();
	}
	else
	{
		*this = ostring.str().c_str();
	}

	return *this;
}

AString& AString::Format(const char* format, ...)
{
	int old_size = strlen(format);
	std::unique_ptr<char[]> buf(new char[old_size]);
	va_list ap;

	va_start(ap, format);
	int new_size = vsnprintf(buf.get(), old_size, format, ap);
	va_end(ap);
	if (new_size < 0)
	{
		return *this = L"";
	}

	buf.reset(new char[new_size + 1]);
	va_start(ap, format);
	new_size = vsnprintf(buf.get(), new_size + 1, format, ap);
	va_end(ap);

	if (new_size < 0)
	{
		return *this = L"";
	}

	return *this = buf.get();
}

AString& AString::Format(const wchar_t* format, ...)
{
	wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
	
	const char* fmt = cvtGBK.to_bytes(format).c_str();

	int old_size = strlen(fmt);
	std::unique_ptr<char[]> buf(new char[old_size]);
	va_list ap;

	va_start(ap, format);
	int new_size = vsnprintf(buf.get(), old_size, fmt, ap);
	va_end(ap);
	if (new_size < 0)
	{
		return *this = L"";
	}

	buf.reset(new char[new_size + 1]);
	va_start(ap, format);
	new_size = vsnprintf(buf.get(), new_size + 1, fmt, ap);
	va_end(ap);

	if (new_size < 0)
	{
		return *this = L"";
	}

	return *this = buf.get();
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
