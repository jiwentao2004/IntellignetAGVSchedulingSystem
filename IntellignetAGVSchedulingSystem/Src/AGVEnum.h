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
	None,

	// 满载
	Full = 0xFF,
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
	None,

	// 因网络异常,无法发送数据造成的异常
	Linkbreak = -1,

	// 升降杆长时间未升到位或未降下引起的异常
	LifterError = -2,

	// 辊筒或链条长时间未接到货物或未将货物卸下引起的异常
	RollerError = -3,

	// 机械臂动作长时间未执行完成引起的异常
	ArmError = -4,

	// 因长时间无法找到磁条的脱磁异常
	Miss = 1,

	// 因碰撞引起的AGV停止,需要人位处理
	Crash,

	// 因检测路线上的物体,无法继续移动
	Obs,
};

/*!
 * @brief 描述AGV运行状态的枚举
 * @date 2019-08-29
 */
enum AGVStatus
{
	// 待机
	Wait,

	// 停止
	Stop,

	// 运行
	Run,

	// 急停
	Scream,

	// 寻磁
	Find,

	// 非接触避障减速
	ObsDown,

	// 交通管制停止
	Traffic,

	// 休眠 2019-08-30
	Sleep,
};

/*!
 * @brief 描述AGV升降杆状态的枚举
 * @date 2019-08-29
 */
enum AGVLifter
{
	// 落下
	Down,
	// 下落中
	GoingDown,
	// 升起中
	GoingUp,
	// 升起
	Up,
};

/*!
 * @brief 描述AGV辊筒状态的枚举
 * @date 2019-08-30
*/
enum AGVRoller
{
	// 停止
	Stop,
	// 正转中
	Positive,
	// 反转中
	Negative,
};

/*!
 * @brief 描述AGV机械臂状态的枚举
 * @date 2019-08-30
*/
enum AGVArmStatus
{
	// 未执行
	None,
	// 执行中
	Execute,
	// 完成
	Done,
};


/*!
 * @brief 控制AGV升降杆上升、下降或停止的标识枚举
 * @date 2019-08-30
*/
enum AGVLifterControl
{
	// 停止
	Stop,
	// 上升开始
	Up,
	// 下降开始
	Down,
};

/*!
 * @brief 控制AGV辊筒正转、反转或停止的标识枚举
 * @date 2019-08-30
*/
enum AGVRollerControl
{
	// 停止
	Stop,
	// 正转开始
	Positive,
	// 反转开始
	Negative,
};