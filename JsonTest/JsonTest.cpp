// JsonTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <codecvt>
#include "../IntellignetAGVSchedulingSystem/Include/json/json.h"

using WCHAR_GBK		= codecvt_byname<wchar_t, char, mbstate_t>;
using WCHAR_UTF8	= codecvt_utf8<wchar_t>;

// linux下为"zh_CN.GBK"
#define GBK_NAME ".936"

int main()
{
	ifstream fin;
	fin.open("./Config/Arm.json");
	if (!fin)
	{
		// open file failed
		throw("Loading arm action name error:Open arm config file failed!");
		return -1;
	}

	ostringstream ostring;
	ostring << fin.rdbuf();
	fin.close();

	string strContext = ostring.str();
	// CharReaderBuilder
	Json::CharReaderBuilder builder;
	Json::CharReader* JsonReader(builder.newCharReader());
	Json::Value JsonRoot;

	JSONCPP_STRING errs;
	const char* pstr = strContext.c_str();

	if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
	{
		// read json string failed
		throw("Loading arm action name error:" + errs);
		return -1;
	}

	// 机械臂名称Json对象组
	Json::Value ArmArr = JsonRoot["Arm"];

	for (size_t k = 0; k < ArmArr.size(); ++k)
	{
		// 机械臂名称
		Json::Value Arm = ArmArr[k];

		// AGV编号
		int no = Json_ReadInt(Arm["No"]);

		// 编号与AGV不符或不是全局配置则不使用此配置信息
		if (no != 1 && no != 0)
		{
			continue;
		}

		for (int i = 1; i < 0xFF; ++i)
		{
			ostringstream ostrName;
			string strAction = "";

			ostrName << i;

			Json::Value action = Arm.get(ostrName.str(), Json::Value());

			// UTF-8 转 ACSII

			if (action.isNull())
			{
				continue;
			}

			strAction = action.asString();

			if (strAction.empty())
			{
				continue;
			}

			// gbk与unicode之间的转换器
			wstring_convert<WCHAR_GBK>  cvtGBK(new WCHAR_GBK(GBK_NAME));
			// utf8与unicode之间的转换器
			wstring_convert<WCHAR_UTF8> cvtUTF8;
			// 从utf8转换为unicode
			wstring ustr = cvtUTF8.from_bytes(strAction);
			// 从unicode转换为gbk
			strAction = cvtGBK.to_bytes(ustr);

			printf("动作:%d的名称是:%s\n",i, strAction.c_str());
		}
	}

	delete JsonReader;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
