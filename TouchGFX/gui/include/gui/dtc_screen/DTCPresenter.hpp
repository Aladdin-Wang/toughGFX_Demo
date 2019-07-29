#ifndef DTC_PRESENTER_HPP
#define DTC_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DTCView;

class DTCPresenter : public Presenter, public ModelListener
{
public:
    DTCPresenter(DTCView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~DTCPresenter() {};

private:
    DTCPresenter();

    DTCView& view;
};


#endif // DTC_PRESENTER_HPP
