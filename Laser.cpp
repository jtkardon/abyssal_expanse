#include "Laser.h"
#include "LogManager.h"
#include "EventOut.h"
#include "WorldManager.h"

Laser::Laser()
{
    //setSprite("laser");
    setSolidness(df::SOFT);
    setType("weapon");
    //df::Vector new_pos = df::Vector(sub_pos.getX() )
    //setPosition(sub_pos);
    setSpeed(1);
}

int Laser::eventHandler(const df::Event* p_e)
{
    if (p_e->getType() == df::OUT_EVENT) {
        WM.markForDelete(this);
        return 1;
    }
    return 0;
}
