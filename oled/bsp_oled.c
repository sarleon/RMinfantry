/**
  ******************************************************************************
  * @file    bsp_oled.c
  * @author  EC_Dog
  * @version V2.0
  * @date    2016/07/17
  * @brief   
  * 		IIC�� 12864 oled����
  ******************************************************************************
  * @attention
  *     �ο����ϳ����д����������ֻ��program�İ��˹�
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_oled.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Defines -------------------------------------------------------------------*/
#define IIC_SCL_GPIO	GPIOB
#define IIC_SCL_PIN		GPIO_Pin_10
#define IIC_SDA_GPIO	GPIOB
#define IIC_SDA_PIN		GPIO_Pin_11

#define SCL_H()		GPIO_SetBits(IIC_SCL_GPIO, IIC_SCL_PIN)
#define SCL_L()		GPIO_ResetBits(IIC_SCL_GPIO, IIC_SCL_PIN)
#define SDA_H()		GPIO_SetBits(IIC_SDA_GPIO, IIC_SDA_PIN)
#define SDA_L()		GPIO_ResetBits(IIC_SDA_GPIO, IIC_SDA_PIN)


#define OLED_ADDR   0x78
#define X_LEVEL_L		0x00
#define X_LEVEL_H		0x10
#define X_LEVEL		  ((X_LEVEL_H&0x0F)*16+X_LEVEL_L)

#define OLED_WIDTH  128
#define OLED_HEIGHT 64
#define OLED_PAGE   8

/* Variables -----------------------------------------------------------------*/
__IO uint16_t OLED_CMD_Brightness = 0x11;

static uint8_t OLED_Gram[128][8];     //OLED���Դ�

const unsigned char F6x8[][6] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};

static void OLED_WriteData(uint8_t iic_data);
static void OLED_WriteCommand(uint8_t iic_command);


/**
  * @brief  IICר����ʱ����
  * @param  None
  * @retval None
  */
static void IIC_Delay(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
}


/**
  * @brief  IIC��ʼ�ź�
  * @param  None
  * @retval None
  */
static void IIC_Start(void)
{
	SDA_H();
	SCL_H();
	IIC_Delay();
	SDA_L();        //START:when CLK is high,DATA change form high to low
	IIC_Delay();
	SCL_L();
	IIC_Delay();
}


/**
  * @brief  IICֹͣ�ź�
  * @param  None
  * @retval None
  */
static void IIC_Stop(void)
{
	SDA_L();
	SCL_L();
	IIC_Delay();
	SCL_H();
	IIC_Delay();
	SDA_H();
	IIC_Delay();
}


/**
  * @brief  IIC����һ���ֽڣ����ж�Ӧ���ź�
  * @param  None
  * @retval None
  */
static void IIC_WriteByte(uint8_t byte)
{
	for(uint8_t i=0;i<8;i++)
	{
		if(byte & 0x80)
			SDA_H();
		else
			SDA_L();
		byte <<= 1;
		IIC_Delay();
		SCL_H();
		IIC_Delay();
		SCL_L();
		IIC_Delay();
	}
  /*
  ֻ�Ǹ�һ��ʱ��������Ack��������SDA�ĵ�ƽ�ߵͶԴ�ʵ�ⲻӰ�죬����
  ���SDA�����ȶ������ͻ��ֻ���������������Ӧ��ֻҪ�ȶ����H��L
  */
	SDA_H();    //  SDA_L();
	IIC_Delay();
	SCL_H();
	IIC_Delay();
	SCL_L();
	IIC_Delay();
}



/*********************************************************************
*                      ȫ�´��죬�����ڴ�
**********************************************************************/
/**
  * @brief  OLEDд����
  * @param  data
  * @retval None
  */
static void OLED_WriteData(uint8_t iic_data)
{
	IIC_Start();
	IIC_WriteByte(OLED_ADDR);
	IIC_WriteByte(0x40);
	IIC_WriteByte(iic_data);
	IIC_Stop();
}


/**
  * @brief  OLEDд����
  * @param  command
  * @retval None
  */
static void OLED_WriteCommand(uint8_t iic_command)
{
	IIC_Start();
	IIC_WriteByte(OLED_ADDR);
	IIC_WriteByte(0x00);
	IIC_WriteByte(iic_command);
	IIC_Stop();
}


