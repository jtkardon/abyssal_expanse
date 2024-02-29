#include "Generator.h"
#include "EventStep.h"
#include "WorldManager.h"
#include <stdlib.h>
#include "LogManager.h"
#include "Spawner.h"
#include "DisplayManager.h"
#include "Coin.h"

//The Generator creates objects after a certain amount of frames
//Creates a spawner in random locations every 450 frames
//Creates a coin in a random location every 150 frames
Generator::Generator()
{
	setType("generator");
	setSolidness(df::SPECTRAL);
	sub = new Sub();
	spawner_slowdown = 450;
	spawner_countdown = 30;
	coin_slowdown = 150;
	coin_countdown = coin_slowdown;
}

//Empty draw function as generator should not be drawn
int Generator::draw()
{
	return 0;
}

//Deals with step event
int Generator::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		spawn("spawner");
		spawn("coin");
		return 1;
	}
	return 0;
}


//Spawning code is similar so using same function with different parameter
//Spawns one of the type of object in a random location
void Generator::spawn(std::string type)
{
	if (type == "spawner") {
		spawner_countdown--;
		if (spawner_countdown > 0)
			return;
		spawner_countdown = spawner_slowdown;
	}
	else if (type == "coin") {
		coin_countdown--;
		if (coin_countdown > 0)
			return;
		coin_countdown = coin_slowdown;
	}

	//First get a random position in the world, at least 5 units away from top and left walls
	df::Vector pos((float)(rand() % (int)(WM.getBoundary().getHorizontal() - 5)),
		(float)(rand() % (int)(WM.getBoundary().getVertical() - 5)));

	//Counter just breaks the while loop after 10 times to prevent lag
	int counter = 50;
	//Makes sure that object is not within certain units of sub (30 units x, 7 units 7)
	//Will keep randomizing until it is good
	while (pos.getX() > sub->getPosition().getX() - 30 &&
		pos.getX() < sub->getPosition().getX() + 30 &&
		pos.getY() > sub->getPosition().getY() - 7 &&
		pos.getY() < sub->getPosition().getY() + 7) 
	{
		pos = df::Vector((float)(rand() % (int)(WM.getBoundary().getHorizontal() - 5)),
			(float)(rand() % (int)(WM.getBoundary().getVertical() - 5)));
		counter--;
		if (counter < 0)
			break;
	}

	counter = 50;
	
	if (type == "spawner") { //Spawner
		Spawner* object = new Spawner(pos);
		df::ObjectList collisions = WM.getCollisions(object, pos);
		//Makes sure object is not colliding with another object
		while (!collisions.isEmpty() || !WM.boxIntersectsBox(WM.getWorldBox(object, pos), WM.getBoundary())) {
			pos.setX((pos.getX() + 1 % (int)WM.getBoundary().getHorizontal()));
			collisions = WM.getCollisions(object, pos);
			counter--;
			if (counter < 0) {
				pos = df::Vector(3, 3);
				break;
			}
		}
		object->setPosition(pos);
	}
	else if (type == "coin") { //Coin
		Coin* object = new Coin(pos);
		df::ObjectList collisions = WM.getCollisions(object, pos);
		//Makes sure object is not colliding with another object
		while (!collisions.isEmpty() || !WM.boxIntersectsBox(WM.getWorldBox(object, pos), WM.getBoundary())) {
			pos.setX((pos.getX() + 1 % (int)WM.getBoundary().getHorizontal()));
			collisions = WM.getCollisions(object, pos);
			counter--;
			if (counter < 0) {
				pos = df::Vector(3, 3);
				break;
			}
		}
		object->setPosition(pos);
	}
}


