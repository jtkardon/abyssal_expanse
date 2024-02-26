#pragma once
#include "Object.h"
#include "EventCollision.h"
#include "Sub.h"
class Harpoon : public df::Object {
private:
	Sub* sub;
	int x_offset;
	bool goingBack;

public:
	Harpoon(Sub* sub);
	int eventHandler(const df::Event* p_e) override;
};