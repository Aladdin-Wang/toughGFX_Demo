#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os.h"
#include "main.h"
extern osMessageQId gui_msg_qHandle;
extern osMessageQId hal_msg_qHandle;

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
	osEvent retkey;
	retkey = osMessageGet(hal_msg_qHandle,1);
	if(retkey.status == osEventMessage)
	{
		if(retkey.value.v == UBP_KEY)
		{
			modelListener->key_event();
		}
		if(retkey.value.v > 0x20000000)
		{
			modelListener->RtextSDCardView((uint8_t *)retkey.value.p);
		}
	}

}
void Model::set_light_onoff(uint8_t data)
{
	osMessagePut(gui_msg_qHandle,data,200);
}
void Model::ReadDID()
{
	
}
void Model::ClearDID()
{

}
void Model::StartUp()
{
	osMessagePut(gui_msg_qHandle,UBP_START,200);
}
void Model::RefreshData()
{
	osMessagePut(gui_msg_qHandle,UBP_REFRESH,200);
}