/**
  * @brief  OLED��������1
  * @param  x����
  * @param  page
  * @retval None
  */
void OLED_SetPositionInPage(uint8_t x, uint8_t page) 
{ 
	OLED_WriteCommand(0xb0+page);        //����page����Χb0~b7
	OLED_WriteCommand(((x&0xf0)>>4)|0x10);//set the upper column address

	OLED_WriteCommand(x&0x0f);//set the lower column address
}


/**
  * @brief  OLED��������2
  * @param  x:x����
  * @param  y:y����
  * @retval None
  */
static void OLED_SetPos(uint8_t x, uint8_t y)
{
  OLED_WriteCommand(0xb0+y/8);
  OLED_WriteCommand(((x&0xf0)>>4)|0x10);  //set the upper column address
	OLED_WriteCommand(x&0x0f);       //set the lower column address
}


/**
  * @brief  ���������Դ浽oled
  * @param  None
  * @retval None
*/
void OLED_RefreshGram(void)
{
  for(uint8_t page=0;page<8;page++)
  {
    OLED_SetPos(0,page*8);
    for(uint8_t column=0;column<OLED_WIDTH;column++)
      OLED_WriteData(OLED_Gram[column][page]);
  }
}


/**
  * @brief  ����
  * @param  None
  * @retval None
*/
void OLED_Clear(void)
{
  for(uint8_t page=0;page<8;page++)
  {
    for(uint8_t column=0;column<OLED_WIDTH;column++)
      OLED_Gram[column][page] = 0;
  }
  //�����Դ�
  OLED_RefreshGram();
}

  
/**
  * @brief  �򿪻��߹ر�OLED��ʾ
  * @param  0:�ر�,1:��
  * @retval None
*/
void OLED_DisplaySet(uint8_t state)
{
  if(state == 0)
    OLED_WriteCommand(0xaf);
  else
    OLED_WriteCommand(0xae);
}


/**
  * @brief  ����
  * @param  x:x����
  * @param  y:y����
  * @param  isShow: not.����ʾ��is.��ʾ
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
  */
void OLED_DrawPixel(uint8_t x, uint8_t y, ISorNOT isShow, ISorNOT isRefresh)
{
  uint8_t page = 0;   //ҳ��
  uint8_t bitX = 0;   //��һλ
  uint8_t tmp = 0;    //�м�ֵ
  
  //�ж��Ƿ񳬷�Χ
  if(x>=OLED_WIDTH || y>=OLED_HEIGHT)
    return;
  
  page = y/8;
  bitX = y%8;
  tmp = 1<<bitX;  //tmp = 1<<(7-bitX);��������½�Ϊ0,0
  if(isShow)
  {
    OLED_Gram[x][page] |= tmp;
  }
  else
  {
    OLED_Gram[x][page] &= ~tmp;
  }
  
  if(isRefresh == IS)
  {
    //���������
    OLED_SetPos(x, y);
    OLED_WriteData(OLED_Gram[x][page]);
  }
}


/**
  * @brief  �����8λ��Ч���ݣ�Ϊ�˼ӿ�д���ٶ�!!!!!!!̫����!!!!!!!!
  * @param  x:x����(�ɸ�)
  * @param  y:y����(�ɸ�)
  * @param  wrtData:д�������
  * @param  effBits:д����Чλ��
  * @param  invSW:���򿪹�
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
  */
