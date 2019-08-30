/*!
 * @file AGVType
 * @brief 描述AGV种类的基本信息
 * @author FanKaiyu
 * @date 2019-08-29
 * @version 1.0
*/
#pragma once
#include <string>

using namespace std;

#ifndef _AGV_TYPE_H
#define _AGV_TYPE_H

/*!
 * @brief 描述AGV能力的标识枚举
 * @date 2019-08-29
 */
enum AGVAbility
{
	// 无
	None,
	// 背负
	Consign,
	// 举升
	Lift,
	// 牵引
	Pull,
	// 潜入
	Dive,
	// 机械臂
	Arm,
	// 叉车
	Fork,
};

/*!
 * @class AGVType
 * @brief 描述AGV类型的基本属性的类
 * @date 2019-08-29
*/
class AGVType
{
public:
	AGVType();
	~AGVType();
	AGVType(const AGVType& type);

public:
	/*!
	 * @brief 用以描述AGV品牌的字符串
	 * @date 2019-08-29
	*/
	string m_strBrand;

	/*!
	 * @brief 用以描述AGV型号的字符串
	 * @date 2019-08-29
	*/
	string m_strVersion;

	/*!
	 * @brief 用以描述AGV功能的标识
	 * @date 2019-08-29
	*/
	unsigned short m_usAbility;

	/*!
	 * @brief 用以描述AGV最大速度的值,单位:m/min
	 * @date 2019-08-29
	*/
	float m_fMaxSpeed;

	/*!
	 * @brief 用以描述AGV最大载重量的值,单位:kg
	 * @date 2019-08-29
	*/
	float m_fMaxWeight;

public:
	/*!
	 * @brief 拷贝AGV类型信息
	 * @param AGVType& AGV类型信息
	*/
	void operator=(const AGVType& type);
};

#endif // !_AGV_TYPE_H