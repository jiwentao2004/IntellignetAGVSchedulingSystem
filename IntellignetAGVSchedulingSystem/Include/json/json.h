// Copyright 2007-2010 Baptiste Lepilleur and The JsonCpp Authors
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#pragma once
#ifndef JSON_JSON_H_INCLUDED
#define JSON_JSON_H_INCLUDED

#include "autolink.h"
#include "features.h"
#include "reader.h"
#include "value.h"
#include "writer.h"
//#include "json_value.cpp"
//#include "json_reader.cpp"
//#include "json_writer.cpp"
#include <string>

using namespace std;

/*******·â×°Json¶ÁÐ´º¯Êý********/
static int Json_ReadInt(Json::Value JV, int ori_value = 0);
static double Json_ReadDouble(Json::Value JV, double ori_value = 0.0);
static float Json_ReadFloat(Json::Value JV, float ori_value = 0.0f);
static string Json_ReadString(Json::Value JV, string ori_value = "");
static bool Json_ReadBool(Json::Value JV, bool ori_value = false);
static unsigned int Json_ReadUInt(Json::Value JV, unsigned int ori_value = 0);
#ifdef _WIN64
static long long Json_ReadInt64(Json::Value JV, long long ori_value = 0);
static unsigned long long Json_ReadUInt64(Json::Value JV, unsigned long long ori_value = 0);
#endif //!_WIN64

///////////////////////////////////////////////////
int Json_ReadInt(Json::Value JV, int ori_value)
{
	int result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::intValue)
		result = JV.asInt();
	return result;
}

double Json_ReadDouble(Json::Value JV, double ori_value)
{
	double result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::realValue)
		result = JV.asDouble();
	return result;
}

float Json_ReadFloat(Json::Value JV, float ori_value)
{
	float result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::realValue)
		result = JV.asFloat();
	return result;
}

string Json_ReadString(Json::Value JV, string ori_value)
{
	string result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::stringValue)
		result = JV.asCString();
	return result;
}

bool Json_ReadBool(Json::Value JV, bool ori_value)
{
	bool result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::booleanValue)
		result = JV.asBool();
	return result;
}

unsigned int Json_ReadUInt(Json::Value JV, unsigned int ori_value)
{
	unsigned int result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::uintValue)
		result = JV.asUInt();
	return result;
}

#ifdef _WIN64
long long Json_ReadInt64(Json::Value JV, long long ori_value)
{
	long long result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::intValue)
		result = JV.asInt64();
	return result;
}

unsigned long long Json_ReadUInt64(Json::Value JV, unsigned long long ori_value)
{
	unsigned long long result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::uintValue)
		result = JV.asUInt64();
	return result;
}
#endif //_WIN64

#ifdef _WIN64
#define Json_ReadULL Json_ReadUInt64
#define Json_ReadLL Json_ReadInt64
#else
#define Json_ReadULL Json_ReadUInt
#define Json_ReadLL Json_ReadInt
#endif 

#endif // JSON_JSON_H_INCLUDED
