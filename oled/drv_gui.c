/**
  ******************************************************************************
  * @file    drv_gui.c
  * @author  EC_Dog
  * @version V1.0
  * @date    2016/08/01
  * @brief   
  *   ȫ�����ڻ��㺯������
  ******************************************************************************
  * @attention
  *   �кܶຯ���ǲ���ȫ�ġ�����
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_gui.h"
#include "bsp_oled.h"
#include "stdlib.h"
#include "stdarg.h"
/* Defines -------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/


/**
  * @brief  ����ˮƽ����
  * @param  y:yλ��
  * @param  x0:x��ʼλ��
  * @param  x1:x����λ��
  * @param  isShow: not.�ڣ�is.��
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
*/
void GUI_DrawHLine(uint16_t y,uint16_t x0,uint16_t x1,ISorNOT isShow,ISorNOT isRefresh)
{ 
  for(uint16_t x=x0;x<=x1;x++)
    OLED_DrawPixel(x,y,isShow,isRefresh);
}


/**
  * @brief  ���ƴ�ֱ����
  * @param  x:xλ��
  * @param  y0:y��ʼλ��
  * @param  y1:y����λ��
  * @param  isShow: not.�ڣ�is.��
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
*/
void GUI_DrawVLine(uint16_t x,uint16_t y0,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh)
{
  for(uint16_t y= y0;y<=y1;y++)
    OLED_DrawPixel(x,y,isShow,isRefresh);
}


/**
  * @brief  ��������
  * @param  x0:x��ʼλ�ã�С��
  * @param  y0:y��ʼλ��
  * @param  x1:x����λ�ã���
  * @param  y1:y����λ��
  * @param  isShow: not.�ڣ�is.��
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
*/
void GUI_DrawLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh)
{
  float k = 0;
  float b = 0;
  float fX0 = x0;
  float fX1 = x1;
  float fY0 = y0;
  float fY1 = y1;
  uint16_t x = 0;
  uint16_t y = 0;
  
  k = (fY1-fY0)/(fX1-fX0);
  b = fY1-k*fX1;
  
  for(x=x0;x<=x1;x++)
  {
    y=k*x+b;
    OLED_DrawPixel(x,y,isShow,isRefresh);
  }
}


/**
  * @brief  ���ƾ���
  * @param  x0:x���Ͻ�
  * @param  y0:x���Ͻ�
  * @param  x1:y���½�
  * @param  y1:y���½�
  * @param  isShow: not.�ڣ�is.��
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
*/
void GUI_DrawRect(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh)
{
  GUI_DrawHLine(y0,x0,x1,isShow,isRefresh);
  GUI_DrawHLine(y1,x0,x1,isShow,isRefresh);
  GUI_DrawVLine(x0,y0,y1,isShow,isRefresh);
  GUI_DrawVLine(x1,y0,y1,isShow,isRefresh);
}


/**
  * @brief  ����ʵ�ľ���()
  * @param  x0:x���Ͻ�
  * @param  y0:x���Ͻ�
  * @param  x1:y���½�
  * @param  y1:y���½�
  * @param  isShow: not.�ڣ�is.��
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
*/
void GUI_DrawFullRect(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,ISorNOT isShow,ISorNOT isRefresh)
{
  for(int16_t y=y0;y<=y1;y++)
  {
     GUI_DrawHLine(y,x0,x1,isShow,isRefresh);
  }
}


/**
  * @brief  ��ָ��������ͼƬ���Ե�Ϊ��λһ��һ�д�ӡ
  * @param  x:���Ͻ�x
  * @param  y:���Ͻ�y
  * @param  bmp:ͼƬ��Ϣ
  * @param  InvSW:��ת����
  * @retval None
*/
void GUI_DrawBmp(int16_t x, int16_t y, BmpInfoStructTypedDef* bmpInfo, InvChoose InvSW)
{
  
  int16_t begX=x<0?0:x;       //��ʼ
  int16_t begY=y<0?0:y;
  int16_t begXCnt=x<0?0-x:0;
  int16_t begYCnt=y<0?0-y:0;
  
  int16_t posX=begX, posY=begY;
  uint16_t xCnt, yCnt;
  uint8_t bitShow;   //��ʾ
  for(xCnt=begXCnt; xCnt<bmpInfo->width; xCnt++,posX++)
  {
    for(yCnt=begYCnt,posY=begY; yCnt<bmpInfo->height; yCnt++,posY++)
    {
      if(InvSW==INV_OFF)
      {
        bitShow = (*(bmpInfo->pBmp+xCnt+(yCnt/8)*bmpInfo->width)>>(yCnt%8))&0x01;
      }
      else
      {
        bitShow = !((*(bmpInfo->pBmp+xCnt+(yCnt/8)*bmpInfo->width)>>(yCnt%8))&0x01);
      }
      OLED_DrawPixel(posX,posY,(ISorNOT)bitShow,NOT);
    }
  }
}


