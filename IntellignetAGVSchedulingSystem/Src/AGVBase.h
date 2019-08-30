/*!
 * @file AGVBase
 * @brief 描述AGV基本属性的信息
 * @author FanKaiyu
 * @date 2019-08-29
 * @version 1.0
*/
#pragma once
#include "AGVType.h"
#include "AGVEnum.h"

#include <string>

using namespace std;

#ifndef _AGV_BASE_H
#define _AGV_BASE_H

/*!
 * @class AGVBase
 * @brief 描述AGV基本属性的类
 * @date 2019-08-29
*/
class AGVBase
{
public:
	AGVBase();
	~AGVBase();
	AGVBase(const unsigned short usNo,const AGVType& Type);
	AGVBase(const unsigned short usNo, const AGVType& Type,const unsigned short usCurLocation,const unsigned short usEndLocation);

#pragma region AGV Arrtibute
private:
	// AGV属性变量

	/*!
	 * @brief 描述AGV编号的值
	 * @date 2019-08-29
	*/
	unsigned short m_usNo;

	/*!
	 * @brief 描述AGV型号的对象
	 * @date 2019-08-29
	*/
	AGVType m_Type;

	// 描述AGV当前状态的值

	/*!
	 * @brief 描述AGV当前位置信息的值,通常表示当前RFID卡号
	 * @date 2019-08-29
	*/
	unsigned short m_usCurLocation;

	/*!
	 * @brief 描述AGV当前速度的值,通常为百分比
	 * 
	 * 双驱动AGV正向移动时速度为正值,反向移动时速度为负值
	 * @date 2019-08-29
	 * @update 2019-08-30 FanKaiyu 增加双驱动AGV速度说明
	*/
	char m_chCurSpeed;

	/*!
	 * @brief 描述AGV当前剩余电量的值,通常为百分比
	 * @date 2019-08-29
	*/
	unsigned char m_byBattery;

	/*!
	 * @brief 描述AGV当前升降杆状态的标识
	 * @date 2019-08-29
	*/
	unsigned char m_byLifter;

	/*!
	 * @brief 描述AGV当前辊筒或链条状态的标识
	 * @date 2019-08-29
	*/
	unsigned char m_byRoller;

	// 描述AGV当前机械臂状态的标识

	/*!
	 * @brief 描述AGV机械臂当前执行的动作
	 * @date 2019-08-29
	*/
	unsigned short m_usArmAction;

	/*!
	 * @brief 描述AGV机械臂当前执行动作的状态
	 * @date 2019-08-29
	*/
	unsigned char m_byArmStatus;

	/*!
	 * @brief 描述AGV当前的运行状态
	 * @date 2019-08-29
	*/
	unsigned char m_byStatus;

	/*!
	 * @brief 描述AGV当前的异常信息
	 * @date 2019-08-29
	*/
	char m_chError;

	/*!
	 * @brief 描述AGV当前的载货数量
	 * @date 2019-08-29
	*/
	unsigned char m_byCargo;

	/*!
	 * @brief 描述AGV移动目标位置的值,通常表示终点RFID卡号
	 * @date 2019-08-29
	*/
	unsigned short m_usEndLocation;

	/*!
	 * @brief 描述AGV机械臂动作名称的字符串组
	 * @date 2019-08-30
	*/
	string m_strActNameArr[0xFF];

	/*!
	 * @brief 描述AGV上一位置信息,通常表示上一RFID卡号
	 * @date 2019-08-30
	*/
	unsigned short m_usOldLocation;

	/*!
	 * @brief 描述AGV上一终点位置信息,通常表示上一RFID卡号
	 * @date 2019-08-30
	*/
	unsigned short m_usOldEndLocation;
#pragma endregion

#pragma region AGV Action Function Code
public:
	// AGV动作函数

	/*!
	 * @brief 移动至工站
	 *
	 * 通知AGV移动至指定的工站
	 * @date 2019-08-29
	 * @param unsigned short 工站编号
	*/
	void MoveToStation(const unsigned short usStation);

	/*!
	 * @brief 移动至坐标
	 *
	 * 通知AGV移动至指定的位置
	 * @date 2019-08-29
	 * @param unsigned short 位置信息,通常为RFID卡编号
	*/
	void MoveToLocation(const unsigned short usLocation);

	/*!
	 * @brief 车速调整
	 *
	 * 用于用户临时调整车速,提升AGV速度或降低AGV速度.
	 * 仅1次有效.
	 * @date 2019-08-29
	 * @param char 车速
	*/
	void SetSpeed(const char chSpeed);

	/*!
	 * @brief 急停
	 *
	 * 用于紧急情况下远程停止AGV
	 * @date 2019-08-29
	*/
	void Scream();

