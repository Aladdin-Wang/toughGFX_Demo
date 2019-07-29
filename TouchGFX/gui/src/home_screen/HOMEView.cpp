#include <gui/home_screen/HOMEView.hpp>
#include "main.h"
HOMEView::HOMEView()
{

}

void HOMEView::setupScreen()
{
    HOMEViewBase::setupScreen();
}

void HOMEView::tearDownScreen()
{
    HOMEViewBase::tearDownScreen();
}
void HOMEView::SwitchANT1()
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

void HOMEView::togglelight()
{
		application().gotoDIDScreenNoTransition();
}

