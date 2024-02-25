#pragma once
#include "Object.h"
#include "EventCollision.h"

class Laser : public df::Object {
private:
	void collide(const df::EventCollision* p_collision_event);

public:
	Laser();
	int eventHandler(const df::Event* p_e) override;
};