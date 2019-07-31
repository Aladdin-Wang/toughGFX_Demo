#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os.h"
#include "main.h"
extern osMessageQId gui_msg_qHandle;
Model::Model() : modelListener(0)
{
}

void Model::tick()
{
	osEvent retkey;
	retkey = osMessageGet(gui_msg_qHandle,1);
	if(retkey.value.v == UBP_KEY)
	{
		modelListener->key_event();
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
