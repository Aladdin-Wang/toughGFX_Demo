#ifndef UPDATA_PRESENTER_HPP
#define UPDATA_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class UPDATAView;

class UPDATAPresenter : public Presenter, public ModelListener
{
public:
    UPDATAPresenter(UPDATAView& v);

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

    virtual ~UPDATAPresenter() {};
    void StartUp()  
    {
        model->StartUp();
    }
    void RefreshData()
    {
        model->RefreshData();
    }
    virtual void RtextSDCardView(uint8_t * data);
private:
    UPDATAPresenter();

    UPDATAView& view;
};


#endif // UPDATA_PRESENTER_HPP