void OLED_DrawSomeBits(int16_t x, int16_t y, uint8_t wrtData, uint8_t effBits, \
                      InvChoose InvSW, ISorNOT isRefresh)
{
  //�ж��Ƿ���һ��ҳ��
  int16_t page1 = y/8;
  int16_t page2 = (y+effBits-1)/8;
  int8_t isInOnePage = ((page1==page2)?1:0);
  uint8_t bitsTmp1 = wrtData, bitsTmp2 = wrtData;
  uint8_t bitsChose;    //ȡλ
  
  if(y<-8||y>=OLED_HEIGHT||x<0||x>=OLED_WIDTH)
    return;
  else{
    if(y<0){
      if(effBits+y<=0){
        return;
      }else{
        //�Դ治�ı��ȡλ
        bitsChose = 0xff<<(effBits+y);
        OLED_Gram[x][0] = (bitsChose&OLED_Gram[x][0]) | \
        (((InvSW==INV_OFF)?(bitsTmp1>>-y):~(bitsTmp1>>-y))&(~bitsChose));
      }
      if(isRefresh==IS){
        OLED_SetPos(x,0);
        OLED_WriteData(OLED_Gram[x][0]);
      }
    }else{
      if(isInOnePage){
        //�Դ治�ı���෴ȡλ
        bitsChose = (0xff<<(y%8))&(0xff>>(8-effBits-y%8));
        OLED_Gram[x][page1] = ((~bitsChose)&OLED_Gram[x][page1]) | \
              (((InvSW==INV_OFF)?(bitsTmp1<<(y%8)):~(bitsTmp1<<(y%8)))&bitsChose);
        if(isRefresh==IS){
          OLED_SetPos(x,y);
          OLED_WriteData(OLED_Gram[x][page1]);
        }
      }else{
        //�Դ治�ı���෴ȡλ
        bitsChose = 0xff<<(y%8);
        OLED_Gram[x][page1] = ((~bitsChose)&OLED_Gram[x][page1]) | \
              (((InvSW==INV_OFF)?(bitsTmp1<<(y%8)):~(bitsTmp1<<(y%8)))&bitsChose);
        
        if(page2<OLED_PAGE){
          //�Դ治�ı���෴ȡλ
          bitsChose = 0xff>>((8-(y+effBits)%8));
          OLED_Gram[x][page2] = ((~bitsChose)&OLED_Gram[x][page2]) | \
                (((InvSW==INV_OFF)?(bitsTmp2>>(8-y%8)):~(bitsTmp2>>(8-y%8)))&bitsChose);
        }
        
        if(isRefresh==IS){
          OLED_SetPos(x,y);
          OLED_WriteData(OLED_Gram[x][page1]);
          if(page2<OLED_PAGE){
            OLED_SetPos(x,y+8);
            OLED_WriteData(OLED_Gram[x][page2]);
          }
        }
      }
    }
  }
}


/**
  * @brief  ��ָ��������ͼƬ(����ѡ��ֻ���µ��Դ�)
  * @param  x:���Ͻ�x(��Ϊ����)
  * @param  y:���Ͻ�y����Ϊ������
  * @param  showW:��ʾ�Ŀ��(��ѹ��)�ɴ���ͼƬ
  * @param  showH:��ʾ�ĸ߶�(��ѹ��)�ɴ���ͼƬ
  * @param  bmpInfo:ͼƬ��Ϣ
  * @param  InvSW:���򿪹�
  * @param  isRefresh: not.�����µ�oled;is.����
  * @param  None
*/
void OLED_DrawBmp(int16_t x, int16_t y, uint16_t showW, uint16_t showH, \
                  BmpInfoStructTypedDef* bmpInfo, InvChoose InvSW)
{
  int16_t xPos = x;
  int16_t yPos = y;
  uint16_t xCnt;
  
  int16_t lastY = y+showH-1;  //���һ��λ��
  uint16_t pageCnt=0;
  uint8_t effBits;            //��Ч������λ��
  uint8_t dataChose;          //Ҫ��ʾ��8λ����
  
  do
  {
    effBits = (lastY-yPos+1>=8)?8:(lastY-yPos+1);
    for(xPos=x,xCnt=0;xCnt<showW;xPos++,xCnt++)
    {
      if(xCnt<bmpInfo->width)
        dataChose = *(bmpInfo->pBmp+(pageCnt*bmpInfo->width+xCnt));
      else
        dataChose = 0;
      OLED_DrawSomeBits(xPos, yPos, dataChose, effBits, InvSW, IS);
    }
    yPos+=8;
    pageCnt++;
  }
  while(yPos<=lastY&&yPos<=y+bmpInfo->height);
}


/**
  * @brief  ��ָ����Сд��һ��6x8��׼ASCII�ַ���
  * @param  x:���Ͻ�x(��Ϊ����)
  * @param  y:���Ͻ�y(��Ϊ����)
  * @param  showW:�ı���Ŀ��
  * @param  showH:�ı���ĸ߶�
  * @param  pWrtData:д���ַ���ָ��
  * @param  InvSW:���򿪹�
  * @param  isRefresh: not.�����µ�oled;is.����
  * @retval None
  */
