#pragma once
#include "Object.h"
#include "Sub.h"
#include "EventCollision.h"
#include "ObjectList.h"

class Shark : public df::Object {
private:
	Sub* sub;
	int health;
	int weaponHitByID;
	float changedSpeed;
	void step(int count);
	void collide(const df::EventCollision* p_collision_event);

		
public:
	Shark(df::Vector pos);
	~Shark();
	int eventHandler(const df::Event* p_e) override;
};