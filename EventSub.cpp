#include "EventSub.h"
//This is so other objects can get the sub's attributes
//Mostly used by shark to get position of sub for pathfinding
EventSub::EventSub(Sub* sub)
{
	setType(SUB_EVENT);
	this->sub = sub;
}

Sub* EventSub::getSub() const
{
	return sub;
}
