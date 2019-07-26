#include "bsp_driver_lcd.h"
#include "dma2d.h"
#include "fonts.h"
/*用于存储当前选择的字体格式*/
static sFONT *LCD_Currentfonts;
/* 用于存储当前字体颜色和字体背景颜色的变量*/
static uint32_t CurrentTextColor   = 0x000000;
static uint32_t CurrentBackColor   = 0xFFFFFF;
/* 用于存储层对应的显存空间 和 当前选择的层*/
static uint32_t CurrentFrameBuffer = LCD_FRAME_BUFFER;
static uint32_t CurrentLayer = LCD_BACKGROUND_LAYER;
#define CR_MASK                     ((uint32_t)0xFFFCE0FC)  /* DMA2D CR Mask */
#define PFCCR_MASK                  ((uint32_t)0x00FC00C0)  /* DMA2D FGPFCCR Mask */
#define DEAD_MASK                   ((uint32_t)0xFFFF00FE)  /* DMA2D DEAD Mask */
/*根据液晶数据手册的参数配置*/
#define HBP  46		//HSYNC后的无效像素
#define VBP  23		//VSYNC后的无效行数

#define HSW   1		//HSYNC宽度
#define VSW   1		//VSYNC宽度

#define HFP  20		//HSYNC前的无效像素
#define VFP   22		//VSYNC前的无效行数


#define ZOOMMAXBUFF 16384
uint8_t zoomBuff[ZOOMMAXBUFF] = {0};	//用于缩放的缓存，最大支持到128*128

/**
  * @brief  选择要控制的层.
  * @param  Layerx: 选择要操作前景层(第2层)还是背景层(第1层)
  * @retval None
  */
void LCD_SetLayer(uint32_t Layerx)
{
  if (Layerx == LCD_BACKGROUND_LAYER)
  {
    CurrentFrameBuffer = LCD_FRAME_BUFFER; 
    CurrentLayer = LCD_BACKGROUND_LAYER;
  }
  else
  {
    CurrentFrameBuffer = LCD_FRAME_BUFFER + BUFFER_OFFSET;
    CurrentLayer = LCD_FOREGROUND_LAYER;
  }
}  
/**
  * @brief  Configure the transparency.
  * @param  transparency: specifies the transparency, 
  *         This parameter must range from 0x00 to 0xFF.
  * @retval None
  */
void LCD_SetTransparency(uint8_t transparency)
{
  if (CurrentLayer == LCD_BACKGROUND_LAYER)
  {
    HAL_LTDC_SetAlpha(&hltdc,(uint32_t)LTDC_Layer1, transparency);
  }
  else
  {     
    HAL_LTDC_SetAlpha(&hltdc,(uint32_t)LTDC_Layer2, transparency);
  }
  HAL_LTDC_Reload(&hltdc,LTDC_RELOAD_IMMEDIATE);
}

FlagStatus DMA2D_GetFlagStatus(uint32_t DMA2D_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_DMA2D_GET_FLAG(DMA2D_FLAG));
  
  /* Check the status of the specified DMA2D flag */
  if (((DMA2D->ISR) & DMA2D_FLAG) != (uint32_t)RESET)
  {
    /* DMA2D_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DMA2D_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the DMA2D_FLAG status */
  return bitstatus;
}
/* USER CODE BEGIN 1 */
/**
  * @brief  Clears the hole LCD.
  * @param  Color: the color of the background.
  * @retval None
  */
