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

	return 0;
}