
#define __DRIVER_CHASSIS_GLOBALS

#include "Config.h"
#include "Handler.h"
#include "OSinclude.h"
#include "CommonDataStructure.h"
#include "Task_CANSend.h"
#include "Driver_Judge.h"
#include "Driver_Chassis.h"
#include "Driver_Control.h"
#include "Driver_CloudMotor.h"
#include "Driver_SuperGyroscope.h"

#include "Driver_DBUS.h"


/**
  * @brief  ���̳�ʼ��
  * @param  void 
  * @retval void
  */
void Chassis_InitConfig(void)
{
    ChassisMaxSumCurrent = 2380.0F;
    
    ChassisParam.TargetVX = 0;
    ChassisParam.TargetVY = 0;
    ChassisParam.TargetOmega = 0;
    ChassisParam.TargetABSAngle = 0;
    ChassisParam.SpeedLevel = ChassisSpeedLevel_Hight;
    
    for(int i = 0; i < 4; i++)
    {
        ChassisFrameCounter[i] = 0;
        ChassisFrameRate[i] = 0;
    }
}


#if INFANTRY == 7


#else


/**
  * @brief  XY�����ٶ�����
  * @param  X�ٶ�
  * @param  Y�ٶ�
  * @retval void
  */
void Chassis_SpeedSet(float XSpeed, float YSpeed)
{
    XSpeed = XSpeed > MaxWheelSpeed? MaxWheelSpeed : XSpeed;
    XSpeed = XSpeed < -MaxWheelSpeed ? -MaxWheelSpeed : XSpeed;
    
    YSpeed = YSpeed > MaxWheelSpeed ? MaxWheelSpeed : YSpeed;
    YSpeed = YSpeed < -MaxWheelSpeed ? -MaxWheelSpeed : YSpeed;
    
    ChassisParam.TargetVX = XSpeed;
    ChassisParam.TargetVY = YSpeed;
}


/**
  * @brief  ����Ŀ��Ƕ�����
  * @param  Ŀ��Ƕ�
  * @retval void
  */
void Chassis_TargetDirectionSet(float Target)
{
    ChassisParam.TargetABSAngle = Target;
}


/**
  * @brief  ���̵���
  * @param  1 ��������          0 ����ֹͣ 
  * @param  1 �����ͷ�          0 ��������  
  * @retval void
  */
void Chassis_Adjust(uint8_t mode,uint8_t supply)
{
    int16_t WheelSpeed[4];
    
#if MOTORTYPE == 0
    int16_t PowerSum;
    int16_t ABSSpeed[4];
#endif
    
    //����վģʽ�����нǶȱջ�
    if(!supply)
    {
        Control_ChassisPID();
    }
    
    //���ֽ���
    MecanumCalculate(ChassisParam.TargetVX, ChassisParam.TargetVY, ChassisParam.TargetOmega, WheelSpeed);
    
    ChassisParam.LF.TargetSpeed = WheelSpeed[0];
    ChassisParam.RF.TargetSpeed = WheelSpeed[1];
    ChassisParam.LB.TargetSpeed = WheelSpeed[2];
    ChassisParam.RB.TargetSpeed = WheelSpeed[3];

//35�����Ҫ���ж�̬��������
#if MOTORTYPE == 0
    ABSSpeed[0] = (ChassisParam.LF.NeedCurrent > 0 ? ChassisParam.LF.NeedCurrent : -ChassisParam.LF.NeedCurrent);
    ABSSpeed[1] = (ChassisParam.RF.NeedCurrent > 0 ? ChassisParam.RF.NeedCurrent : -ChassisParam.RF.NeedCurrent);
    ABSSpeed[2] = (ChassisParam.LB.NeedCurrent > 0 ? ChassisParam.LB.NeedCurrent : -ChassisParam.LB.NeedCurrent);
    ABSSpeed[3] = (ChassisParam.RB.NeedCurrent > 0 ? ChassisParam.RB.NeedCurrent : -ChassisParam.RB.NeedCurrent);
    
    //���ʷ���
    PowerSum = ABSSpeed[0] + ABSSpeed[1] + ABSSpeed[2] + ABSSpeed[3];
    
    if(PowerSum > 0)
    {
        ChassisParam.LF.LimitCurrent = ChassisMaxSumCurrent * ABSSpeed[0] / PowerSum;
        ChassisParam.RF.LimitCurrent = ChassisMaxSumCurrent * ABSSpeed[1] / PowerSum;
        ChassisParam.LB.LimitCurrent = ChassisMaxSumCurrent * ABSSpeed[2] / PowerSum;
        ChassisParam.RB.LimitCurrent = ChassisMaxSumCurrent * ABSSpeed[3] / PowerSum;
    }
    else
    {
        ChassisParam.LF.LimitCurrent = ChassisMaxSumCurrent / 4;
        ChassisParam.RF.LimitCurrent = ChassisMaxSumCurrent / 4;
        ChassisParam.LB.LimitCurrent = ChassisMaxSumCurrent / 4;
        ChassisParam.RB.LimitCurrent = ChassisMaxSumCurrent / 4;
    }
#endif
    
    Chassis_SendMotorParam(mode, supply);
}


