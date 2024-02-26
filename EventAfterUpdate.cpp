#include "EventAfterUpdate.h"

//This is to send a signal every frame after objects haved moved but before anything is drawn on screen
//It is used to make sure the harpoon stays exactly with the sub
EventAfterUpdate::EventAfterUpdate()
{
	setType(AFTER_UPDATE_EVENT);
}