void LCD_Clear(uint32_t Color)
{
	uint32_t timeout=0; 
	/*hdma2d.Instance = DMA2D;
	hdma2d.Init.Mode = DMA2D_R2M;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
	hdma2d.Init.OutputOffset = 0x0;
	if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_DMA2D_ConfigLayer(&hdma2d,CurrentLayer); //层配置
	HAL_DMA2D_Start(&hdma2d,Color,CurrentFrameBuffer,800,480);//开启传输
	HAL_DMA2D_PollForTransfer(&hdma2d,1000);//传输数据*/
	__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
	DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
	DMA2D->CR=DMA2D_R2M;			//寄存器到存储器模式
	DMA2D->OPFCCR=DMA2D_OUTPUT_RGB888;	//设置颜色格式
	DMA2D->OOR=0x0;				//设置行偏移 

	DMA2D->OMAR=CurrentFrameBuffer;				//输出存储器地址
	DMA2D->NLR=(480)|((800)<<16);	//设定行数寄存器
	DMA2D->OCOLR=Color;						//设定输出颜色寄存器 
	DMA2D->CR|=DMA2D_CR_START;				//启动DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;		//清除传输完成标志 	
}
/**
  * @brief  éè??×?ì?μ???é??°×?ì?μ?±3?°??é?
  * @param  TextColor: ×?ì???é?
  * @param  BackColor: ×?ì?μ?±3?°??é?
  * @retval None
  */
void LCD_SetColors(uint32_t TextColor, uint32_t BackColor) 
{
  CurrentTextColor = TextColor; 
  CurrentBackColor = BackColor;
}

/**
  * @brief ??è?μ±?°éè??μ?×?ì???é?oí×?ì?μ?±3?°??é?
  * @param  TextColor: ???ò×?ì???é?μ?????
  * @param  BackColor: ???ò×?ì?±3?°??é?μ?????
  * @retval None
  */
void LCD_GetColors(uint32_t *TextColor, uint32_t *BackColor)
{
  *TextColor = CurrentTextColor;
  *BackColor = CurrentBackColor;
}

/**
  * @brief  éè??×?ì???é?
  * @param  Color: ×?ì???é?
  * @retval None
  */
void LCD_SetTextColor(uint32_t Color)
{
  CurrentTextColor = Color;
}

/**
  * @brief  éè??×?ì?μ?±3?°??é?
  * @param  Color: ×?ì?μ?±3?°??é?
  * @retval None
  */
void LCD_SetBackColor(uint32_t Color)
{
  CurrentBackColor = Color;
}

/**
  * @brief  éè??×?ì???ê?(ó￠??)
  * @param  fonts: ????òaéè??μ?×?ì???ê?
  * @retval None
  */
void LCD_SetFont(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}
/**
  * @brief  Gets the Text Font.
  * @param  None.
  * @retval the used font.
  */
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}


