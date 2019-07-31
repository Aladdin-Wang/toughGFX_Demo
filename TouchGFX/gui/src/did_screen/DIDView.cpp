#include <gui/did_screen/DIDView.hpp>

DIDView::DIDView()
{

}

void DIDView::setupScreen()
{
    DIDViewBase::setupScreen();
}

void DIDView::tearDownScreen()
{
    DIDViewBase::tearDownScreen();
}
void DIDView::ClearDIDClicked()
{
    memset(textHWVersionBuffer,0,10);
    memset(textSWVersionBuffer,0,10);
    textHWVersion.invalidate();
    textSWVersion.invalidate();
    presenter->ClearDID();
}
void DIDView::ReadDIDClicked()
{
	Unicode::strncpy(textHWVersionBuffer, "V0.23", 10);
    textHWVersion.invalidate();
    
	Unicode::strncpy(textSWVersionBuffer, "V0.02", 10);
    textSWVersion.invalidate();
	
	presenter->ReadDID();
}

