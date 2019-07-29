/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef HOME_VIEW_BASE_HPP
#define HOME_VIEW_BASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/home_screen/HOMEPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class HOMEViewBase : public touchgfx::View<HOMEPresenter>
{
public:
    HOMEViewBase();
    virtual ~HOMEViewBase() {}

    virtual void setupScreen();
    virtual void handleKeyEvent(uint8_t key);

    /*
     * Custom Action Handlers
     */
    virtual void SwitchANT1()
    {
        // Override and implement this function in HOMEView
    }

    virtual void togglelight()
    {
        // Override and implement this function in HOMEView
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box box1;
    touchgfx::ToggleButton toggleButton1;
    touchgfx::Button button1;
    touchgfx::TextArea textArea1;
    touchgfx::Button button3;
    touchgfx::TextArea textArea2;
    touchgfx::Button button4;
    touchgfx::TextArea textArea3;
    touchgfx::Button button2;
    touchgfx::TextArea textArea4;

private:

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Callback Declarations
     */
    touchgfx::Callback<HOMEViewBase, const touchgfx::AbstractButton&> buttonCallback;

};

#endif // HOME_VIEW_BASE_HPP