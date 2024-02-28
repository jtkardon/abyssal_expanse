#pragma once
#include "Object.h"
#include "EventStep.h"
#include "EventCollision.h"

class Spawner : public df::Object {
private:
	int health;
	int maxHealth;
	int spawn_slowdown;
	int spawn_countdown;
	int* weaponHitByID;
	void step();
	void collide(const df::EventCollision* p_collision_event);


public:
	Spawner(df::Vector pos);
	~Spawner();
	int eventHandler(const df::Event* p_e) override;

};