/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint32_t index = 0, counter = 0, xpos =0;
  uint32_t  Xaddress = 0;
  
  xpos = Xpos*LCD_PIXEL_WIDTH*3;
  Xaddress += Ypos;
  
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  {
    
    for(counter = 0; counter < LCD_Currentfonts->Width; counter++)
    {
          
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> counter)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
        (((c[index] & (0x1 << counter)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
      {
        *(__IO uint16_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos) = (0x00FFFF & CurrentBackColor);        //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos+2) = (0xFF0000 & CurrentBackColor) >> 16; //R
      }
      else
      {
        *(__IO uint16_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos) = (0x00FFFF & CurrentTextColor);        //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos+2) = (0xFF0000 & CurrentTextColor) >> 16; //R
      }
      Xaddress++;
    }
      Xaddress += (LCD_PIXEL_WIDTH - LCD_Currentfonts->Width);
  }
}
/**
  * @brief  显示一个像素点
  * @param  x: 像素点的x坐标
  * @param  y: 像素点的y坐标
  * @retval None
  */
void PutPixel(int16_t x, int16_t y)
{ 
  if(x < 0 || x > LCD_PIXEL_WIDTH || y < 0 || y > LCD_PIXEL_HEIGHT)
  {
    return;  
  }
#if 0
 LCD_DrawLine(x, y, 1, LCD_DIR_HORIZONTAL);
#else /*这样直接描点效率估计会高点*/
 {
	  /*RGB888*/
	  uint32_t  Xaddress =0;
    Xaddress =  CurrentFrameBuffer + 3*(LCD_PIXEL_WIDTH*y + x);
	  *(__IO uint16_t*) Xaddress= (0x00FFFF & CurrentTextColor);        //GB
  	*(__IO uint8_t*)( Xaddress+2)= (0xFF0000 & CurrentTextColor) >> 16; //R
  }
#endif
}
/**
  * @brief  Displays one character (16dots width, 24dots height).
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..29
  * @param  Column: start column address.
  * @param  Ascii: character ascii code, must be between 0x20 and 0x7E.
  * @retval None
  */
void LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii)
{
  Ascii -= 32;

  LCD_DrawChar(Line, Column, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}
/**
  * @brief  Clears the selected line.
  * @param  Line: the Line to be cleared.
  *   This parameter can be one of the following values:
  *     @arg LCD_LINE_x: where x can be: 0..13 if LCD_Currentfonts is Font16x24
  *                                      0..26 if LCD_Currentfonts is Font12x12 or Font8x12
  *                                      0..39 if LCD_Currentfonts is Font8x8
  * @retval None
  */
void LCD_ClearLine(uint16_t Line)
{
  uint16_t refcolumn = 0;
  /* Send the string character by character on lCD */
  while ((refcolumn < LCD_PIXEL_WIDTH) && (((refcolumn + LCD_Currentfonts->Width)& 0xFFFF) >= LCD_Currentfonts->Width))
  {
    /* Display one character on LCD */
    LCD_DisplayChar(Line, refcolumn, ' ');
    /* Decrement the column position by 16 */
    refcolumn += LCD_Currentfonts->Width;
  }
}
/**
  * @brief  Displays a maximum of 20 char on the LCD.
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  *ptr: pointer to string to display on LCD.
  * @retval None
  */
void LCD_DisplayStringLine(uint16_t Line, uint8_t *ptr)
{  
  uint16_t refcolumn = 0;
  /* Send the string character by character on lCD */
  while ((refcolumn < LCD_PIXEL_WIDTH) && ((*ptr != 0) & (((refcolumn + LCD_Currentfonts->Width) & 0xFFFF) >= LCD_Currentfonts->Width)))
  {
    /* Display one character on LCD */
    LCD_DisplayChar(Line, refcolumn, *ptr);
    /* Decrement the column position by width */
    refcolumn += LCD_Currentfonts->Width;
    /* Point on the next character */
    ptr++;
  }
}
/**
  * @brief  Displays an uni-line (between two points).
  * @param  x1: specifies the point 1 x position.
  * @param  y1: specifies the point 1 y position.
  * @param  x2: specifies the point 2 x position.
  * @param  y2: specifies the point 2 y position.
  * @retval None
  */
void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    PutPixel(x, y);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}
/**
  * @brief 显示一条直线
  * @param Xpos: 直线起点的x坐标
  * @param Ypos: 直线起点的y坐标
  * @param Length: 直线的长度
  * @param Direction: 直线的方向，可输入LCD_DIR_HORIZONTAL(水平方向) LCD_DIR_VERTICAL(垂直方向).
  * @retval None
  */
