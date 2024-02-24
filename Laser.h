#pragma once
#include "Object.h"

class Laser : public df::Object {

public:
	Laser();
	int eventHandler(const df::Event* p_e) override;
};