/***************************************************************
  * ͼƬ�ؼ� begin
****************************************************************/
/**
  * @brief  ����ͼƬ��ʾ�ؼ�
  * @param  x:���Ͻ�x
  * @param  y:���Ͻ�y
  * @param  hSize:ˮƽ���
  * @param  vSize:��ֱ�߶�
  * @retval WidgetImageHandle:�ؼ����
*/
WidgetImageHandle GUI_WidgetImage_Create(uint16_t x, uint16_t y, uint16_t hSize, uint16_t vSize)
{
  WidgetImageHandle handle;
  
  //�ؼ���ʼ��
  handle = malloc(sizeof(*handle));
  handle->x = x;
  handle->y = y;
  handle->hSize = hSize;
  handle->vSize = vSize;
  
  return handle;
}


/**
  * @brief  ���ÿؼ���ӦͼƬ
  * @param  pBmpInfo:ָ��ͼƬ��Ϣ��ָ��
  * @param  handle:�ؼ����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetImage_SetBmp(WidgetImageHandle handle, BmpInfoStructTypedDef* bmpInfo)
{
  if(handle != NULL)
  {
    handle->imageInfo = bmpInfo;
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}


/**
  * @brief  ����ͼƬ�ؼ���С
  * @param  handle:�ؼ����
  * @param  hSize:ˮƽ���
  * @param  vSize:��ֱ�߶�
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetImage_SetHV(WidgetImageHandle handle, uint16_t hSize, uint16_t vSize)
{
  handle->hSize = hSize;
  handle->vSize = vSize;
  
  if(handle != NULL)
  {
    handle->hSize = hSize;
    handle->vSize = vSize;
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}


/**
  * @brief  ͼƬ�ؼ���ʾ
  * @param  handle:�ؼ����
  * @param  isShow:�Ƿ���ʾ
  * @param  isRefresh: not.��ֱ����ʾ��oled;is.����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetImage_Show(WidgetImageHandle handle, ISorNOT isShow, ISorNOT isRefresh)
{
  if(handle!=NULL && handle->imageInfo!=NULL)
  {
    if(isShow == IS)
    {
      OLED_DrawBmp(handle->x,handle->y,handle->hSize,handle->vSize,handle->imageInfo, INV_OFF);
    }
    else
    {
      GUI_DrawFullRect(handle->x,handle->y,handle->x+handle->hSize-1,handle->y+handle->vSize-1,isShow,isRefresh);
    }
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}
/***************************************************************
  * ͼƬ�ؼ� end
****************************************************************/


/***************************************************************
  * �ı��ؼ� begin(Test OK)
****************************************************************/
/**
  * @brief  �����ı��ؼ�
  * @param  x:���Ͻ�x
  * @param  y:���Ͻ�y
  * @param  hSize:ˮƽ���
  * @param  vSize:��ֱ�߶�
  * @retval WidgetTextHandle:�ؼ����
*/
WidgetTextHandle GUI_WidgetText_Create(uint16_t x, uint16_t y, uint16_t hSize, uint16_t vSize)
{
  WidgetTextHandle handle;
  handle = malloc(sizeof(*handle));
  handle->x = x,
  handle->y = y,
  
  handle->hSize = hSize;
  handle->vSize = vSize;
  return handle;
}


