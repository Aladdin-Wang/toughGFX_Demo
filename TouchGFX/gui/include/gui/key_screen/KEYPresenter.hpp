#ifndef KEY_PRESENTER_HPP
#define KEY_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class KEYView;

class KEYPresenter : public Presenter, public ModelListener
{
public:
    KEYPresenter(KEYView& v);

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

    virtual ~KEYPresenter() {};

private:
    KEYPresenter();

    KEYView& view;
};


#endif // KEY_PRESENTER_HPP
