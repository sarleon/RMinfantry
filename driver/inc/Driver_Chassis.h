

#ifndef __DRIVER_CHASSIS_H
#define __DRIVER_CHASSIS_H

#include "Config.h"
#include "OSinclude.h"
#include "stm32f4xx.h"


#if MOTORTYPE == 1
#define CURRENTCONTROLCANID             0x35        //��3510���͵�����ID��
#endif

#define BASECHASSISCONTROLCANID         0x303

#define LFCHASSISCONTROLCANID           0x75
#define MaxWheelSpeed                   900
#define ChassisLimitCurrent             2750            //���̵������Ƽ���
#define MOUSEINTLIMIT                   0.9F        //�����ת�ٶ����ޣ��������תʱ�����ٶȸ��������С��ֵ


//���̵��CANID
#if MOTORTYPE == 1
#define LFCHASSISCANID                  0x201
#define RFCHASSISCANID                  0x202
#define LBCHASSISCANID                  0x203
#define RBCHASSISCANID                  0x204
#else
#define LFCHASSISCANID                  0x41
#define RFCHASSISCANID                  0x42
#define LBCHASSISCANID                  0x43
#define RBCHASSISCANID                  0x44
#endif

//���̵���ٶȿ���
#define CHASSISSPEEDSETCANID            0x46
//3510���̵������վģʽ
#define CHASSISSUPPLYSPEEDSETCANID      0x155
//���̵����������
#define CHASSISCURRENTSETCANID          0x40


#if INFANTRY == 6
#define CHASSISMAXPOWER                 9999.0F       //���������
#else
#define CHASSISMAXPOWER                 80.0F       //���������
#endif


#ifdef  __DRIVER_CHASSIS_GLOBALS
#define __DRIVER_CHASSIS_EXT
#else
#define __DRIVER_CHASSIS_EXT extern
#endif


//�ٶ�ö��
typedef enum
{
    ChassisSpeedLevel_Hight,
    ChassisSpeedLevel_Low
}ChassisSpeedLevel_Enum;


//���������
typedef struct
{
    int16_t TargetSpeed;             //���Ŀ���ٶ�
    int16_t RealSpeed;               //���ʵ���ٶ�
    uint16_t LimitCurrent;           //���Ƶ���
    uint16_t RealCurrent;            //ʵ�ʵ���
    uint16_t NeedCurrent;            //�������
}OneMotorParam_Struct;


//���̵�������ṹ��
typedef struct
{
    OneMotorParam_Struct LF;
    OneMotorParam_Struct RF;
    OneMotorParam_Struct LB;
    OneMotorParam_Struct RB;
    ChassisSpeedLevel_Enum SpeedLevel;
    float TargetVX;
    float TargetVY;
    float TargetOmega;
    float TargetABSAngle;
}ChassisParam_Struct;


//��������ܵ�������
__DRIVER_CHASSIS_EXT float ChassisMaxSumCurrent;   
//���״̬
__DRIVER_CHASSIS_EXT ChassisParam_Struct ChassisParam;    
//���̵��֡������
__DRIVER_CHASSIS_EXT uint16_t ChassisFrameCounter[4];   
//���̵��֡������
__DRIVER_CHASSIS_EXT uint16_t ChassisFrameRate[4];  



void Chassis_InitConfig(void);
void Chassis_SpeedSet(float XSpeed, float YSpeed);
void Chassis_TargetDirectionSet(float Target);
void Chassis_Adjust(uint8_t mode,uint8_t supply);
void Chassis_SendMotorParam(uint8_t mode,uint8_t supply);
static void MecanumCalculate(float Vx, float Vy, float Omega, int16_t *Speed);

#if MOTORTYPE == 0
void Chassis_MotorDebug(void);
#endif

void Chassis_BaseControl(uint8_t mode, float Target);


#endif
