#include "GameOver.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "GameStart.h"
#include "ResourceManager.h"

GameOver::GameOver()
{
	RM.getSound("gameOver")->play();
	setType("gameover");
	setLocation(df::CENTER_CENTER);
	setSprite("gameover");
	deleteCountdown = 100;
	// Deletes generator first to make sure no new objects spawn
	df::ObjectList allObjects = WM.getAllObjects();
	df::ObjectListIterator oli(&allObjects);

	//Delete sharks, spawners and coins and generator
	for (oli.first(); !oli.isDone(); oli.next()) {
		df::Object* p_o = oli.currentObject();
		if (p_o->getType() == "shark" || p_o->getType() == "spawner" || p_o->getType() == "coin" || p_o->getType() == "generator")
			WM.markForDelete(p_o);
	}
	df::Vector p(WM.getView().getHorizontal() * 3 / 6,
		WM.getView().getVertical() / 2);
	setPosition(DM.viewToWorld(p));
}

GameOver::~GameOver()
{
	// Deletes viewObjects
	df::ObjectList allObjects = WM.getAllObjects();
	df::ObjectListIterator oli(&allObjects);
	for (oli.first(); !oli.isDone(); oli.next()) {
		df::Object* p_o = oli.currentObject();
		if (p_o->getType() == "ViewObject")
			WM.markForDelete(p_o);
	}
	new GameStart();
}

//Override to display as sprite
int GameOver::draw()
{

	return df::Object::draw();
}

//Gets step event
int GameOver::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		deleteCountdown--;
		if (deleteCountdown <= 0)
			WM.markForDelete(this);
		return 1;
	}
	return 0;
}