/**
  * @brief  �����ٶ������Ƶ���
  * @param  ģʽ  1 �������ݽṹ�е�Ŀ���ٶ������Ƶ���     0 �����ٶ������Ƶ���Ϊ0�����ڽ���ͣ����
  * @param  ����վģʽ  1 ʹ�ò���վģʽ�������ͷ�     0 ��ʹ�ò���վģʽ
  * @retval void
  */
void Chassis_SendMotorParam(uint8_t mode,uint8_t supply)
{
    static  CanSend_Type   SendData;
    
#if MOTORTYPE == 1
    FormatTrans FT;
#endif
    
#if CANPORT == 1
    SendData.CANx = 1;
#else
    SendData.CANx = 2;
#endif
    
    SendData.SendCanTxMsg.DLC   =   8;
    SendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
    SendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
    
#if MOTORTYPE == 1
    if(supply)
    {
        SendData.SendCanTxMsg.StdId =   CHASSISSUPPLYSPEEDSETCANID;
    }
    else
    {
        SendData.SendCanTxMsg.StdId =   CHASSISSPEEDSETCANID;
    }
#else
    SendData.SendCanTxMsg.StdId =   CHASSISSPEEDSETCANID;
#endif
    
    if(mode)
    {
        //Ŀ���ٶ�
        SendData.SendCanTxMsg.Data[1] = ChassisParam.LF.TargetSpeed >> 8;
        SendData.SendCanTxMsg.Data[0] = ChassisParam.LF.TargetSpeed;
        SendData.SendCanTxMsg.Data[3] = ChassisParam.RF.TargetSpeed >> 8;
        SendData.SendCanTxMsg.Data[2] = ChassisParam.RF.TargetSpeed;
        SendData.SendCanTxMsg.Data[5] = ChassisParam.LB.TargetSpeed >> 8;
        SendData.SendCanTxMsg.Data[4] = ChassisParam.LB.TargetSpeed;
        SendData.SendCanTxMsg.Data[7] = ChassisParam.RB.TargetSpeed >> 8;
        SendData.SendCanTxMsg.Data[6] = ChassisParam.RB.TargetSpeed;
        xQueueSend(Queue_CANSend, &SendData, 10);
        
        
//3510����Ҫ������ʵ�ʵ����������Ƶ���
#if MOTORTYPE == 1
        SendData.SendCanTxMsg.StdId =   CURRENTCONTROLCANID;
        //ʵ�ʵ���
        if(JudgeFrameRate < 10)         //����ϵͳ���߷�0
        {
            FT.F = 0;
        }
        else
        {
            FT.F = InfantryJudge.RealCurrent * 1000.0F;     //��λת��ΪA
        }
        SendData.SendCanTxMsg.Data[0] = FT.U[0];
        SendData.SendCanTxMsg.Data[1] = FT.U[1];
        SendData.SendCanTxMsg.Data[2] = FT.U[2];
        SendData.SendCanTxMsg.Data[3] = FT.U[3];
        
        //���Ƶ���
        FT.F = ChassisMaxSumCurrent;
        SendData.SendCanTxMsg.Data[4] = FT.U[0];
        SendData.SendCanTxMsg.Data[5] = FT.U[1];
        SendData.SendCanTxMsg.Data[6] = FT.U[2];
        SendData.SendCanTxMsg.Data[7] = FT.U[3];
        
        xQueueSend(Queue_CANSend, &SendData, 10);
        
#else   //35���Ҫ���͵�������Ƶ���
        SendData.SendCanTxMsg.StdId =   CHASSISCURRENTSETCANID;
        SendData.SendCanTxMsg.Data[1] = ChassisParam.LF.LimitCurrent >> 8;
        SendData.SendCanTxMsg.Data[0] = ChassisParam.LF.LimitCurrent;
        SendData.SendCanTxMsg.Data[3] = ChassisParam.RF.LimitCurrent >> 8;
        SendData.SendCanTxMsg.Data[2] = ChassisParam.RF.LimitCurrent;
        SendData.SendCanTxMsg.Data[5] = ChassisParam.LB.LimitCurrent >> 8;
        SendData.SendCanTxMsg.Data[4] = ChassisParam.LB.LimitCurrent;
        SendData.SendCanTxMsg.Data[7] = ChassisParam.RB.LimitCurrent >> 8;
        SendData.SendCanTxMsg.Data[6] = ChassisParam.RB.LimitCurrent;
        xQueueSend(Queue_CANSend, &SendData, 10);
#endif
    }
    else
    {
        
#if MOTORTYPE == 1
        //3510��������Ͷ���
#else
        //Ŀ���ٶ�ȫ������
        SendData.SendCanTxMsg.StdId =   CHASSISSPEEDSETCANID;
        SendData.SendCanTxMsg.Data[0] = 0;
        SendData.SendCanTxMsg.Data[1] = 0;
        SendData.SendCanTxMsg.Data[2] = 0;
        SendData.SendCanTxMsg.Data[3] = 0;
        SendData.SendCanTxMsg.Data[4] = 0;
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
        xQueueSend(Queue_CANSend, &SendData, 10);
        
        SendData.SendCanTxMsg.StdId =   CHASSISCURRENTSETCANID;
        SendData.SendCanTxMsg.Data[0] = 0;
        SendData.SendCanTxMsg.Data[1] = 0;
        SendData.SendCanTxMsg.Data[2] = 0;
        SendData.SendCanTxMsg.Data[3] = 0;
        SendData.SendCanTxMsg.Data[4] = 0;
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
        xQueueSend(Queue_CANSend, &SendData, 10);
#endif
    }
}


