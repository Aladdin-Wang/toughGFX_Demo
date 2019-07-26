#ifndef __BSP__DRIVER__LCD__H
#define __BSP__DRIVER__LCD__H
#include "stm32f4xx_hal.h"
#include "ltdc.h"
#include "fonts.h"
/*把这个宏设置成非0值 液晶屏使用RGB888色彩，若为0则使用RGB565色彩*/
#define LCD_RGB_888  1
typedef struct
{
  int16_t X;
  int16_t Y;
} Point, * pPoint;
typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;
#define LCD_COLOR_WHITE          0xFFFFFF
#define LCD_COLOR_BLACK          0x000000
#define LCD_COLOR_GREY           0xC0C0C0
#define LCD_COLOR_BLUE           0x0000FF
#define LCD_COLOR_BLUE2          0x0000A0
#define LCD_COLOR_RED            0xFF0000
#define LCD_COLOR_MAGENTA        0xFF00FF
#define LCD_COLOR_GREEN          0x00FF00
#define LCD_COLOR_CYAN           0x00FFFF
#define LCD_COLOR_YELLOW         0xFFFF00
/** @defgroup STM32F429I_DISCOVERY_LCD_Private_Defines
  * @{
  */

#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))   
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LCD_Private_Macros
  * @{
  */
#define ABS(X)  ((X) > 0 ? (X) : -(X))    
/* LCD Size (Width and Height) */
#define  LCD_PIXEL_WIDTH    ((uint16_t)800)
#define  LCD_PIXEL_HEIGHT   ((uint16_t)480)

#define LCD_FRAME_BUFFER       ((uint32_t)0xD0000000)		//第一层首地址
#define BUFFER_OFFSET          ((uint32_t)800*480*3)     //一层液晶的数据量
#define LCD_PIXCELS            ((uint32_t)800*480) 

/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT         Font16x24
/** 
  * @brief  LCD Direction  
  */ 
#define LCD_DIR_HORIZONTAL       0x0000
#define LCD_DIR_VERTICAL         0x0001
/** 
  * @brief  LCD Layer  
  */ 
#define LCD_BACKGROUND_LAYER     0x0000
#define LCD_FOREGROUND_LAYER     0x0001

void     LCD_Init(void);
void     LCD_LayerInit(void);
void     LCD_ChipSelect(FunctionalState NewState);
void     LCD_SetLayer(uint32_t Layerx);
void     LCD_SetColors(uint32_t _TextColor, uint32_t _BackColor); 
void     LCD_GetColors(uint32_t *_TextColor, uint32_t *_BackColor);
void     LCD_SetTextColor(uint32_t Color);
void     LCD_SetBackColor(uint32_t Color);
void     LCD_SetTransparency(uint8_t transparency);
void     LCD_ClearLine(uint16_t Line);
void     LCD_Clear(uint32_t Color);
uint32_t LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void     LCD_SetColorKeying(uint32_t RGBValue);
void     LCD_ReSetColorKeying(void);
void     LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c);
void     LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii);
void     LCD_SetFont(sFONT *fonts);
sFONT *  LCD_GetFont(void);
void     LCD_DisplayStringLine(uint16_t Line, uint8_t *ptr);
void     LCD_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width);
void     LCD_WindowModeDisable(void);
void     LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction);
void     LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     LCD_DrawEllipse(int Xpos, int Ypos, int Radius, int Radius2);
void     LCD_DrawFullEllipse(int Xpos, int Ypos, int Radius, int Radius2);
void     LCD_DrawMonoPict(const uint32_t *Pict);
void     LCD_WriteBMP(uint32_t BmpAddress);
void     LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     LCD_PolyLine(pPoint Points, uint16_t PointCount);
void     LCD_PolyLineRelative(pPoint Points, uint16_t PointCount);
void     LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount);
void     LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount);
void     LCD_FillPolyLine(pPoint Points, uint16_t PointCount);
void     LCD_Triangle(pPoint Points, uint16_t PointCount);
void     LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);
void     LCD_WriteCommand(uint8_t LCD_Reg);
void     LCD_WriteData(uint8_t value);
void     LCD_PowerOn(void);
void     LCD_DisplayOn(void);
void     LCD_DisplayOff(void);
void     LCD_CtrlLinesWrite(GPIO_TypeDef* GPIOx, uint16_t CtrlPins, BitAction BitVal);
void     PutPixel(int16_t x, int16_t y);
/*汉字*/
void LCD_DispChar_CH ( uint16_t usX, uint16_t usY, uint16_t usChar);
void LCD_DispString_EN_CH( uint16_t usX, uint16_t usY, const uint8_t * pStr );
void LCD_DisplayStringLine_EN_CH(uint16_t Line, uint8_t *ptr);
/*缩放*/
void LCD_DisplayStringLineEx(uint16_t x, //显示的x点
														 uint16_t y, //显示的y点
														 uint16_t Font_width,	//要显示的字体宽度，英文字符在此基础上/2。注意为偶数
														 uint16_t Font_Heig,	//要显示的字体高度，注意为偶数
														 uint8_t *ptr,				//显示的字符内容
														 uint16_t DrawModel);  //是否反色显示
#endif


