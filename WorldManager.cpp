#include "WorldManager.h"
#include "LogManager.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "Box.h"
#include "Object.h"
#include "ViewObject.h"

using namespace df;
df::WorldManager::WorldManager() {
	setType("WorldManager");
}

df::WorldManager::~WorldManager()
{
	shutDown();
}


// Get the one and only instance of the WorldManager.
df::WorldManager& df::WorldManager::getInstance() {
	static WorldManager worldManager;
	return worldManager;
}

// Startup game world (initialize everything to empty).
// Return 0.
int df::WorldManager::startUp()
{
	
	updates.clear();
	deletions.clear();
	Manager::startUp();
	return 0;
}

// Shutdown game world (delete all game world Objects).
void df::WorldManager::shutDown()
{
	ObjectList ol = updates;
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next())
		delete li.currentObject();
	Manager::shutDown();
}


// Add Object to world. Return 0 if ok, else -1.
int df::WorldManager::insertObject(df::Object* p_o) {
	return updates.insert(p_o);
}

// Remove Object from world. Return 0 if ok, else -1.
int df::WorldManager::removeObject(df::Object* p_o) {
	return updates.remove(p_o);
}

// Return list of all Objects in world.
df::ObjectList df::WorldManager::getAllObjects() const {
	return updates;
}

// Return list of Objects matching type
// List is empty if none found
df::ObjectList df::WorldManager::objectsOfType(std::string type) const
{
	ObjectList output;
	ObjectListIterator li(&updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getType() == type)
			output.insert(li.currentObject());
	}

	return output;
}


// Update world.
// Delete Objects marked for deletion.
void df::WorldManager::update() {
	ObjectListIterator uli(&updates);
	for (uli.first(); !uli.isDone(); uli.next()) {
		//Add velocity to position
		Vector newPos = uli.currentObject()->predictPosition();

		//If object should change position, then move.
		if (newPos != uli.currentObject()->getPosition()) {
			moveObject(uli.currentObject(), uli.currentObject()->predictPosition());
		}
	}

	ObjectListIterator dli(&deletions);
	for (dli.first(); !dli.isDone(); dli.next()) {
		delete (dli.currentObject());
	}
	deletions.clear();
}


// Indicate object is to be deleted at end of current game update.
// Return 0 if ok, else -1.
int df::WorldManager::markForDelete(Object* p_o) {
	ObjectListIterator li(&deletions);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject() == p_o) {
			return 0;
		}
	}
	deletions.insert(p_o);
	return 0;
}

//Draws all Objects
void df::WorldManager::draw()
{
	ObjectListIterator li(&updates);
	for (int i = 0; i <= MAX_ALTITUDE; i++) {
		for (li.first(); !li.isDone(); li.next()) {
			Box box = getWorldBox(li.currentObject(), li.currentObject()->getPosition());
			if (li.currentObject()->getAltitude() == i) {
				LM.writeLog("Drawing current obj tpye:%s, boxinte=%d, box=(%f,%f) pos=(%f,%f)\n", li.currentObject()->getType().c_str(), boxIntersectsBox(box, view), box.getCorner().getX(), box.getCorner().getY(), li.currentObject()->getPosition().getX(), li.currentObject()->getPosition().getY());
				if (boxIntersectsBox(box, view) || dynamic_cast <ViewObject*> (li.currentObject())) {
					li.currentObject()->draw();
				}
			}
		}
	}
}

// Return list of Objects collided with at position `where'.
// Collisions only with solid Objects.
// Does not consider if p_o is solid or not.
df::ObjectList df::WorldManager::getCollisions(Object* p_o, Vector where) const
{
	// Make empty list.
	ObjectList collision_list;

	// Iterate through all objects.
	ObjectListIterator i(&updates);

	for (i.first(); !i.isDone(); i.next()) {
		Object* p_temp_o = i.currentObject();

		if (p_temp_o != p_o) { // Do not consider self.
			Box b = getWorldBox(p_o, where);
			Box b_temp = getWorldBox(p_temp_o, p_temp_o->getPosition());
			// Same location and both solid?
			if (boxIntersectsBox(b, b_temp)
				&& p_temp_o->isSolid())
			{
				collision_list.insert(p_temp_o);
			}
		}
	}
	return collision_list;
}