#if MOTORTYPE == 0
/**
  * @brief  �������ģʽ������700���ٶ�0
  * @param  void
  * @retval void
  */
void Chassis_MotorDebug(void)
{
    static  CanSend_Type   SendData;
    
#if CANPORT == 1
    SendData.CANx = 1;
#else
    SendData.CANx = 2;
#endif
    
    SendData.SendCanTxMsg.DLC   =   8;
    SendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
    SendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
    
    SendData.SendCanTxMsg.StdId =   CHASSISSPEEDSETCANID;
    SendData.SendCanTxMsg.Data[1] = 0;
    SendData.SendCanTxMsg.Data[0] = 0;
    SendData.SendCanTxMsg.Data[3] = 0;
    SendData.SendCanTxMsg.Data[2] = 0;
    SendData.SendCanTxMsg.Data[5] = 0;
    SendData.SendCanTxMsg.Data[4] = 0;
    SendData.SendCanTxMsg.Data[7] = 0;
    SendData.SendCanTxMsg.Data[6] = 0;
    xQueueSend(Queue_CANSend, &SendData, 10);
    
    SendData.SendCanTxMsg.StdId =   CHASSISCURRENTSETCANID;
    SendData.SendCanTxMsg.Data[1] = /* 02 */ 0;
    SendData.SendCanTxMsg.Data[0] = /* BC */ 0;
    SendData.SendCanTxMsg.Data[3] = /* 02 */ 0;
    SendData.SendCanTxMsg.Data[2] = /* BC */ 0;
    SendData.SendCanTxMsg.Data[5] = /* 02 */ 0;
    SendData.SendCanTxMsg.Data[4] = /* BC */ 0;
    SendData.SendCanTxMsg.Data[7] = /* 02 */ 0;
    SendData.SendCanTxMsg.Data[6] = /* BC */ 0;
    xQueueSend(Queue_CANSend, &SendData, 10);
}
#endif


