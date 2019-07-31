#ifndef HOME_PRESENTER_HPP
#define HOME_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HOMEView;

class HOMEPresenter : public Presenter, public ModelListener
{
public:
    HOMEPresenter(HOMEView& v);

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

    virtual ~HOMEPresenter() {};
    void set_light_onoff(uint8_t data)
		{
			model->set_light_onoff(data);
		}
	virtual void key_event();
private:
    HOMEPresenter();

    HOMEView& view;
};


#endif // HOME_PRESENTER_HPP