	/*!
	 * @brief 复位
	 *
	 * 重置AGV的状态信息,使AGV恢复运行
	 * @date 2019-08-29
	*/
	void Reset();

	/*!
	 * @brief 恢复默认值
	 *
	 * 重置AGV的状态信息,重新获取AGV状态信息
	 * @date 2019-08-29
	*/
	void Default();

	/*!
	 * @brief 关机
	 *
	 * 远程控制AGV关闭电源
	 * @date 2019-08-30
	*/
	void Shutdown();

	/*!
	 * @brief 休眠
	 *
	 * 远程控制AGV至休眠状态
	 * @date 2019-08-30
	*/
	void Sleep();

	/*!
	 * @brief 唤醒/开机
	 * 
	 * 远程控制AGV开启电源或唤醒
	 * @date 2019-08-30
	*/
	void Wakeup();

	/*!
	 * @brief 升降杆控制
	 *
	 * 远程控制AGV升降杆上升或下降
	 * @date 2019-08-30
	 * @param unsigned char 为0时停止,为1时上升,为2时下降
	*/
	void LifterControl(const unsigned char byCtrl);

	/*!
	 * @brief 辊筒/链条控制
	 *
	 * 远程控制AGV辊筒正传、反转、停止
	 * date 2019-08-30
	 * @param unsigned char 为0时停止,为1时正转,为2时反转
	*/
	void RollerControl(const unsigned char byCtrl);

	/*!
	 * @brief 机械臂动作控制
	 *
	 * 远程控制AGV机械臂动作开始,停止
	 * date 2019-08-30
	 * @param unsigned short 为0时停止,为其他值时执行相应动作
	*/
	void ArmControl(const unsigned short byCtrl);
#pragma endregion

#pragma region Initialize AGV Attribute
public:
	// 初始化AGV属性函数

	/*!
	 * @brief AGV属性初始化
	 * @date 2019-08-30
	 * @param unsigned short AGV编号
	 * @param AGVType* AGV类型对象
	*/
	void InitializeAttribut(const unsigned short usNo,const AGVType& type);

	/*!
	 * @brief 重载AGV属性初始化
	 * @date 2019-08-30
	 * @param unsigned short AGV编号
	 * @param AGVType* AGV类型对象
	 * @param unsigned short AGV当前位置信息,通常指RFID卡编号
	 * @param unsigned short AGV终点位置信息
	*/
	void InitializeAttribut(const unsigned short usNo,const AGVType& type, const unsigned short usCurLocation, const unsigned short usEndLocation = 0);

	/*!
	 * @brief 加载AGV机械臂动作名称
	 * @date 2019-08-30
	 * @param string AGV动作文件路径
	*/
	void LoadActName(string strPath);

	/*!
	 * @brief 加载AGV机械臂动作名称
	 * @date 2019-08-30
	 * @param string AGV动作文件目录路径
	*/
	void LoadActNameFile(string strPath);
#pragma endregion

#pragma region Update AGV Attribute
public:
	// 更新AGV属性函数

	/*!
	 * @brief 更新AGV当前的速度信息
	 * @date 2019-08-30
	 * @param char AGV传回的当前速度信息
	*/
	void UpdateSpeed(const char chSpeed);

	/*!
	 * @brief 更新AGV当前的电量信息
	 * @date 2019-08-30
	 * @param char AGV传回的当前的剩余电量信息
	*/
	void UpdateBattery(const unsigned char byBattery);

	/*!
	 * @brief 更新AGV当前的状态信息
	 * @date 2019-08-30
	 * @param unsigned char AGV传回的当前运行状态信息
	*/
	void UpdateStatus(const unsigned char byStatus);

	/*!
	 * @brief 更新AGV当前的载货数量信息
	 * @date 2019-08-30
	 * @param unsigend char AGV传回的当前的载货数量信息,通常0标识空载,255表示满载
	*/
	void UpdateCargo(const unsigned char byCargo);

	/*!
	 * @brief 更新AGV当前升降杆的状态信息
	 * @date 2019-08-30
	 * @param unsigned char AGV传回的当前升降杆状态信息
	*/
	void UpdateLifter(const unsigned char byLifter);

	/*!
	 * @brief 更新AGV当前辊筒的状态信息
	 * @date 2019-08-30
	 * @param unsigned char AGV传回的当前辊筒状态信息
	*/
	void UpdateRoller(const unsigned char byRoller);

	/*!
	 * @brief 更新AGV当前机械臂执行的动作信息
	 * @date 2019-08-30
	 * @param unsigned short AGV传回的机械臂当前执行的动作信息
	*/
	void UpdateArmAction(const unsigned short usAction);