void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction)
{
	uint32_t timeout=0; 
	uint32_t  Xaddress = 0;
		/*计算目标地址*/
  Xaddress = CurrentFrameBuffer + 3*(LCD_PIXEL_WIDTH*Ypos + Xpos);
		/*水平方向*/
	if(Direction == LCD_DIR_HORIZONTAL)
  { 
		hdma2d.Init.OutputOffset = 0x0;
	}
	else /*垂直方向*/
  { 
		hdma2d.Init.OutputOffset = LCD_PIXEL_WIDTH - 1; 
	}

	/*水平方向*/
	if(Direction == LCD_DIR_HORIZONTAL)
  { 
			__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
			DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
			DMA2D->CR=DMA2D_R2M;			//寄存器到存储器模式
			DMA2D->OPFCCR=DMA2D_OUTPUT_RGB888;	//设置颜色格式
			DMA2D->OOR=hdma2d.Init.OutputOffset;				//设置行偏移 

			DMA2D->OMAR=Xaddress;				//输出存储器地址
			DMA2D->NLR=(1)|((Length)<<16);	//设定行数寄存器
			DMA2D->OCOLR=CurrentTextColor;						//设定输出颜色寄存器 
			DMA2D->CR|=DMA2D_CR_START;				//启动DMA2D
	}
	else /*垂直方向*/
  {  
			__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
			DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
			DMA2D->CR=DMA2D_R2M;			//寄存器到存储器模式
			DMA2D->OPFCCR=DMA2D_OUTPUT_RGB888;	//设置颜色格式
			DMA2D->OOR=hdma2d.Init.OutputOffset;				//设置行偏移 

			DMA2D->OMAR=Xaddress;				//输出存储器地址
			DMA2D->NLR=(Length)|((1)<<16);	//设定行数寄存器
			DMA2D->OCOLR=CurrentTextColor;						//设定输出颜色寄存器 
			DMA2D->CR|=DMA2D_CR_START;				//启动DMA2D
	}

	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;		//清除传输完成标志 
}
/**
  * @brief  Draw a circle.
  * @param  Xpos: specifies the X position, can be a value from 0 to 240.
  * @param  Ypos: specifies the Y position, can be a value from 0 to 320.
  * @param  Radius: radius of the circle.
  * @retval None
  */
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  
    int x = -Radius, y = 0, err = 2-2*Radius, e2;
    do {
      

        *(__IO uint16_t*) (CurrentFrameBuffer + (3*((Xpos-x) + LCD_PIXEL_WIDTH*(Ypos+y))))= (0x00FFFF & CurrentTextColor);       //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*((Xpos-x) + LCD_PIXEL_WIDTH*(Ypos+y))+2))= (0xFF0000 & CurrentTextColor) >> 16; //R
      
        *(__IO uint16_t*) (CurrentFrameBuffer + (3*((Xpos+x) + LCD_PIXEL_WIDTH*(Ypos+y)))) = (0x00FFFF & CurrentTextColor);      //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*((Xpos+x) + LCD_PIXEL_WIDTH*(Ypos+y))+2))= (0xFF0000 & CurrentTextColor) >> 16; //R
      
        *(__IO uint16_t*) (CurrentFrameBuffer + (3*((Xpos+x) + LCD_PIXEL_WIDTH*(Ypos-y)))) = (0x00FFFF & CurrentTextColor);      //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*((Xpos+x) + LCD_PIXEL_WIDTH*(Ypos-y))+2))= (0xFF0000 & CurrentTextColor) >> 16; //R
      
        *(__IO uint16_t*) (CurrentFrameBuffer + (3*((Xpos-x) + LCD_PIXEL_WIDTH*(Ypos-y)))) = (0x00FFFF & CurrentTextColor);      //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*((Xpos-x) + LCD_PIXEL_WIDTH*(Ypos-y))+2))= (0xFF0000 & CurrentTextColor) >> 16; //R


        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    }
    while (x <= 0);
    
}
/**
  * @brief  Displays a full circle.
  * @param  Xpos: specifies the X position, can be a value from 0 to 240.
  * @param  Ypos: specifies the Y position, can be a value from 0 to 320.
  * @param  Radius
  * @retval None
  */
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      LCD_DrawLine(Xpos - CurX, Ypos - CurY, 2*CurY, LCD_DIR_VERTICAL);
      LCD_DrawLine(Xpos + CurX, Ypos - CurY, 2*CurY, LCD_DIR_VERTICAL);
    }
    
    if(CurX > 0) 
    {
      LCD_DrawLine(Xpos - CurY, Ypos - CurX, 2*CurX, LCD_DIR_VERTICAL);
      LCD_DrawLine(Xpos + CurY, Ypos - CurX, 2*CurX, LCD_DIR_VERTICAL);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
  
  LCD_DrawCircle(Xpos, Ypos, Radius);  
}
/**
  * @brief  绘制实心矩形
  * @param  Xpos: 起始X坐标
  * @param  Ypos: 起始Y坐标
  * @param  Height: 矩形高
  * @param  Width: 矩形宽
  * @retval None
  */
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint32_t timeout=0; 
	uint32_t  Xaddress = 0;
		/*计算目标地址*/
  Xaddress = CurrentFrameBuffer + 3*(LCD_PIXEL_WIDTH*Ypos + Xpos);
		
	__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
	DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
	DMA2D->CR=DMA2D_R2M;			//寄存器到存储器模式
	DMA2D->OPFCCR=DMA2D_OUTPUT_RGB888;	//设置颜色格式
	DMA2D->OOR=(LCD_PIXEL_WIDTH - Width);;				//设置行偏移 

	DMA2D->OMAR=Xaddress;				//输出存储器地址
	DMA2D->NLR=(Height)|((Width)<<16);	//设定行数寄存器
	DMA2D->OCOLR=CurrentTextColor;						//设定输出颜色寄存器 
	DMA2D->CR|=DMA2D_CR_START;				//启动DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;		//清除传输完成标志 
}
/**
  * @brief  Displays a rectangle.
  * @param  Xpos: specifies the X position, can be a value from 0 to 240.
  * @param  Ypos: specifies the Y position, can be a value from 0 to 320.
  * @param  Height: display rectangle height, can be a value from 0 to 320.
  * @param  Width: display rectangle width, can be a value from 0 to 240.
  * @retval None
  */
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* draw horizontal lines */
  LCD_DrawLine(Xpos, Ypos, Width, LCD_DIR_HORIZONTAL);
  LCD_DrawLine(Xpos, (Ypos+ Height), Width, LCD_DIR_HORIZONTAL);
  
  /* draw vertical lines */
  LCD_DrawLine(Xpos, Ypos, Height, LCD_DIR_VERTICAL);
  LCD_DrawLine((Xpos + Width), Ypos, Height, LCD_DIR_VERTICAL);
}
/**
 * @brief  缩放字模，缩放后的字模由1个像素点由8个数据位来表示
										0x01表示笔迹，0x00表示空白区
 * @param  in_width ：原始字符宽度
 * @param  in_heig ：原始字符高度
 * @param  out_width ：缩放后的字符宽度
 * @param  out_heig：缩放后的字符高度
 * @param  in_ptr ：字库输入指针	注意：1pixel 1bit
 * @param  out_ptr ：缩放后的字符输出指针 注意: 1pixel 8bit
 *		out_ptr实际上没有正常输出，改成了直接输出到全局指针zoomBuff中
 * @param  en_cn ：0为英文，1为中文
 * @retval 无
 */
