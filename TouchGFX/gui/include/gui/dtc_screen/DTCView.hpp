#ifndef DTC_VIEW_HPP
#define DTC_VIEW_HPP

#include <gui_generated/dtc_screen/DTCViewBase.hpp>
#include <gui/dtc_screen/DTCPresenter.hpp>

class DTCView : public DTCViewBase
{
public:
    DTCView();
    virtual ~DTCView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DTC_VIEW_HPP