	/*!
	 * @brief 更新AGV当前机械臂执行动作的状态
	 * @date 2019-08-30
	 * @param unsigned char AGV传回的机械臂当前执行动作的状态信息
	*/
	void UpdateArmStatus(const unsigned char byStatus);

	/*!
	 * @brief 更新AGV当前的位置信息
	 * @date 2019-08-30
	 * @param unsigend short AGV传回的当前位置信息
	 * @return unsigned short AGV上一位置信息
	*/
	const unsigned short UpdateCurLocation(const unsigned short usLocation);

	/*!
	 * @brief 更新AGV终点的位置信息
	 * @date 2019-08-30
	 * @param unsigned short AGV传回的终点位置信息
	 * @return unsigned short AGV上一终点位置信息
	*/
	const unsigned short UpdateEndLocation(const unsigned short usLocation);

	/*!
	 * @brief 更新AGV异常状态信息
	 * @date 2019-08-30
	 * @param char AGV传回的异常状态信息
	*/
	void UpdateError(const char chError);
#pragma endregion

#pragma region Get AGV Attribute
public:
	// 获取AGV属性函数

	/*!
	 * @brief 获取AGV编号信息
	 * @date 2019-08-30
	 * @return unsigned short AGV编号信息
	*/
	const unsigned short GetNo() const;

	/*!
	 * @brief 获取AGV类型信息
	 * @date 2019-08-30
	 * @return AGVType AGV类型信息
	*/
	AGVType GetType() const;

	/*!
	 * @brief 获取AGV当前位置信息
	 * @date 2019-08-30
	 * @return unsigned short AGV当前位置信息
	*/
	const unsigned short GetCurLocation() const;

	/*!
	 * @brief 获取AGV当前速度信息
	 * @date 2019-08-30
	 * @return char AGV当前速度信息
	*/
	const char GetSpeed() const;

	/*!
	 * @brief 获取AGV当前剩余电量信息
	 * @date 2019-08-30
	 * @return unsigned char AGV当前剩余电量信息
	*/
	const unsigned char GetBattery() const;

	/*!
	 * @brief 获取AGV当前运行状态信息
	 * @date 2019-08-30
	 * @return unsigned short AGV当前的运行状态信息
	*/
	const unsigned char GetStatus() const;

	/*!
	 * @brief 获取AGV当前异常信息
	 * @date 2019-08-30
	 * @return char AGV当前的异常信息
	*/
	const char GetError() const;

	/*!
	 * @brief 获取AGV当前的载货数量
	 * @date 2019-08-30
	 * @return unsigned char AGV当前的载货数量
	*/
	const unsigned char GetCargo() const;

	/*!
	 * @brief 获取AGV当前终点位置信息
	 * @date 2019-08-30
	 * @return unsigned short AGV当前终点位置信息
	*/
	const unsigned short GetEndLocation() const;

	/*!
	 * @brief 获取AGV机械臂动作名
	 * @date 2019-08-30
	 * @param unsigned char AGV机械臂动作编号
	 * @return string 机械臂动作名
	*/
	string GetArmActionName(const unsigned char byAction);

	/*!
	 * @brief 获取AGV上一位置信息
	 * @date 2019-08-30
	 * @return unsigned short AGV上一位置信息
	*/
	const unsigned short GetOldLocation() const;

	/*!
	 * @brief 获取AGV上一终点位置信息
	 * @date 2019-08-30
	 * @return unsigned short AGV上一终点位置信息
	*/
	const unsigned short GetOldEndLocation() const;

	/*!
	 * @brief 获取AGV升降杆当前状态信息
	 * @date 2019-08-30
	 * @return unsigned char AGV升降杆当前状态信息
	*/
	const unsigned char GetLifter() const;

	/*!
	 * @brief 获取AGV辊筒当前状态信息
	 * @date 2019-08-30
	 * @return unsigned char AGV辊筒当前状态信息
	*/
	const unsigned char GetRoller() const;

	/*!
	 * @brief 获取AGV机械臂当前执行的动作信息
	 * @date 2019-08-30
	 * @return unsigned short AGV机械臂当前执行的动作信息 
	*/
	const unsigned short GetArmAction() const;

	/*!
	 * @brief 获取AGV机械臂当前执行动作的状态信息
	 * @date 2019-08-30
	 * @return unsigned char AGV机械臂当前执行动作的状态信息
	*/
	const unsigned char GetArmStatus() const;
#pragma endregion

#pragma region Set AGV Attribute
public:
	// 修改AGV属性函数

	/*!
	 * @brief 修改AGV异常状态信息
	 *
	 * UpdateError函数用以接收AGV上传回的异常状态信息，并修改异常状态信息
	 * SetError函数用以上位机主动修改异常状态信息
	 * @param char 异常状态信息
	*/
	void SetError(const char chError);
#pragma endregion
};

#endif // !_AGV_BASE_H