#include <gui/updata_screen/UPDATAView.hpp>
#include <gui/updata_screen/UPDATAPresenter.hpp>

UPDATAPresenter::UPDATAPresenter(UPDATAView& v)
    : view(v)
{
}

void UPDATAPresenter::activate()
{

}

void UPDATAPresenter::deactivate()
{

}
void UPDATAPresenter::RtextSDCardView(uint8_t * data)
{
    view.RtextSDCardView(data);
}
