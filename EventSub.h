#pragma once
#include "Event.h"
#include "Sub.h"

const std::string SUB_EVENT = "df::sub";

class EventSub : public df::Event {
private:
	Sub* sub;


public:
	EventSub(Sub* sub);
	Sub* getSub() const;
};
