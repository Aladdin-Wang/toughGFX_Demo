#include "GUI.h"
#include "gt9xx.h"

extern int16_t pre_x;
extern int16_t pre_y;
void GUI_TOUCH_X_ActivateX(void) 
{
 
}


void GUI_TOUCH_X_ActivateY(void)
{

}

int  GUI_TOUCH_X_MeasureX(void) 
{
	int32_t xvalue;
		GT9xx_GetOnePiont();
		xvalue=pre_x;
		return xvalue;
}

int  GUI_TOUCH_X_MeasureY(void) 
{	
	int32_t yvalue;
    
		GT9xx_GetOnePiont();
		yvalue = pre_y;
		return yvalue;
}
