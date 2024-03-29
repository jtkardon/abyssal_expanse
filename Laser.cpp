#include "Laser.h"
#include "LogManager.h"
#include "EventOut.h"
#include "WorldManager.h"

Laser::Laser()
{
    setSolidness(df::SOFT);
    setType("weapon");
    setAltitude(1);

    setSpeed(1);
}

//Handles out, collision events
int Laser::eventHandler(const df::Event* p_e)
{
    if (p_e->getType() == df::OUT_EVENT) {
        WM.markForDelete(this);
        return 1;
    }
    else if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event =
            dynamic_cast <const df::EventCollision*> (p_e);
        collide(p_collision_event);
    }
    return 0;
}

//If hitting shark or spawner, delete the laser
void Laser::collide(const df::EventCollision* p_collision_event)
{
    if (p_collision_event->getObject1()->getType() == "shark" ||
        p_collision_event->getObject2()->getType() == "shark" || 
        p_collision_event->getObject1()->getType() == "spawner" ||
            p_collision_event->getObject2()->getType() == "spawner") {
        WM.markForDelete(this);
    }
}