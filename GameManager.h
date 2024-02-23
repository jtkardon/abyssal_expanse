#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define GM df::GameManager::getInstance()

namespace df {
	const int FRAME_TIME_DEFAULT = 33;  // In milliseconds.

	class GameManager : public Manager {

	private:
		GameManager();                      // Private (a singleton).
		GameManager(GameManager const&);   // No copying.
		void operator=(GameManager const&); // No assignment.
		~GameManager();
		bool game_over = false;       // True, then game loop should stop.
		int frame_time = FRAME_TIME_DEFAULT;       // Target time per game loop (in milliseconds).

	public:
		// Get the singleton instance of the GameManager.
		static GameManager& getInstance();
		// Startup all GameManager services.
		int startUp();

		// Shut down GameManager services.
		void shutDown();

		// Run game loop.
		void run();

		// Set game over status to indicated value.
		// If true (the default), will stop game loop.
		void setGameOver(bool game_over = true);

		// Get game over status.
		bool getGameOver() const;

		// Return frame time.
		// Frame time is target time for game loop, in milliseconds.
		int getFrameTime() const;
	};
} //end of namespace df
#endif