// Move Object.
// If no collision with solid, move ok else don't move.
// If p_go is Spectral, move ok.
// Return 0 if move ok, else -1 if collision with solid.
int df::WorldManager::moveObject(Object* p_o, Vector where)
{
	if (p_o->isSolid()) { //Need to be solid for collisions
		
		//Get collisions
		ObjectList list = getCollisions(p_o, where);
		if (!list.isEmpty()) {
			//Iterate over list
			bool doMove = true;
			ObjectListIterator li(&list);
			for (li.first(); !li.isDone(); li.next()) {
				Object* p_temp_o = li.currentObject();

				//Create collision event
				EventCollision ec(p_o, p_temp_o, where);
				//Send to both objects
				p_o->eventHandler(&ec);
				p_temp_o->eventHandler(&ec);

				//If both HARD, then cannot move
				if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD) {
					doMove = false;
				}
			}
			if (!doMove) {
				return -1;
			}
		}
	}

	Box originalBox = getWorldBox(p_o, p_o->getPosition());
	Box newBox = getWorldBox(p_o, where);

	//Check for out event
	if (boxIntersectsBox(originalBox, boundary) && !boxIntersectsBox(newBox, boundary)) {
		EventOut eo;
		p_o->eventHandler(&eo);
	}
	
	//If here, no collision so allow move
	p_o->setPosition(where);

	//If view is following this object, adjust view
	if (p_view_following != NULL && p_view_following == p_o)
		setViewPosition(where);
	return 0; //Move was ok
}

// Return true if two positions intersect, else false.
bool df::WorldManager::positionsIntersect(Vector p1, Vector p2) const
{
	if (abs(p1.getX() - p2.getX()) < 1 &&
		abs(p1.getY() - p2.getY()) < 1)
		return true;
	return false;
}

//Return true if boxes intersect, else false
bool df::WorldManager::boxIntersectsBox(Box A, Box B) const
{
	//Horizonal Overlap
	float ax1 = A.getCorner().getX();
	float ax2 = A.getCorner().getX() + A.getHorizontal();
	float ay1 = A.getCorner().getY();
	float ay2 = A.getCorner().getY() + A.getVertical();

	float bx1 = B.getCorner().getX();
	float bx2 = B.getCorner().getX() + B.getHorizontal();
	float by1 = B.getCorner().getY();
	float by2 = B.getCorner().getY() + B.getVertical();

	bool bHor = bx1 >= ax1 && bx1 <= ax2;
	bool aHor = ax1 >= bx1 && ax1 <= bx2;

	bool bVert = by1 >= ay1 && by1 <= ay2;
	bool aVert = ay1 >= by1 && ay1 <= by2;

	return (bHor || aHor) && (bVert || aVert);
}

// Convert relative bounding Box for Object to absolute world Box.
Box df::WorldManager::getWorldBox(const Object* object, Vector where) const
{
	Box temp_box = object->getBox();
	Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + where.getX());
	corner.setY(corner.getY() + where.getY());
	temp_box.setCorner(corner);

	return temp_box;
}

//Get game world boundary
Box df::WorldManager::getBoundary() const
{
	return boundary;
}

// Set game world boundary.
void df::WorldManager::setBoundary(Box new_boundary)
{
	boundary = new_boundary;
}

// Get player view of game world.
Box df::WorldManager::getView() const
{
	return view;
}

// Set player view of game world.
void df::WorldManager::setView(Box new_view)
{
	view = new_view;
}

// Set view to center screen on position view_pos.
// View edge will not go beyond world boundary.
void df::WorldManager::setViewPosition(Vector view_pos)
{
	//Make sure horizontal not out of world boundary
	float x = view_pos.getX() - view.getHorizontal() / 2;
	if (x + view.getHorizontal() > boundary.getHorizontal())
		x = boundary.getHorizontal() - view.getHorizontal();
	if (x < 0)
		x = 0;

	//Make sure vertical not out of world boundary
	float y = view_pos.getY() - view.getVertical() / 2;
	if (y + view.getVertical() > boundary.getVertical())
		y = boundary.getVertical() - view.getVertical();
	if (y < 0)
		y = 0;
	view.setCorner(Vector(x, y));
}

// Set view to center screen on Object.
// Set to NULL to stop following.
// If p_new_view_following not legit, return -1 else return 0.
int df::WorldManager::setViewFollowing(Object* p_new_view_following)
{
	//Set to NULL to turn 'off' following
	if (p_new_view_following == NULL) {
		p_view_following = NULL;
		return 0;
	}

	bool found = false;
	ObjectListIterator li(&updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject() == p_new_view_following)
			found = true;
	}

	//If found, adjust attribute accordingly and set view position
	if (found) {
		p_view_following = p_new_view_following;
		setViewPosition(p_view_following->getPosition());
		return 0;
	}
	
	//If we get here, was not legit. Don't change current view
	return -1;
}
