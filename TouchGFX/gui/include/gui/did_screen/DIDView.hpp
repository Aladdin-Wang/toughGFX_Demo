#ifndef DID_VIEW_HPP
#define DID_VIEW_HPP

#include <gui_generated/did_screen/DIDViewBase.hpp>
#include <gui/did_screen/DIDPresenter.hpp>

class DIDView : public DIDViewBase
{
public:
    DIDView();
    virtual ~DIDView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void ReadDIDClicked();
    virtual void ClearDIDClicked();
protected:
};

#endif // DID_VIEW_HPP
