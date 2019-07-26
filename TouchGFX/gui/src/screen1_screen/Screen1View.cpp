#include <gui/screen1_screen/Screen1View.hpp>
#include "main.h"
Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::SwitchANT1()
{
		if(toggleButton1.getState() == true)
		{
			presenter->set_light_onoff(UBP_LIGHT_ON);
		}
		else
		{
			presenter->set_light_onoff(UBP_LIGHT_OFF);
		}
}

void Screen1View::togglelight()
{
		application().gotoScreen2ScreenNoTransition();
}
