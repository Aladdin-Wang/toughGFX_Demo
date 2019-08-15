#ifndef UPDATA_VIEW_HPP
#define UPDATA_VIEW_HPP

#include <gui_generated/updata_screen/UPDATAViewBase.hpp>
#include <gui/updata_screen/UPDATAPresenter.hpp>

class UPDATAView : public UPDATAViewBase
{
public:
    UPDATAView();
    virtual ~UPDATAView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void RefreshDataClicked();
    virtual void StartUpClicked();
    virtual void RtextSDCardView(uint8_t * data);
protected:
};

#endif // UPDATA_VIEW_HPP
