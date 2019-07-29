#ifndef HOME_VIEW_HPP
#define HOME_VIEW_HPP

#include <gui_generated/home_screen/HOMEViewBase.hpp>
#include <gui/home_screen/HOMEPresenter.hpp>

class HOMEView : public HOMEViewBase
{
public:
    HOMEView();
    virtual ~HOMEView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void togglelight();
		virtual void SwitchANT1();
protected:
};

#endif // HOME_VIEW_HPP
