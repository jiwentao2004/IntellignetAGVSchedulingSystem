/*!
 * @file AGVEnum
 * @brief 描述AGV状态、异常等常量的文件
 * @author FanKaiyu
 * @date 2019-08-29
 * @version 1.0
*/
#pragma once

/*!
 * @brief 描述AGV载货数量的枚举
 * @date 2019-08-29
 */
enum AGVCargo
{
	// 空载
	Cargo_None,

	// 满载
	Cargo_Full = 0xFF,
};

/*!
 * @brief 描述AGV异常状态的枚举
 *
 * 异常值大于0，为AGV自检的异常
 * 异常值下雨0，为上位机检测的异常
 * @date 2019-08-29
 * @update 2019-08-30 FanKaiyu 增加AGV异常状态分类的说明
 */
enum AGVError
{
	// 无异常
	Error_None,

	// 因网络异常,无法发送数据造成的异常
	Error_Linkbreak = -1,

	// 升降杆长时间未升到位或未降下引起的异常
	Error_LifterError = -2,

	// 辊筒或链条长时间未接到货物或未将货物卸下引起的异常
	Error_RollerError = -3,

	// 机械臂动作长时间未执行完成引起的异常
	Error_ArmError = -4,

	// 因长时间无法找到磁条的脱磁异常
	Error_Miss = 1,

	// 因碰撞引起的AGV停止,需要人位处理
	Error_Crash,

	// 因检测路线上的物体,无法继续移动
	Error_Obs,
};

/*!
 * @brief 描述AGV运行状态的枚举
 * @date 2019-08-29
 */
enum AGVStatus
{
	// 待机
	Status_Wait,

	// 运行
	Status_Run,

	// 停止
	Status_Stop,

	// 急停
	Status_Scream,

	// 寻磁
	Status_Find,

	// 非接触避障减速
	Status_ObsDown,

	// 交通管制停止
	Status_Traffic,

	// 休眠 2019-08-30
	Status_Sleep,

	// 充电中 2019-09-03
	Status_Charging,

	// 远程急停 2019-09-03
	Status_RemoteScream,

	// 全线急停 2019-09-03
	Status_AllScream,

	// 加速 2019-09-03
	Status_SpeedUp,

	// 减速 2019-09-03
	Status_SpeedDown,

	// 暂停 2019-09-03
	Status_Pause,
};

/*!
 * @brief 描述AGV升降杆状态的枚举
 * @date 2019-08-29
 */
enum AGVLifter
{
	// 落下
	Lifter_Down,
	// 下落中
	Lifter_GoingDown,
	// 升起中
	Lifter_GoingUp,
	// 升起
	Lifter_Up,
};

/*!
 * @brief 描述AGV辊筒状态的枚举
 * @date 2019-08-30
*/
enum AGVRoller
{
	// 停止
	Roller_Stop,
	// 正转中
	Roller_Positive,
	// 反转中
	Roller_Negative,
};

/*!
 * @brief 描述AGV机械臂状态的枚举
 * @date 2019-08-30
*/
enum AGVArmStatus
{
	// 未执行
	Arm_Status_None,
	// 执行中
	Arm_Status_Execute,
	// 完成
	Arm_Status_Done,
};


/*!
 * @brief 控制AGV升降杆上升、下降或停止的标识枚举
 * @date 2019-08-30
*/
enum AGVLifterControl
{
	// 停止
	Lifter_Ctrl_Stop,
	// 上升开始
	Lifter_Ctrl_Up,
	// 下降开始
	Lifter_Ctrl_Down,
};

/*!
 * @brief 控制AGV辊筒正转、反转或停止的标识枚举
 * @date 2019-08-30
*/
enum AGVRollerControl
{
	// 停止
	Roller_Ctrl_Stop,
	// 正转开始
	Roller_Ctrl_Positive,
	// 反转开始
	Roller_Ctrl_Negative,
};

/*!
 * @brief 描述AGV模式的标识枚举
 * @date 2019-09-03
*/
enum AGVMode
{
	// 离线
	Mode_Offline,
	// 在线
	Mode_Online,
};