#include <gui/home_screen/HOMEView.hpp>
#include <gui/home_screen/HOMEPresenter.hpp>
#include "main.h"
HOMEPresenter::HOMEPresenter(HOMEView& v)
    : view(v)
{
}

void HOMEPresenter::activate()
{

}

void HOMEPresenter::deactivate()
{

}
void HOMEPresenter:: key_event()
{
	view.handleKeyEvent(UBP_KEY);
}

