#include <gui/updata_screen/UPDATAView.hpp>

UPDATAView::UPDATAView()
{

}

void UPDATAView::setupScreen()
{
    UPDATAViewBase::setupScreen();
}

void UPDATAView::tearDownScreen()
{
    UPDATAViewBase::tearDownScreen();
}
void UPDATAView::StartUpClicked()
{
    presenter->StartUp();
}
void UPDATAView::RefreshDataClicked()
{
    presenter->RefreshData();
}
void UPDATAView::RtextSDCardView(uint8_t * data)
{
	for(uint8_t i=0;i<LONGTEXT_SIZE;i++)
	{
		longTextBuffer[i] = (uint16_t)data[i];
	}
    longText.invalidate();
}

