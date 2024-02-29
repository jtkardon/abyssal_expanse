#pragma once
#include "Object.h"
#include "Music.h"
class GameStart : public df::Object {
private:
	Music* titleMusic;

public:
	GameStart();
	int eventHandler(const df::Event* p_e) override;
};