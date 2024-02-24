#pragma once
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

class Sub : public df::Object {
private:
	int laser_countdown;
	int laser_slowdown;
	int dirFacing; // 1 = right, -1 = left
	void keyHandler(const df::EventKeyboard* p_keyboard_event);
	void mouseHandler(const df::EventMouse* p_mouse_event);
	void moveX(float delta);
	void moveY(float delta);
	
public:
	Sub();
	~Sub();
	int eventHandler(const df::Event* p_e) override;
};