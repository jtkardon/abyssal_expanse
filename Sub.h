#pragma once
#include "Object.h"
#include "EventKeyboard.h"

class Sub : public df::Object {
private:
	void keyHandler(const df::EventKeyboard* p_keyboard_event);
	void moveX(float delta);
	void moveY(float delta);
	
public:
	Sub();
	~Sub();
	int eventHandler(const df::Event* p_e) override;
};