void LCD_zoomChar(uint16_t in_width,	//原始字符宽度
									uint16_t in_heig,		//原始字符高度
									uint16_t out_width,	//缩放后的字符宽度
									uint16_t out_heig,	//缩放后的字符高度
									uint8_t *in_ptr,	//字库输入指针	注意：1pixel 1bit
									uint8_t *out_ptr, //缩放后的字符输出指针 注意: 1pixel 8bit
									uint8_t en_cn)		//0为英文，1为中文	
{
	uint8_t *pts,*ots;
	//根据源字模及目标字模大小，设定运算比例因子，左移16是为了把浮点运算转成定点运算
	unsigned int xrIntFloat_16=(in_width<<16)/out_width+1; 
  unsigned int yrIntFloat_16=(in_heig<<16)/out_heig+1;
	
	unsigned int srcy_16=0;
	unsigned int y,x;
	uint8_t *pSrcLine;
	uint8_t tempBuff[1024] = {0};
	uint32_t			uChar;
	uint16_t			charBit = in_width / 8;
	uint16_t			Bitdiff = 32 - in_width;
	
	//检查参数是否合法
	if(in_width >= 32) return;												//字库不允许超过32像素
	if(in_width * in_heig == 0) return;	
	if(in_width * in_heig >= 1024 ) return; 					//限制输入最大 32*32
	
	if(out_width * out_heig == 0) return;	
	if(out_width * out_heig >= ZOOMMAXBUFF ) return; //限制最大缩放 128*128
	pts = (uint8_t*)&tempBuff;
	
	//为方便运算，字库的数据由1 pixel 1bit 映射到1pixel 8bit
	//0x01表示笔迹，0x00表示空白区
	if(en_cn == 0x00)//英文
	{
		//这里以16 * 24字库作为测试，其他大小的字库自行根据下列代码做下映射就可以
		//英文和中文字库上下边界不对，可在此次调整。需要注意tempBuff防止溢出
			pts+=in_width*4;
			for(y=0;y<in_heig;y++)	
			{
				uChar = *(uint32_t *)(in_ptr + y * charBit) >> Bitdiff;
				for(x=0;x<in_width;x++)
					{
						*pts++ = (uChar >> x) & 0x01;
					}
			}		
	}
	else //中文
	{
			for(y=0;y<in_heig;y++)	
			{
				/*源字模数据*/
				uChar = in_ptr [ y * 3 ];
				uChar = ( uChar << 8 );
				uChar |= in_ptr [ y * 3 + 1 ];
				uChar = ( uChar << 8 );
				uChar |= in_ptr [ y * 3 + 2];
				/*映射*/
				for(x=0;x<in_width;x++)
					{
						if(((uChar << x) & 0x800000) == 0x800000)
							*pts++ = 0x01;
						else
							*pts++ = 0x00;
					}
			}		
	}

	//zoom过程
	pts = (uint8_t*)&tempBuff;	//映射后的源数据指针
	ots = (uint8_t*)&zoomBuff;	//输出数据的指针
	for (y=0;y<out_heig;y++)	/*行遍历*/
    {
				unsigned int srcx_16=0;
        pSrcLine=pts+in_width*(srcy_16>>16);				
        for (x=0;x<out_width;x++) /*行内像素遍历*/
        {
            ots[x]=pSrcLine[srcx_16>>16]; //把源字模数据复制到目标指针中
            srcx_16+=xrIntFloat_16;			//按比例偏移源像素点
        }
        srcy_16+=yrIntFloat_16;				  //按比例偏移源像素点
        ots+=out_width;						
    }
	/*！！！缩放后的字模数据直接存储到全局指针zoomBuff里了*/
	out_ptr = (uint8_t*)&zoomBuff;	//out_ptr没有正确传出，后面调用直接改成了全局变量指针！
	
	/*实际中如果使用out_ptr不需要下面这一句！！！
		只是因为out_ptr没有使用，会导致warning。强迫症*/
	out_ptr++; 
}			
/**
 * @brief  在显示器上显示一个中文字符
 * @param  usX ：在特定扫描方向下字符的起始X坐标
 * @param  usY ：在特定扫描方向下字符的起始Y坐标
 * @param  usChar ：要显示的中文字符（国标码）
 * @retval 无
 */ 