/**
  * @brief  ���ֽ���
  * @param  x�ٶȣ�ǰ��
  * @param  y�ٶȣ��ң�
  * @param  ���ٶȣ�˳ʱ��Ϊ����
  * @retval void
  */
static void MecanumCalculate(float Vx, float Vy, float Omega, int16_t *Speed)
{
    float Buffer[4], Param, MaxSpeed;
    uint8_t index;
    
    Buffer[0] = Vx + Vy + Omega;
    Buffer[1] = Vx - Vy - Omega;
    Buffer[2] = Vx - Vy + Omega;
    Buffer[3] = Vx + Vy - Omega;
    
    //�޷�
    for(index = 0, MaxSpeed = 0; index < 4; index++)
    {
        if((Buffer[index] > 0 ? Buffer[index] : -Buffer[index]) > MaxSpeed)
        {
            MaxSpeed = (Buffer[index] > 0 ? Buffer[index] : -Buffer[index]);
        }
    }
    if(MaxWheelSpeed < MaxSpeed)
    {
        Param = (float)MaxWheelSpeed / MaxSpeed;
        Speed[0] = Buffer[0] * Param;
        Speed[1] = Buffer[1] * Param;
        Speed[2] = Buffer[2] * Param;
        Speed[3] = Buffer[3] * Param; 
    }
    else
    {
        Speed[0] = Buffer[0];
        Speed[1] = Buffer[1];
        Speed[2] = Buffer[2];
        Speed[3] = Buffer[3];
    }
}


#endif



/**
  * @brief  ����̷���ֹͣ����
  * @param  ģʽ
  * @param  ģʽ����
  * @retval void
  */
void Chassis_BaseControl(uint8_t mode, float Target)
{
    static  CanSend_Type   SendData;
    FormatTrans FT;
    
#if CANPORT == 1
    SendData.CANx = 1;
#else
    SendData.CANx = 2;
#endif
    
    SendData.SendCanTxMsg.DLC   =   8;
    SendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
    SendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
    SendData.SendCanTxMsg.StdId =   BASECHASSISCONTROLCANID;
    
    if(mode == 0)               //���־�ֹ
    {
        SendData.SendCanTxMsg.Data[0] = 0;
        SendData.SendCanTxMsg.Data[1] = 0;
        SendData.SendCanTxMsg.Data[2] = 0;
        SendData.SendCanTxMsg.Data[3] = 0;
        SendData.SendCanTxMsg.Data[4] = 0;
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
    }
    else if(mode == 1)          //����ܣ��ܵ��˺�ת����Ӧ����    
    {
        SendData.SendCanTxMsg.Data[0] = 1;
        SendData.SendCanTxMsg.Data[1] = 0;
        SendData.SendCanTxMsg.Data[2] = 0;
        SendData.SendCanTxMsg.Data[3] = 0;
        SendData.SendCanTxMsg.Data[4] = 0;
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
    }
    else if(mode == 2)          //ת��ָ���Ƕ�
    {
        FT.F = Target;
        
        SendData.SendCanTxMsg.Data[0] = 2;
        SendData.SendCanTxMsg.Data[1] = FT.U[0];
        SendData.SendCanTxMsg.Data[2] = FT.U[1];
        SendData.SendCanTxMsg.Data[3] = FT.U[2];
        SendData.SendCanTxMsg.Data[4] = FT.U[3];
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
    }
    else if(mode == 3)          //����ܣ��ܵ��˺�������
    {
        FT.F = Target;
        
        SendData.SendCanTxMsg.Data[0] = 3;
        SendData.SendCanTxMsg.Data[1] = 0;
        SendData.SendCanTxMsg.Data[2] = 0;
        SendData.SendCanTxMsg.Data[3] = 0;
        SendData.SendCanTxMsg.Data[4] = 0;
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
    }
    
    xQueueSend(Queue_CANSend, &SendData, 10);
}







