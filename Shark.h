#pragma once
#include "Object.h"
#include "Sub.h"

class Shark : public df::Object {
private:
	void step(int count);
	Sub* sub;

public:
	Shark(df::Vector pos);
	int eventHandler(const df::Event* p_e) override;
};