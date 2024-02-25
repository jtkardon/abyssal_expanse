#include "Generator.h"
#include "EventStep.h"
#include "WorldManager.h"
#include <stdlib.h>
#include "LogManager.h"
#include "Spawner.h"
#include "DisplayManager.h"
#include "Coin.h"
Generator::Generator()
{
	setType("Generator");
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

int Generator::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		spawn("spawner");
		spawn("coin");
		return 1;
	}
	return 0;
}

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
	df::Vector pos((float)(rand() % (int)(WM.getBoundary().getHorizontal() - 5) + 5),
		(float)(rand() % (int)(WM.getBoundary().getVertical() - 5)) + 5);

	//Counter just breaks the while loop after 10 times to prevent lag
	int counter = 50;
	//Makes sure that spawner is not within certain units of sub
	while (pos.getX() > sub->getPosition().getX() - 30 &&
		pos.getX() < sub->getPosition().getX() + 30 &&
		pos.getY() > sub->getPosition().getY() - 7 &&
		pos.getY() < sub->getPosition().getY() + 7) 
	{
		pos = df::Vector((float)(rand() % (int)(WM.getBoundary().getHorizontal() - 5) + 5),
			(float)(rand() % (int)(WM.getBoundary().getVertical() - 5)) + 5);
		counter--;
		if (counter < 0)
			break;
	}

	counter = 50;
	if (type == "spawner") {
		Spawner* object = new Spawner(pos);
		df::ObjectList collisions = WM.getCollisions(object, pos);
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
	else if (type == "coin") {
		Coin* object = new Coin(pos);
		df::ObjectList collisions = WM.getCollisions(object, pos);
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


