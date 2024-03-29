#include "Spawner.h"
#include "Shark.h"
#include "WorldManager.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"

Spawner::Spawner(df::Vector pos)
{
	setType("spawner");
	setAltitude(1);
	setSprite("spawner");

	spawn_slowdown = 90;
	spawn_countdown = 30;
	setPosition(pos);
	
	maxHealth = 5;
	health = maxHealth;
	weaponHitByID = new int[maxHealth];
	df::Sound* spawnerCreated = RM.getSound("spawnerCreated");
	spawnerCreated->play();
}

Spawner::~Spawner() {
	df::EventView ev("Score", 50, true);
	WM.onEvent(&ev);
}

//Handles step, collision events
int Spawner::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	else if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_collision_event);
	}
	return 0;
}

//Every 90 frames, spawn a shark at the spawner's location
void Spawner::step() {
	spawn_countdown--;
	if (spawn_countdown > 0) {
		return;
	}
	spawn_countdown = spawn_slowdown;
	
	new Shark(getPosition());
}

//Handles collisions
void Spawner::collide(const df::EventCollision* p_collision_event)
{
	if (p_collision_event->getObject1()->getType() == "weapon" ||
		p_collision_event->getObject2()->getType() == "weapon" ||
		p_collision_event->getObject1()->getType() == "harpoon" ||
		p_collision_event->getObject2()->getType() == "harpoon") {

		bool oneIsWeapon = false;

		//Make sure the shark isn't hit by the same weapon twice
		for (int i = 0; i < maxHealth; i++) {
			if (p_collision_event->getObject1()->getType() == "weapon" || p_collision_event->getObject1()->getType() == "harpoon") {
				if (weaponHitByID[i] == p_collision_event->getObject1()->getId()) //If already hit by this weapon, ignore the collision
					return;
				oneIsWeapon = true;
			}
			else {
				if (weaponHitByID[i] == p_collision_event->getObject2()->getId()) //If already hit by this weapon, ignore the collision
					return;
			}
		}

		//Test to only get the id of the weapon
		if (oneIsWeapon) {
			weaponHitByID[maxHealth - health] = p_collision_event->getObject1()->getId();
		}
		else {
			weaponHitByID[maxHealth - health] = p_collision_event->getObject2()->getId();
		}
		
		health--;
		if (health <= 0) {
	
			WM.markForDelete(this);
		}
	}
}
