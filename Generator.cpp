#include "Generator.h"
#include "EventStep.h"
#include "WorldManager.h"
#include <stdlib.h>
#include "LogManager.h"
#include "Spawner.h"
#include "DisplayManager.h"

Generator::Generator()
{
	setType("Generator");
	setSolidness(df::SPECTRAL);
	sub = new Sub();
	spawner_slowdown = 450;
	spawner_countdown = 30;
}

//Empty draw function as generator should not be drawn
int Generator::draw()
{
	return 0;
}

int Generator::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		spawnSpawner();
		spawnCoin();
		return 1;
	}
	return 0;
}

void Generator::spawnSpawner()
{
	spawner_countdown--;
	if (spawner_countdown > 0)
		return;
	spawner_countdown = spawner_slowdown;
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
	Spawner* spawner = new Spawner(pos);
	df::ObjectList collisions = WM.getCollisions(spawner, pos);
	while (!collisions.isEmpty() || !WM.boxIntersectsBox(WM.getWorldBox(spawner, pos), WM.getBoundary())) {
		pos.setX((pos.getX() + 1 % (int)WM.getBoundary().getHorizontal()));
		collisions = WM.getCollisions(spawner, pos);
		counter--;
		if (counter < 0) {
			pos = df::Vector(3, 3);
			break;
		}
	}
	spawner->setPosition(pos);
}

void Generator::spawnCoin()
{
}

