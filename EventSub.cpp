#include "EventSub.h"

EventSub::EventSub(Sub* sub)
{
	setType(SUB_EVENT);
	this->sub = sub;
}

Sub* EventSub::getSub() const
{
	return sub;
}
