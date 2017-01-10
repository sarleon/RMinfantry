#ifndef __BSP_OLED_H
#define __BSP_OLED_H

#include "stm32f4xx.h"


/** 
  * @brief  Bmp structures definition
  */
typedef __packed struct __BmpInfo
{
  uint16_t width;
  uint16_t height;
  const uint8_t* pBmp;
}BmpInfoStructTypedDef;


/** 
  * @brief  ��ת����
  */
typedef enum
{
	INV_OFF = 0,
	INV_ON  = 1,
}InvChoose;


/** 
  * @brief  �� �� ��
  */
typedef enum
{
	NOT = 0,
	IS  = 1,
}ISorNOT;



void OLED_SetPositionInPage(uint8_t x, uint8_t y);
void OLED_Init(void);


void OLED_DrawPixel(uint8_t x, uint8_t y, ISorNOT isShow, ISorNOT isRefresh);
void OLED_RefreshGram(void);
//void OLED_DrawBmp(uint16_t x, uint16_t y, BmpInfoStructTypedDef* bmpInfo, InvChoose InvSW);
void OLED_DrawSomeBits(int16_t x, int16_t y, uint8_t wrtData, uint8_t effBits, \
        InvChoose InvSW, ISorNOT isRefresh);
void OLED_DrawBmp(int16_t x, int16_t y, uint16_t showW, uint16_t showH, \
        BmpInfoStructTypedDef* bmpInfo, InvChoose InvSW);
void OLED_Print6x8Str(int16_t x,int16_t y,uint16_t showW,uint16_t showH,
        uint8_t* pWrtData,InvChoose InvSW,ISorNOT isRefresh);
uint8_t* OLED_TextPrint(void* fmt, ...);
void OLED_Clear(void);


#endif


///**
//  * @brief  ��ָ��������ͼƬ(ͬʱ���µ��Դ�)
//  * @param  x:���Ͻ�x
//  * @param  y:���Ͻ�y
//  * @param  bmp:ͼƬ��Ϣ
//  * @param  None
//*/
//void OLED_DrawBmp(uint16_t x, uint16_t y, BmpInfoStructTypedDef* bmpInfo, InvChoose InvSW)
//{
//  uint8_t firstBitExc = y%8;                    //��һ��λƫ��(0-7)
//  uint8_t endBitExc = (y+bmpInfo->height)%8+1;  //���һ��λƫ��(0-7)
//  uint16_t firstPage = y/8;                     //��ʵ����ʼҳ��ַ
//  uint16_t endPage = (y+bmpInfo->height)/8;     //��ʵ�Ľ���ҳ��ַ
//  uint16_t drawEndPage;                         //���Ľ���ҳ
//  uint16_t xBeginPos = x;                       //��ʼxλ��(0-127)
//  uint16_t xEndPos = x+bmpInfo->width-1;        //����xλ��(0-127)
//  
//  //���Ʒ�Χ
//  drawEndPage = endPage>=OLED_PAGE?(OLED_PAGE-1):endPage;
//  xEndPos = xEndPos>=OLED_WIDTH?(OLED_WIDTH-1):xEndPos;
//  
//  uint16_t pageP=firstPage,pageCnt=0;
//  uint32_t xP,xCnt;
//  uint8_t highBitsGet=0xff<<(8-firstBitExc);    //һ��λ��ȡ��λ
//  uint8_t lowBitsGet=0xff>>(firstBitExc);       //һ��λ��ȡ��λ
//  
//  int16_t tmp;
//  //��һ�к����һ����ͬһ�е����⴦��
////  if(firstPage == endPage)
////  {
////    OLED_SetPositionInPage(xBeginPos,pageP);
////  }
////  else if(firstPage<endPage)
////  {
//    //��һ�����⴦��
//    OLED_SetPositionInPage(xBeginPos,pageP);
//    for(xP=xBeginPos,xCnt=pageCnt*bmpInfo->width; xP<=xEndPos; xP++,xCnt++)
//    {
//      OLED_Gram[xP][pageP] = \
//          ((OLED_Gram[xP][pageP])&(0xff>>(8-firstBitExc))) | \
//          ((*(bmpInfo->pBmp+xCnt)&lowBitsGet)<<(firstBitExc));
//      OLED_WriteData(OLED_Gram[xP][pageP]);
//    }
//    pageP++;
//    pageCnt++;
//    //ѭ�������м��
//    tmp = (endPage>drawEndPage)?drawEndPage:(drawEndPage-1);
//    for(; pageP<=tmp; pageP++,pageCnt++)
//    {
//      OLED_SetPositionInPage(xBeginPos,pageP);
//      for(xP=xBeginPos,xCnt=pageCnt*bmpInfo->width; xP<=xEndPos; xP++,xCnt++)
//      {
//        OLED_Gram[xP][pageP] = \
//          ((*(bmpInfo->pBmp+xCnt-bmpInfo->width)&highBitsGet)>>(8-firstBitExc)) | \
//          ((*(bmpInfo->pBmp+xCnt)&lowBitsGet)<<(firstBitExc));
//        OLED_WriteData(OLED_Gram[xP][pageP]);
//      }
//    }
//    //���һ�����⴦����������һЩ��
//    if(tmp==drawEndPage-1)
//    {
//      OLED_SetPositionInPage(xBeginPos, pageP);
//      for(xP=xBeginPos,xCnt=pageCnt*bmpInfo->width; xP<=xEndPos; xP++,xCnt++)
//      {
//        OLED_Gram[xP][pageP] = \
//            (((*(bmpInfo->pBmp+xCnt-bmpInfo->width)&highBitsGet)>>(8-firstBitExc))&(0xff>>(8-endBitExc))) | \
//            ((OLED_Gram[xP][pageP])&(0xff<<endBitExc));
//        OLED_WriteData(OLED_Gram[xP][pageP]);
//      }
//    }
////  }
//}
