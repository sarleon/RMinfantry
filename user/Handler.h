
#ifndef __HANDLER_H
#define __HANDLER_H

#include "Config.h"
#include "stm32f4xx.h"
#include "OSinclude.h"
#include "drv_gui.h"


#ifdef  __HANDLER_GLOBALS
#define __HANDLER_EXT
#else
#define __HANDLER_EXT   extern
#endif


/************************   ���о��    ************************/
__HANDLER_EXT   xQueueHandle    Queue_CANSend;                  //CAN���Ͷ��о��
/************************   ������    ************************/
__HANDLER_EXT   TaskHandle_t    TaskHandle_BellOnce;            //���η�����������
__HANDLER_EXT   TaskHandle_t    TaskHandle_BellCycle;           //ѭ�����������


#if USEESP8266orOLED == 0
__HANDLER_EXT    WidgetTextHandle Oled_Handler;
#endif




#endif
