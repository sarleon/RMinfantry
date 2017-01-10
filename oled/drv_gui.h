#ifndef __DRV_GUI_H
#define __DRV_GUI_H

#include "stm32f4xx.h"
#include "string.h"
#include "bsp_oled.h"


/** 
  * @brief GUI State
  */ 
typedef enum
{
  GUI_FAILED = 0,
  GUI_SUCCESS = 1,
}GUI_State_EmTypedef;

/** 
  * @brief ͼƬ�ؼ����ݽṹ 
  */  
typedef struct
{
  //�ؼ����Ͻǵ�λ��
  uint16_t x;
  uint16_t y;
  //�ؼ�ˮƽ�ߴ�
  uint16_t hSize;
  //�ؼ���ֱ�ߴ�
  uint16_t vSize;
  //Ҫ��ʾ��ͼƬ����Ϣ
  BmpInfoStructTypedDef* imageInfo;

}*WidgetImageHandle;


/** 
  * @brief �ı��ؼ����ݽṹ 
  */  
typedef struct
{
  //�ؼ����Ͻǵ�λ��
  uint16_t x;
  uint16_t y;
  //�ؼ�ˮƽ�ߴ�
  uint16_t hSize;
  //�ؼ���ֱ�ߴ�
  uint16_t vSize;
  //�������ı���Ϣ
  uint8_t* pText;
  //�Ƿ���ʾ�߿�
  ISorNOT isShowRim;
}*WidgetTextHandle;


/** 
  * @brief �������ؼ����ݽṹ 
  */  
typedef struct
{
  //���������Ͻǵ�λ��
  uint16_t x;
  uint16_t y;
  //������ˮƽ�ߴ�
  uint16_t hSize;
  //��������ֱ�ߴ�
  uint16_t vSize;
  //�ؼ���Сֵ
  int32_t miniMum;
  //�ؼ����ֵ
  int32_t maxiMum;
  //�ؼ���ǰֵ
  float value;
  //��ֵ��ʾ״̬
  ISorNOT isShowValue;
  //��������ʽ
  uint8_t form;
}*WidgetProgBarHandle;


/** 
  * @brief check State
  */ 
typedef enum
{
  FALSE = 0,
  TURE  = 1,
}TorF_EmTypeDef;

/** 
  * @brief checkbox�ؼ����ݽṹ 
  */  
typedef struct
{
  //checkbox�ؼ����Ͻǵ�λ��
  uint16_t x;
  uint16_t y;
  //checkbox�ؼ�ˮƽ�ߴ�
  uint16_t hSize;
  //checkbox�ؼ���ֱ�ߴ�
  uint16_t vSize;
  //�ؼ���ǰ״̬
  TorF_EmTypeDef checked;
  //�ؼ��ı�
  uint8_t* pText;
  //text invChoose
  InvChoose textInv;
}*WidgetCheckBoxHandle;


/** 
  * @brief �ؼ�����ö�� 
  */ 
typedef enum
{
  WIDGET_IMAGE  = 0,
  WIDGET_TEXT,
  WIDGET_PROGBAR,
  WIDGET_CHECKBOX,
}WidgetTypeEmTypeDef;

/** 
  * @brief �ؼ��ṹ 
  */ 
typedef struct
{
  //�ؼ�����
  WidgetTypeEmTypeDef type;
  //�ؼ����
  uint32_t handle;
}WidgetTypeDef;

/**
  * @brief �˵��ṹ
  */ 
typedef struct _menu
{
  //���˵�
  struct _menu*  p_parMenu;
  WidgetTypeDef x;
}menuTypeDef;


void GUI_DrawHLine(uint16_t y,uint16_t x0,uint16_t x1,ISorNOT isShow,ISorNOT isRefresh);
void GUI_DrawVLine(uint16_t x,uint16_t y0,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh);
void GUI_DrawLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh);
void GUI_DrawRect(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh);
void GUI_DrawFullRect(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh);
void GUI_DrawBmp(int16_t x, int16_t y, BmpInfoStructTypedDef* bmpInfo, InvChoose InvSW);

WidgetImageHandle GUI_WidgetImage_Create(uint16_t x, uint16_t y, uint16_t hSize, uint16_t vSize);
GUI_State_EmTypedef GUI_WidgetImage_SetBmp(WidgetImageHandle handle, BmpInfoStructTypedDef* bmpInfo);
GUI_State_EmTypedef GUI_WidgetImage_SetHV(WidgetImageHandle handle, uint16_t hSize, uint16_t vSize);
GUI_State_EmTypedef GUI_WidgetImage_Show(WidgetImageHandle handle, ISorNOT isShow, ISorNOT isRefresh);

WidgetTextHandle GUI_WidgetText_Create(uint16_t x, uint16_t y, uint16_t hSize, uint16_t vSize);
GUI_State_EmTypedef GUI_WidgetText_SetText(WidgetTextHandle handle, void* fmt, ...);
GUI_State_EmTypedef GUI_WidgetText_AddText(WidgetTextHandle handle, void* fmt, ...);
GUI_State_EmTypedef GUI_WidgetText_SetRim(WidgetTextHandle handle,ISorNOT isShowRim);
GUI_State_EmTypedef GUI_WidgetText_Show(WidgetTextHandle handle, ISorNOT isShow, ISorNOT isRefresh);

WidgetProgBarHandle GUI_WidgetProgBar_Create(uint16_t x, uint16_t y, int32_t miniMum,int32_t maxiMum,\
      uint16_t hSize, float value, uint8_t form, ISorNOT isShowValue);
GUI_State_EmTypedef GUI_WidgetProgBar_SetVal(WidgetProgBarHandle handle, float value);
GUI_State_EmTypedef GUI_WidgetProgBar_Show(WidgetProgBarHandle handle, ISorNOT isShow, ISorNOT isRefresh);

WidgetCheckBoxHandle GUI_WidgetCheckBox_Create(uint16_t x, uint16_t y,\
      uint16_t hSize, TorF_EmTypeDef checked, void* pText);
GUI_State_EmTypedef GUI_WidgetCheckBox_SetVal(WidgetCheckBoxHandle handle,TorF_EmTypeDef checked);
GUI_State_EmTypedef GUI_WidgetCheckBox_SetTextInv(WidgetCheckBoxHandle handle,InvChoose textInv);
GUI_State_EmTypedef GUI_WidgetCheckBox_Show(WidgetCheckBoxHandle handle, ISorNOT isShow, ISorNOT isRefresh);

void GUI_WidgetDestroy(WidgetTypeDef* widget);
void GUI_WidgetFresh(WidgetTypeDef* widgets, uint16_t num, ISorNOT isRefresh);

#endif
