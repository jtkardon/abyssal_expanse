#include "Manager.h"
#include "LogManager.h"
#include "ObjectList.h"
#include "WorldManager.h"

//Set type identifier of manager
void df::Manager::setType(std::string type)
{
	m_type = type;
}

df::Manager::Manager()
{
	m_is_started = false;
	m_type = "base";
}

df::Manager::~Manager()
{
}

// Get type of Manager
std::string df::Manager::getType() const
{
	return m_type;
}

// Startup Manager
// Return 0 if ok, else negative number
int df::Manager::startUp()
{
	m_is_started = true;
	return 0;
}

// Shutdown Manager
void df::Manager::shutDown()
{
	m_is_started = false;
}

//return true when startUp() was executed ok, else false
bool df::Manager::isStarted() const
{
	return m_is_started;
}

//Send event to all Objects
//Return count of number of events sent
int df::Manager::onEvent(const Event* p_event)
{
	int count = 0;

	ObjectList allObjects = WM.getAllObjects();
	ObjectListIterator li(&allObjects);
	for (li.first(); !li.isDone(); li.next()) {
		li.currentObject()->eventHandler(p_event);
		count++;
	}
	return count;
}
