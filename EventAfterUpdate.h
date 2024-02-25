#pragma once
#include "Event.h"


const std::string AFTER_UPDATE_EVENT = "df::after_update";

class EventAfterUpdate : public df::Event {

public:
	EventAfterUpdate();
};