/**
  * @brief  Ϊ�ı�������ı�
  * @param  handle:�ؼ����
  * @param  fmt:�ı�  \n�����Ի��С�����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetText_AddText(WidgetTextHandle handle, void* fmt, ...)
{
  if(handle != NULL)
  {
    uint8_t oledBuf[256];
    int16_t newLen;   //����ӵ����ݳ���
    int16_t oldLen;   //ԭʼ���ݳ���
    uint8_t* tmpPText;
    va_list ap;
    
    if(handle->pText != NULL)
    {
      oldLen = strlen((char*)handle->pText);
    }
    
    va_start(ap,fmt);
    newLen = vsnprintf((char*)oledBuf, 256, (char*)fmt, ap);
    va_end(ap);
    
    if(newLen<0)
    {
      return GUI_FAILED;
    }
    else
    {
      tmpPText = handle->pText;
      handle->pText = malloc(newLen+oldLen+1);
      if(handle->pText!=NULL)
      {
        strcpy((char*)(handle->pText), (char*)tmpPText);
        free(tmpPText);
        strcpy((char*)(handle->pText+oldLen), (char*)oledBuf);
        return GUI_SUCCESS;
      }
      else//����ʧ��
      {
        handle->pText = tmpPText;
        return GUI_FAILED;
      }
    }
  }
  else
  {
    return GUI_FAILED;
  }
}


/**
  * @brief  ���ÿؼ���Ӧ�ı�
  * @param  handle:�ؼ����
  * @param  fmt:�ı�  \n�����Ի��С�����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetText_SetText(WidgetTextHandle handle, void* fmt, ...)
{
  if(handle != NULL)
  {
    uint8_t oledBuf[256];
    int16_t newLen;
    va_list ap;
    
    if(handle->pText != NULL)
    {
      free(handle->pText);
      handle->pText = NULL;
    }
    
    va_start(ap,fmt);
    newLen = vsnprintf((char*)oledBuf, 256, (char*)fmt, ap);
    va_end(ap);
    
    if(newLen<0)
    {
      return GUI_FAILED;
    }
    else
    {
      handle->pText = malloc(newLen+1);
      if(handle->pText!=NULL)
      {
        strcpy((char*)(handle->pText), (char*)oledBuf);
//        for(uint16_t i=0;i<newLen;i++)
//        {
//          *(handle->pText+i) = oledBuf[i];
//        }
        return GUI_SUCCESS;
      }
      else
      {
        return GUI_FAILED;
      }
    }
  }
  else
  {
    return GUI_FAILED;
  }
}

/**
  * @brief  isShowRim����
  * @param  handle:�ؼ����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetText_SetRim(WidgetTextHandle handle,ISorNOT isShowRim)
{
  if(handle!=NULL)
  {
    handle->isShowRim = isShowRim;
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}


/**
  * @brief  �ı��ؼ���ʾ
  * @param  handle:�ؼ����
  * @param  isShow:�Ƿ���ʾ�ı�
  * @param  isRefresh: not.��ֱ����ʾ��oled;is.����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetText_Show(WidgetTextHandle handle, ISorNOT isShow, ISorNOT isRefresh)
{
  if(handle!=NULL)
  {
    uint16_t x1 = handle->x+handle->hSize-1;
    uint16_t y1 = handle->y+handle->vSize-1;
    
    //����ߵĿ�
    if(handle->isShowRim == IS)
      GUI_DrawRect(handle->x,handle->y,x1,y1,IS,isRefresh);
    else
      GUI_DrawRect(handle->x,handle->y,x1,y1,NOT,isRefresh);
    //�ڲ�Ŀ�
    GUI_DrawRect(handle->x+1,handle->y+1,x1-1,y1-1,NOT,isRefresh);
    
    if(handle->pText!=NULL && handle->hSize>=2 && handle->vSize>=2)
    {
      if(isShow == IS)
        OLED_Print6x8Str(handle->x+2,handle->y+2,handle->hSize-4,handle->vSize-4,
              handle->pText,INV_OFF,isRefresh);
      else
        GUI_DrawFullRect(handle->x+2,handle->y+2,x1-2,y1-2,NOT,isRefresh);
    }
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}
/***************************************************************
  * �ı��ؼ� end
****************************************************************/


