#pragma comment(lib, "Winmm.lib")

#include "GameManager.h"
#include "LogManager.h"
#include "Windows.h"
#include "Clock.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "EventAfterUpdate.h"

df::GameManager::GameManager() {
    setType("GameManager");
    timeBeginPeriod(1);
}

df::GameManager::~GameManager() {
    timeEndPeriod(1);
}
// Get the singleton instance of the GameManager.
df::GameManager& df::GameManager::getInstance()
{
    static GameManager gameManager;
    return gameManager;
}

// Startup all GameManager services.
int df::GameManager::startUp()
{
    Manager::startUp();
    LM.startUp();
    WM.startUp();
    DM.startUp();
    IM.startUp();
    RM.startUp();
    game_over = false;
    frame_time = FRAME_TIME_DEFAULT;
    Box defaultBox = Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical());
    WM.setBoundary(defaultBox);
    WM.setView(defaultBox);
    return 0;
}

// Shut down GameManager services.
void df::GameManager::shutDown()
{
    RM.shutDown();
    IM.shutDown();
    DM.shutDown();
    WM.shutDown();
    LM.shutDown();
    Manager::shutDown();
    
    setGameOver();

}

// Run game loop.
void df::GameManager::run()
{
    Clock clock;
    long int loop_time;
    int loopNum = 0;
    long int sleepTime;
    ObjectList worldObjects;
    while (!game_over) {
        clock.delta();
        worldObjects = WM.getAllObjects();
        loopNum++;

        EventStep stepEvent(loopNum);
        onEvent(&stepEvent);
        
        IM.getInput();
        WM.update();

        EventAfterUpdate eau;
        onEvent(&eau);

        WM.draw();
        DM.swapBuffers();
      
        loop_time = clock.split();
        sleepTime = frame_time - loop_time / 1000;
        if (sleepTime > 0) {
            Sleep(sleepTime);
        }
        /*if (loopNum > 1) {
            setGameOver();
        }*/
     
        //GameManager test
        //LM.writeLog("loop_time: %ld, slept for: %ld, total loop time: %ld\n", loop_time / 1000, sleepTime, clock.split() / 1000);
    }
}

// Set game over status to indicated value.
// If true (the default), will stop game loop.
void df::GameManager::setGameOver(bool game_over)
{ 
    this->game_over = game_over;
}
// Get game over status.
bool df::GameManager::getGameOver() const
{
    return game_over;
}

// Return frame time.
// Frame time is target time for game loop, in milliseconds.
int df::GameManager::getFrameTime() const
{
    return frame_time;
}
