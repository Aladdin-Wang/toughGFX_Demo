#ifndef KEY_VIEW_HPP
#define KEY_VIEW_HPP

#include <gui_generated/key_screen/KEYViewBase.hpp>
#include <gui/key_screen/KEYPresenter.hpp>

class KEYView : public KEYViewBase
{
public:
    KEYView();
    virtual ~KEYView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // KEY_VIEW_HPP
