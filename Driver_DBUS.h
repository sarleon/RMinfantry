#ifndef __DRIVER_DBUS_H
#define __DRIVER_DBUS_H


#include "stm32f4xx.h"
#include "OSinclude.h"


//DBUS��������֡����
#define DBUSLength		18				//DBUS����֡��
#define DBUSBackLength	1				//����һ���ֽڱ����ȶ�

					
#define KEY_V		0x4000
#define KEY_C		0x2000
#define KEY_X		0x1000
#define KEY_Z		0x0800
#define KEY_G		0x0400
#define KEY_F		0x0200
#define KEY_R		0x0100
#define KEY_E		0x0080
#define KEY_Q		0x0040
#define KEY_CTRL	0x0020
#define KEY_SHIFT	0x0010
#define KEY_D		0x0008
#define KEY_A		0x0004
#define KEY_S		0x0002
#define KEY_W		0x0001



//ң�ؽ������ݴ洢�ṹ��
typedef struct {
	int16_t ch1;	//each ch value from -660 -- +660
	int16_t ch2;
	int16_t ch3;
	int16_t ch4;
	
	uint8_t switch_left;	//3 value
	uint8_t switch_right;
	
	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
	
		uint8_t press_left;
		uint8_t press_right;
        
        uint8_t jumppress_left;
        uint8_t jumppress_right;
	}mouse;
	
	struct 
	{
/**********************************************************************************
   * ����ͨ��:15   14   13   12   11   10   9   8   7   6     5     4   3   2   1
   *          V    C    X	  Z    G    F    R   E   Q  CTRL  SHIFT  D   A   S   W
************************************************************************************/
		uint16_t key_code;              //ԭʼ��ֵ
        uint16_t jumpkey_code;          //�����ļ�ֵ
	}keyBoard;
}DBUSDecoding_Type;

//DBUS��ң������״̬
typedef enum
{
	Fine,
	Medium,
	Bad,
	Lost
}DBUSConnectStatus_Type;


#ifdef  __DBUS_GLOBALS
#define __DBUS_EXT
#else
#define __DBUS_EXT extern
#endif


__DBUS_EXT uint8_t DBUSBuffer[DBUSLength + DBUSBackLength];				//DBUS,DMA���ջ���
__DBUS_EXT DBUSDecoding_Type DBUS_ReceiveData, LASTDBUS_ReceiveData;			//DBUS����������
__DBUS_EXT uint8_t DBUSFrameCounter;					//DBUS֡����
__DBUS_EXT uint8_t DBUSFrameRate;					    //DBUS֡��
__DBUS_EXT DBUSConnectStatus_Type DBUSConnectStatus;	//DBUS����״̬


void DBUS_InitConfig(void);
void DBUS_DataDecoding(void);
void DBUS_ButtonCheckJump(portTickType CurrentTick);
uint8_t DBUS_CheckPush(uint16_t Key);
uint8_t DBUS_CheckJumpKey(uint16_t Key);
uint8_t DBUS_CheckJumpMouse(uint8_t Key);


#endif
