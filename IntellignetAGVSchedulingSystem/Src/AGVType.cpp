#include "AGVType.h"

#ifdef _AGV_TYPE_H

AGVType::AGVType()
{
	/*!
	 * @brief 初始化
	 * @date 2019-08-29
	*/
	m_strBrand = "";
	m_strVersion = "";
	m_usAbility = None;
	m_fMaxSpeed = 0.0f;
	m_fMaxWeight = 0.0f;
}


AGVType::~AGVType()
{
}


AGVType::AGVType(const AGVType& type)
{
	/*!
	 * @brief 拷贝AGV类型信息
	 * @date 2019-08-30
	*/
	m_strBrand = type.m_strVersion;
	m_strVersion = type.m_strVersion;
	m_usAbility = type.m_usAbility;
	m_fMaxSpeed = type.m_fMaxSpeed;
	m_fMaxWeight = type.m_fMaxWeight;
}

void AGVType::operator=(const AGVType& type)
{
	/*!
	 * @brief 拷贝AGV类型信息
	 * @date 2019-08-30
	*/
	m_strBrand = type.m_strVersion;
	m_strVersion = type.m_strVersion;
	m_usAbility = type.m_usAbility;
	m_fMaxSpeed = type.m_fMaxSpeed;
	m_fMaxWeight = type.m_fMaxWeight;
}
#endif // _AGV_TYPE_H