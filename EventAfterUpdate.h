#pragma once
#include "Event.h"


const std::string AFTER_UPDATE_EVENT = "df::after_update";
//This is to send a signal every frame after objects haved moved but before anything is drawn on screen
//It is used to make sure the harpoon stays exactly with the sub
class EventAfterUpdate : public df::Event {

public:
	EventAfterUpdate();
};
