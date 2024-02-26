#include "Coin.h"
#include "LogManager.h"
Coin::Coin(df::Vector pos)
{
	setType("coin");
	setSprite("coin");
	setPosition(pos);
	setAltitude(3);
	setSolidness(df::SOFT);
}
