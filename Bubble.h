#pragma once
#include "Object.h"


class Bubble : public df::Object {
private:
	char bubbleChar;
public:
	Bubble(bool first);
	int draw() override;
	int eventHandler(const df::Event* p_e);
};