#include "../IntellignetAGVSchedulingSystem/Src/AString.h"

int main(int argv, char* argc[])
{
	AString str = "≤‚ ‘";
	str.toDebug();
	str.toDebug();

	str = "";

	str.FromFile("../JsonTest/Config/Arm.json");

	str.toDebug();

	AString jsonStr = Json_ReadString(str.toJson()["Arm"][0]["3"]).c_str();

	jsonStr.toDebug();

	if (str)
	{
		printf("bool return true\n");

		str.Clear();

		if (!str)
		{
			printf("clear return false\n");
		}

		str = "";

		if (str)
		{
			printf("null return true\n");
		}
		else
		{
			printf("null return false\n");
		}
	}

	str.Format("Test string format:%d,%d\n", 100,100);

	printf(str.toACSII().c_str());

	str.Format(L"Test wstring format:%u,%lld\n", 1,100ll);

	printf(str.toACSII().c_str());

	wstring wt = L"123";
	string st = "123";
	AString at = "123";

	if (at == wt)
	{
		printf("at==wt\n");
	}

	if (at == st)
	{
		printf("at==st\n");
	}

	if (at == "123")
	{
		printf("at==123\n");
	}

	if (at == L"123")
	{
		printf("at==W123\n");
	}

	return 0;
}