void LCD_DispChar_CH ( uint16_t usX, uint16_t usY, uint16_t usChar)
{
	uint8_t ucPage, ucColumn;
	uint8_t ucBuffer [ 24*24/8 ];	

  uint32_t usTemp; 	

	uint32_t  xpos =0;
  uint32_t  Xaddress = 0;
  
	/*xpos表示当前行的显存偏移位置*/
  xpos = usX*LCD_PIXEL_WIDTH*3;
	
	/*Xaddress表示像素点*/
  Xaddress += usY;
	   
  macGetGBKCode ( ucBuffer, usChar );	//取字模数据
	
	/*ucPage表示当前行数*/
	for ( ucPage = 0; ucPage < macHEIGHT_CH_CHAR; ucPage ++ )
	{
    /* 取出3个字节的数据，在lcd上即是一个汉字的一行 */
		usTemp = ucBuffer [ ucPage * 3 ];
		usTemp = ( usTemp << 8 );
		usTemp |= ucBuffer [ ucPage * 3 + 1 ];
		usTemp = ( usTemp << 8 );
		usTemp |= ucBuffer [ ucPage * 3 + 2];
	
		
		for ( ucColumn = 0; ucColumn < macWIDTH_CH_CHAR; ucColumn ++ ) 
		{			
			if ( usTemp & ( 0x01 << 23 ) )  //高位在前 				
			{
				//字体色
			  *(__IO uint16_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos) = (0x00FFFF & CurrentTextColor);        //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos+2) = (0xFF0000 & CurrentTextColor) >> 16; //R

			}				
			else	
			{
				//背景色
				*(__IO uint16_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos) = (0x00FFFF & CurrentBackColor);        //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos+2) = (0xFF0000 & CurrentBackColor) >> 16; //R

			}	
			/*指向当前行的下一个点*/	
			Xaddress++;			
			usTemp <<= 1;
			
		}
		/*显示完一行*/
		/*指向字符显示矩阵下一行的第一个像素点*/
		Xaddress += (LCD_PIXEL_WIDTH - macWIDTH_CH_CHAR);
		
	}
}
/**
 * @brief  利用缩放后的字模显示字符
 * @param  Xpos ：字符显示位置x
 * @param  Ypos ：字符显示位置y
 * @param  Font_width ：字符宽度
 * @param  Font_Heig：字符高度
 * @param  c ：要显示的字模数据
 * @param  DrawModel ：是否反色显示 
 * @retval 无
 */
