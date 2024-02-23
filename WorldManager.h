#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"

#define WM df::WorldManager::getInstance()

namespace df {
	const int MAX_ALTITUDE = 4;

	class WorldManager : public Manager {

	private:
		WorldManager();                       // Private (a singleton).
		WorldManager(WorldManager const&);   // No assignment.
		void operator=(WorldManager const&);  // No copying.
		ObjectList updates;           // List of all Objects in world to update.
		ObjectList deletions;         // List of all Objects in world to delete.
		bool firstLoop;
		Box boundary;				//World Boundary
		Box view;					//Player view of game world
		Object* p_view_following;	//Object view is following
	public:
		~WorldManager();
		// Get the one and only instance of the WorldManager.
		static WorldManager& getInstance();

		// Startup game world (initialize everything to empty).
		// Return 0.
		int startUp();
		// Shutdown game world (delete all game world Objects).
		void shutDown();

		// Add Object to world. Return 0 if ok, else -1.
		int insertObject(Object* p_o);

		// Remove Object from world. Return 0 if ok, else -1.
		int removeObject(Object* p_o);

		// Return list of all Objects in world.
		ObjectList getAllObjects() const;
		
		// Return list of Objects matching type
		// List is empty if none found
		ObjectList objectsOfType(std::string type) const;

		// Update world.
		// Delete Objects marked for deletion.
		void update();

		// Indicate object is to be deleted at end of current game update.
		// Return 0 if ok, else -1.
		int markForDelete(Object* p_o);

		//Draws all Objects
		void draw();

		// Return list of Objects collided with at position `where'.
		// Collisions only with solid Objects.
		// Does not consider if p_o is solid or not.
		ObjectList getCollisions(Object* p_o, Vector where) const;

		// Move Object.
		// If no collision with solid, move ok else don't move.
		// If p_go is Spectral, move ok.
		// Return 0 if move ok, else -1 if collision with solid.
		int moveObject(Object* p_o, Vector where);

		//Return true if two positions intersect, else false
		bool positionsIntersect(Vector p1, Vector p2) const;

		//Return true if boxes intersect, else false
		bool boxIntersectsBox(Box A, Box B) const;

		// Convert relative bounding Box for Object to absolute world Box 
		// at position where.
		Box getWorldBox(const Object* p_o, Vector where) const;

		//Get game world boundary
		Box getBoundary() const;

		// Set game world boundary.
		void setBoundary(Box new_boundary);

		// Get player view of game world.
		Box getView() const;

		// Set player view of game world.
		void setView(Box new_view);

		// Set view to center screen on position view_pos.
		// View edge will not go beyond world boundary.
		void setViewPosition(Vector view_pos);

		// Set view to center screen on Object.
		// Set to NULL to stop following.
		// If p_new_view_following not legit, return -1 else return 0.
		int setViewFollowing(Object* p_new_view_following);

	};
}
#endif