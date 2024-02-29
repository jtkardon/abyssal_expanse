#pragma once
#include "ViewObject.h"

class GameOver : public df::ViewObject {
private:
	int deleteCountdown;

public:
	GameOver();
	~GameOver();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
};