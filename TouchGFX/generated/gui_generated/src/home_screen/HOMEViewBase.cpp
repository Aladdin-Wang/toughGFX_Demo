/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/home_screen/HOMEViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

HOMEViewBase::HOMEViewBase() :
    buttonCallback(this, &HOMEViewBase::buttonCallbackHandler)
{
    box1.setPosition(0, 0, 800, 480);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(101, 66, 71));

    toggleButton1.setXY(332, 358);
    toggleButton1.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
    toggleButton1.setAction(buttonCallback);

    buttonWithDID.setXY(55, 51);
    buttonWithDID.setBitmaps(Bitmap(BITMAP_B4_ID), Bitmap(BITMAP_B4_ID));
    buttonWithDID.setAction(buttonCallback);

    textArea1.setXY(77, 120);
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(TypedText(T_SINGLEUSEID5));

    buttonWithUpdata.setXY(278, 51);
    buttonWithUpdata.setBitmaps(Bitmap(BITMAP_B5_ID), Bitmap(BITMAP_B5_ID));
    buttonWithUpdata.setAction(buttonCallback);

    textArea2.setXY(289, 120);
    textArea2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(TypedText(T_SINGLEUSEID6));

    buttonWithKey.setXY(389, 51);
    buttonWithKey.setBitmaps(Bitmap(BITMAP_B7_ID), Bitmap(BITMAP_B7_ID));
    buttonWithKey.setAction(buttonCallback);

    textArea3.setXY(412, 120);
    textArea3.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea3.setLinespacing(0);
    textArea3.setTypedText(TypedText(T_SINGLEUSEID7));

    buttonWithDTC.setXY(165, 51);
    buttonWithDTC.setBitmaps(Bitmap(BITMAP_B10_ID), Bitmap(BITMAP_B10_ID));
    buttonWithDTC.setAction(buttonCallback);

    textArea4.setXY(187, 120);
    textArea4.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea4.setLinespacing(0);
    textArea4.setTypedText(TypedText(T_SINGLEUSEID8));

    add(box1);
    add(toggleButton1);
    add(buttonWithDID);
    add(textArea1);
    add(buttonWithUpdata);
    add(textArea2);
    add(buttonWithKey);
    add(textArea3);
    add(buttonWithDTC);
    add(textArea4);
}

void HOMEViewBase::setupScreen()
{

}

//Handles when a key is pressed
void HOMEViewBase::handleKeyEvent(uint8_t key)
{
    if(1 == key)
    {
        //Interaction3
        //When hardware button 1 clicked call virtual function
        //Call togglelight
        togglelight();
    }
}

void HOMEViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &toggleButton1)
    {
        //Interaction2
        //When toggleButton1 clicked call virtual function
        //Call SwitchANT1
        SwitchANT1();
    }
    else if (&src == &buttonWithDID)
    {
        //ButtonToDID
        //When buttonWithDID clicked change screen to DID
        //Go to DID with no screen transition
        application().gotoDIDScreenNoTransition();
    }
    else if (&src == &buttonWithUpdata)
    {
        //ButtonToUpdata
        //When buttonWithUpdata clicked change screen to UPDATA
        //Go to UPDATA with no screen transition
        application().gotoUPDATAScreenNoTransition();
    }
    else if (&src == &buttonWithKey)
    {
        //ButtonToKEY
        //When buttonWithKey clicked change screen to KEY
        //Go to KEY with no screen transition
        application().gotoKEYScreenNoTransition();
    }
    else if (&src == &buttonWithDTC)
    {
        //ButtonToDTC
        //When buttonWithDTC clicked change screen to DTC
        //Go to DTC with no screen transition
        application().gotoDTCScreenNoTransition();
    }
}