void LCD_DrawChar_Ex(uint16_t Xpos, //字符显示位置x
												uint16_t Ypos, //字符显示位置y
												uint16_t Font_width, //字符宽度
												uint16_t Font_Heig,  //字符高度 
												uint8_t *c,						//字模数据
												uint16_t DrawModel)		//是否反色显示
{
  uint32_t index = 0, counter = 0, xpos =0;
  uint32_t  Xaddress = 0;
  
  xpos = Xpos*LCD_PIXEL_WIDTH*3;
  Xaddress += Ypos;
  
  for(index = 0; index < Font_Heig; index++)
  {
    
    for(counter = 0; counter < Font_width; counter++)
    {
      if(*c++ == DrawModel)	//根据字模及反色设置决定显示哪种颜色
      {
        *(__IO uint16_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos) = (0x00FFFF & CurrentBackColor);        //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos+2) = (0xFF0000 & CurrentBackColor) >> 16; //R
      }
      else
      {
        *(__IO uint16_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos) = (0x00FFFF & CurrentTextColor);        //GB
        *(__IO uint8_t*)(CurrentFrameBuffer + (3*Xaddress) + xpos+2) = (0xFF0000 & CurrentTextColor) >> 16; //R
      }
      Xaddress++;
    }
      Xaddress += (LCD_PIXEL_WIDTH - Font_width);
  }
}

/**
 * @brief  在显示器上显示中英文字符串,超出液晶宽度时会自动换行。
					 中英文混显示时，请把英文字体设置为Font16x24格式
 * @param  Line ：行(也可理解为y坐标)
 * @param  Column ：列（也可理解为x坐标）
 * @param  pStr ：要显示的字符串的首地址
 * @retval 无
 */
void LCD_DispString_EN_CH( uint16_t Line, uint16_t Column, const uint8_t * pStr )
{
	uint16_t usCh;
	
	
	while( * pStr != '\0' )
	{
		if ( * pStr <= 126 )	           	//英文字符
		{
	
			/*自动换行*/
			if ( ( Column + LCD_Currentfonts->Width ) > LCD_PIXEL_WIDTH )
			{
				Column = 0;
				Line += LCD_Currentfonts->Height;
			}
			
			if ( ( Line + LCD_Currentfonts->Height ) > LCD_PIXEL_HEIGHT )
			{
				Column = 0;
				Line = 0;
			}			
					
			LCD_DisplayChar(Line,Column,*pStr);
			
			Column += LCD_Currentfonts->Width;
		
		  pStr ++;

		}
		
		else	                            //汉字字符
		{
			if ( ( Column + macWIDTH_CH_CHAR ) > LCD_PIXEL_WIDTH )
			{
				Column = 0;
				Line += macHEIGHT_CH_CHAR;
			}
			
			if ( ( Line + macHEIGHT_CH_CHAR ) > LCD_PIXEL_HEIGHT )
			{
				Column = 0;
				Line = 0;
			}	
			
			/*一个汉字两字节*/
			usCh = * ( uint16_t * ) pStr;				
			usCh = ( usCh << 8 ) + ( usCh >> 8 );		

			LCD_DispChar_CH (Line,Column, usCh);
			
			Column += macWIDTH_CH_CHAR;
			
			pStr += 2;           //一个汉字两个字节 
		
    }
		
  }
	
	
}  

