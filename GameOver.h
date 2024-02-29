#pragma once
#include "ViewObject.h"

class GameOver : public df::ViewObject {
private:
	int deleteCountdown;
	int score;

public:
	GameOver(int score);
	~GameOver();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
};