/***************************************************************
  * �������ؼ� begin
****************************************************************/
/**
  * @brief  �����������ؼ�
  * @param  x:���Ͻ�x
  * @param  y:���Ͻ�y
  * @param  hSize:ˮƽ���
  * @param  vSize:��ֱ�߶�(������)
  * @param  value:ֵ����
  * @param  form:0.��ʽ0��1.��ʽ1
  * @param  isShowValue:
  * @retval WidgetProgBarHandle:�ؼ����
*/
WidgetProgBarHandle GUI_WidgetProgBar_Create(uint16_t x, uint16_t y, int32_t miniMum,int32_t maxiMum,\
      uint16_t hSize, float value, uint8_t form, ISorNOT isShowValue)
{
  WidgetProgBarHandle handle;
  handle = malloc(sizeof(*handle));
  
  handle->x = x,
  handle->y = y,
  handle->miniMum = miniMum;
  handle->maxiMum = miniMum<=maxiMum?maxiMum:miniMum;
  handle->value = miniMum;
  handle->hSize = hSize;
  handle->vSize = 14;
  GUI_WidgetProgBar_SetVal(handle, value);
  handle->form = form;
  handle->isShowValue = isShowValue;
  
  return handle;
}


/**
  * @brief  valueֵ����
  * @param  handle:�ؼ����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetProgBar_SetVal(WidgetProgBarHandle handle, float value)
{
  if(handle!=NULL)
  {
    if(value<handle->miniMum)
      handle->value = handle->miniMum;
    else if(value>handle->maxiMum)
      handle->value = handle->maxiMum;
    else
      handle->value = value;
    
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}


/**
  * @brief  �������ؼ���ʾ
  * @param  handle:�ؼ����
  * @param  isShow:�Ƿ���ʾ�ؼ�
  * @param  isRefresh: not.��ֱ����ʾ��oled;is.����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetProgBar_Show(WidgetProgBarHandle handle, ISorNOT isShow, ISorNOT isRefresh)
{
  if(handle != NULL)
  {
    uint16_t x1 = handle->x + handle->hSize -1;
    uint16_t y1 = handle->y + handle->vSize -1;
    float percent = (handle->value-handle->miniMum)/(float)(handle->maxiMum-handle->miniMum);
    
    //��ո�Ƭ����
    GUI_DrawFullRect(handle->x,handle->y,x1,y1,NOT,isRefresh);
    if(isShow == IS)
    {
      if(handle->form == 0)
      {
        uint16_t width = handle->hSize - 2;
        uint16_t showX = (uint16_t)((float)(width-2)*percent);
        GUI_DrawFullRect(handle->x+1,handle->y+2,x1-1,handle->y+3,IS,isRefresh);
        GUI_DrawFullRect(handle->x+1+showX,handle->y+1,handle->x+2+showX,handle->y+4,IS,isRefresh);
      }
      else if(handle->form == 1)
      {
        uint16_t width = handle->hSize - 2;
        uint16_t showX = (uint16_t)((float)(width-2)*percent);
        GUI_DrawRect(handle->x+1,handle->y+1,x1-1,handle->y+4,IS,isRefresh);
        GUI_DrawFullRect(handle->x+1,handle->y+2,handle->x+1+showX,handle->y+3,IS,isRefresh);
      }
      
      if(handle->isShowValue == IS)
      {
        uint8_t* pText = OLED_TextPrint("*Val:%3.2f",handle->value);
        OLED_Print6x8Str(handle->x+1,handle->y+6,handle->hSize-2,8,pText,INV_OFF,isRefresh);
        free(pText);
      }
    }
    
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}
/***************************************************************
  * �������ؼ� end
****************************************************************/


/***************************************************************
  * checkBox�ؼ� begin
****************************************************************/
/**
  * @brief  ����checkbox�ؼ�
  * @param  x:���Ͻ�x
  * @param  y:���Ͻ�y
  * @param  hSize:ˮƽ���
  * @param  vSize:��ֱ�߶�(������)
  * @param  checked:�Ƿ�ѡ��
  * @param  pText:�ؼ��ı�ָ��
  * @retval WidgetCheckBoxHandle:�ؼ����
*/
WidgetCheckBoxHandle GUI_WidgetCheckBox_Create(uint16_t x, uint16_t y,\
      uint16_t hSize, TorF_EmTypeDef checked, void* pText)
{
  WidgetCheckBoxHandle handle;
  handle = malloc(sizeof(*handle));
  
  handle->x = x,
  handle->y = y,

  handle->hSize = hSize;
  handle->vSize = 12;
  handle->checked = checked;
  handle->pText = pText;
  
  return handle;
}

