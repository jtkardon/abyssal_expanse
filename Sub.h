#pragma once
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"

class Sub : public df::Object {
private:
	int laser_countdown;
	int laser_slowdown;
	int harpoon_countdown;
	int harpoon_slowdown;
	int dirFacing; // 1 = right, -1 = left
	int health;
	void keyHandler(const df::EventKeyboard* p_keyboard_event);
	void mouseHandler(const df::EventMouse* p_mouse_event);
	void collide(const df::EventCollision* p_collision_event);
	void moveX(float delta);
	void moveY(float delta);
	void fireLaser();
	
public:
	Sub();
	~Sub();
	int eventHandler(const df::Event* p_e) override;
	int getDirFacing();
	
};