/**
  * @brief  显示一行字符，若超出液晶宽度，不自动换行。
						中英混显时，请把英文字体设置为Font16x24格式
  * @param  Line: 要显示的行编号LINE(0) - LINE(N)
  * @param  *ptr: 要显示的字符串指针
  * @retval None
  */
void LCD_DisplayStringLine_EN_CH(uint16_t Line, uint8_t *ptr)
{  
  uint16_t refcolumn = 0;
  /* Send the string character by character on lCD */
  while ((refcolumn < LCD_PIXEL_WIDTH) && ((*ptr != 0) & (((refcolumn + LCD_Currentfonts->Width) & 0xFFFF) >= LCD_Currentfonts->Width)))
  {
    /* Display one character on LCD */
		if ( * ptr <= 126 )	           	//英文字符
		{
					
			LCD_DisplayChar(Line, refcolumn, *ptr);
			/* Decrement the column position by width */
			refcolumn += LCD_Currentfonts->Width;
			/* Point on the next character */
			ptr++;
		}
		
		else	                            //汉字字符
		{	
			uint16_t usCh;
			
			/*一个汉字两字节*/
			usCh = * ( uint16_t * ) ptr;				
			usCh = ( usCh << 8 ) + ( usCh >> 8 );		
			
			LCD_DispChar_CH ( Line, refcolumn, usCh );
			refcolumn += macWIDTH_CH_CHAR;

			ptr += 2; 		
    }	

  }
}

/**
 * @brief  利用缩放后的字模显示字符串
 * @param  Xpos ：字符显示位置x
 * @param  Ypos ：字符显示位置y
 * @param  Font_width ：字符宽度，英文字符在此基础上/2。注意为偶数
 * @param  Font_Heig：字符高度，注意为偶数
 * @param  c ：要显示的字符串
 * @param  DrawModel ：是否反色显示 
 * @retval 无
 */
void LCD_DisplayStringLineEx(uint16_t x, 		//字符显示位置x
														 uint16_t y, 				//字符显示位置y
														 uint16_t Font_width,	//要显示的字体宽度，英文字符在此基础上/2。注意为偶数
														 uint16_t Font_Heig,	//要显示的字体高度，注意为偶数
														 uint8_t *ptr,					//显示的字符内容
														 uint16_t DrawModel)  //是否反色显示
{
	uint16_t refcolumn = x; //x坐标
	uint16_t Charwidth;
	uint8_t *psr;
	uint8_t Ascii;	//英文
	uint16_t usCh;  //中文
	uint8_t ucBuffer [ 24*24/8 ];	
	
	while ((refcolumn < LCD_PIXEL_WIDTH) && ((*ptr != 0) & (((refcolumn + LCD_Currentfonts->Width) & 0xFFFF) >= LCD_Currentfonts->Width)))
	{
		if(*ptr > 0x80) //如果是中文
		{
			Charwidth = Font_width;
			usCh = * ( uint16_t * ) ptr;				
			usCh = ( usCh << 8 ) + ( usCh >> 8 );
			macGetGBKCode ( ucBuffer, usCh );	//取字模数据
			//缩放字模数据
			LCD_zoomChar(24,24,Charwidth,Font_Heig,(uint8_t *)&ucBuffer,psr,1); 
			//显示单个字符
			LCD_DrawChar_Ex(y,refcolumn,Charwidth,Font_Heig,(uint8_t*)&zoomBuff,DrawModel);
			refcolumn+=Charwidth;
			ptr+=2;
		}
		else
		{
				Charwidth = Font_width / 2;
				Ascii = *ptr - 32;
				//缩放字模数据
				LCD_zoomChar(16,24,Charwidth,Font_Heig,(uint8_t *)&LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height],psr,0);
			  //显示单个字符
				LCD_DrawChar_Ex(y,refcolumn,Charwidth,Font_Heig,(uint8_t*)&zoomBuff,DrawModel);
				refcolumn+=Charwidth;
				ptr++;
		}
	}
}