/**
  * @brief  checkedֵ����
  * @param  handle:�ؼ����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetCheckBox_SetVal(WidgetCheckBoxHandle handle,TorF_EmTypeDef checked)
{
  if(handle!=NULL)
  {
    handle->checked = checked;
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}

/**
  * @brief  textInvֵ����
  * @param  handle:�ؼ����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetCheckBox_SetTextInv(WidgetCheckBoxHandle handle,InvChoose textInv)
{
  if(handle!=NULL)
  {
    handle->textInv = textInv;
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}

/**
  * @brief  checkbox�ؼ���ʾ
  * @param  handle:�ؼ����
  * @param  isShow:�Ƿ���ʾ
  * @param  isRefresh: not.��ֱ����ʾ��oled;is.����
  * @retval GUI_State_EmTypedef
*/
GUI_State_EmTypedef GUI_WidgetCheckBox_Show(WidgetCheckBoxHandle handle, ISorNOT isShow, ISorNOT isRefresh)
{
  if(handle != NULL)
  {
    uint16_t x1 = handle->x+handle->hSize-1;
    uint16_t y1 = handle->y+handle->vSize-1;
    GUI_DrawFullRect(handle->x,handle->y,x1,y1,NOT,isRefresh);
    if(isShow == IS)
    {
      GUI_DrawRect(handle->x+1,handle->y+1,handle->x+handle->vSize-2,y1-1,IS,isRefresh);
      if(handle->checked == IS)
      {
        GUI_DrawFullRect(handle->x+3,handle->y+3,handle->x+handle->vSize-4,y1-3,IS,isRefresh);
      }
      if(handle->textInv == INV_ON)
        GUI_DrawHLine(y1-9,handle->x+handle->vSize+1,x1,IS,isRefresh);
      
      OLED_Print6x8Str(handle->x+handle->vSize+1,y1-8,handle->hSize-3-(handle->vSize-2),8,\
              handle->pText,handle->textInv,isRefresh);
    }
    return GUI_SUCCESS;
  }
  else
  {
    return GUI_FAILED;
  }
}
/***************************************************************
  * checkBox�ؼ� end
****************************************************************/


/***************************************************************
  * MessageBox�ؼ� begin
****************************************************************/
//һ�������TextBox............................
/***************************************************************
  * MessageBox�ؼ� end
****************************************************************/

/**
  * @brief  �ؼ�����
  * @param  widget:�ؼ����
  * @retval None
*/
void GUI_WidgetDestroy(WidgetTypeDef* widget)
{
  free((void*)widget->handle);
  widget->handle = 0;
}

/**
  * @brief  �ؼ�������ʾ
  * @param  widgets:�ؼ����
  * @param  num:�ؼ�����
  * @param  isRefresh: not.��ֱ����ʾ��oled;is.����
  * @retval GUI_State_EmTypedef
*/
void GUI_WidgetFresh(WidgetTypeDef* widgets, uint16_t num, ISorNOT isRefresh)
{
  WidgetTypeDef* pTmpWidget;
  for(uint16_t i=0;i<num;i++)
  {
    pTmpWidget = widgets+i;
    switch(pTmpWidget->type)
    {
      case WIDGET_IMAGE:
        GUI_WidgetImage_Show((WidgetImageHandle)pTmpWidget->handle, IS, isRefresh);
        break;
      case WIDGET_TEXT:
        GUI_WidgetText_Show((WidgetTextHandle)pTmpWidget->handle, IS, isRefresh);
        break;
      case WIDGET_PROGBAR:
        GUI_WidgetProgBar_Show((WidgetProgBarHandle)pTmpWidget->handle, IS, isRefresh);
        break;
      case WIDGET_CHECKBOX:
        GUI_WidgetCheckBox_Show((WidgetCheckBoxHandle)pTmpWidget->handle, IS, isRefresh);
        break;
    }
  }
}
