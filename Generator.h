#pragma once
#include "Object.h"
#include "Sub.h"
class Generator : public df::Object {
private:
	int spawner_slowdown;
	int spawner_countdown;
	int coin_slowdown;
	int coin_countdown;
	void spawn(std::string type);
	Sub* sub;

public:
	Generator();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
};