void OLED_Print6x8Str(int16_t x,int16_t y,uint16_t showW,uint16_t showH,
        uint8_t* pWrtData,InvChoose InvSW,ISorNOT isRefresh)
{
  int16_t xPos = x;
  int16_t yPos = y;
  uint16_t xCnt = 0;
  int16_t wrtCnt = 0;
  int16_t lastY = y+showH-1;  //���һ��λ��
  uint8_t effBits;            //��Ч������λ��
  uint8_t dataChose;          //ѡ��
  int16_t pCpltSymbol = 0;    //��ӡ��ɱ�־λ
  
  while(yPos<=lastY)
  {
    effBits = (lastY-yPos+1>=8)?8:(lastY-yPos+1);
    for(xPos=x,xCnt=0;xCnt+6<showW;xCnt+=6)
    {
      dataChose = *(pWrtData+wrtCnt)-32;
      
      if(*(pWrtData+wrtCnt)=='\0')
        pCpltSymbol = 1;
      
      if(*(pWrtData+wrtCnt)=='\n')
      {
        wrtCnt++;
        break;
      }
      
      if(pCpltSymbol == 0)
      {
        for(int16_t i=0;i<6;i++,xPos++)
        {
            OLED_DrawSomeBits(xPos,yPos,F6x8[dataChose][i],effBits,InvSW,isRefresh);
        }
      }
      else
      {
        for(int16_t i=0;i<6;i++,xPos++)
        {
            OLED_DrawSomeBits(xPos,yPos,0,effBits,InvSW,isRefresh);
        }
      }
      if(pCpltSymbol == 0)
        wrtCnt++;
    }
    for(;xCnt<showW;xCnt++,xPos++)
    {
      OLED_DrawSomeBits(xPos,yPos,0x00,effBits,InvSW,isRefresh);
    }
    yPos+=8;
  }
}


/**
  * @brief  ����һ���ַ���ָ��
  * @param  
  * @Retval None
*/
uint8_t* OLED_TextPrint(void* fmt, ...)
{
  uint8_t textBuf[128];
  uint8_t len;
  uint8_t* point = NULL;
	va_list ap;
	
	va_start(ap,fmt);
	len = vsnprintf((char*)textBuf,128,(char*)fmt,ap);
	va_end(ap);
  if(len>0)
  {
    point = malloc(len+1);
    strcpy((char*)point, (const char*)textBuf);
  }
  return point;
}

/**
  * @brief  OLED��ʼ����ʱ
  * @param  None
  * @retval None
  */
static void OLED_Delay(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();
}


/**
  * @brief  OLED��ʼ��
  * @param  None
  * @retval None
  */
void OLED_Init(void)
{

	OLED_Delay();//��ʼ��֮ǰ����ʱ����Ҫ��
	
	OLED_WriteCommand(0xae);//�ر���ʾ--turn off oled panel
	OLED_WriteCommand(0x00);//--set low column address
	OLED_WriteCommand(0x10);//--set high column address
	OLED_WriteCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WriteCommand(0x81);//--set contrast control register
	OLED_WriteCommand(OLED_CMD_Brightness); //--Set SEG Output Current Brightness
	OLED_WriteCommand(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WriteCommand(0xc8);//--Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WriteCommand(0xa6);//--set normal display
	OLED_WriteCommand(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WriteCommand(0x3f);//--1/64 duty
	OLED_WriteCommand(0xd3);//--set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WriteCommand(0x00);//--not offset
	OLED_WriteCommand(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WriteCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WriteCommand(0xd9);//--set pre-charge period
	OLED_WriteCommand(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WriteCommand(0xda);//--set com pins hardware configuration
	OLED_WriteCommand(0x12);
	OLED_WriteCommand(0xdb);//--set vcomh
	OLED_WriteCommand(0x40);//--Set VCOM Deselect Level
	OLED_WriteCommand(0x20);//--Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WriteCommand(0x02);//
	OLED_WriteCommand(0x8d);//--set Charge Pump enable/disable
	OLED_WriteCommand(0x14);//--set(0x10) disable
	OLED_WriteCommand(0xa4);//--Entire Display(off:0xa4/on:0xa5)
	OLED_WriteCommand(0xa6);//--Inverse Display(off:0xa6/on:0xa7) 
	OLED_WriteCommand(0xaf);//--turn on oled panel
	OLED_Clear(); //��ʼ����
	OLED_SetPositionInPage(0,0);
}
