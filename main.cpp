#include <iostream>
#include "Sound.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "Sub.h"
#include "Bubble.h"
#include "Generator.h"
#include "GameStart.h"
using namespace std;

void loadResources(void);
void populateWorld(void);

int main(int argc, char* argv[]) {
    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);

    // Load game resources
    loadResources();

    // Populate game world with some objects
    populateWorld();


    GM.run();

    // Shut everything down.
    GM.shutDown();
    return 0;
}

//Loads sounds and sprites
void loadResources(void) {
    RM.loadSprite("sprites/subRight.txt", "rightSub");
    RM.loadSprite("sprites/subLeft.txt", "leftSub");
    RM.loadSprite("sprites/laserLeft.txt", "laserLeft");
    RM.loadSprite("sprites/laserRight.txt", "laserRight");
    RM.loadSprite("sprites/sharkRight.txt", "sharkRight");
    RM.loadSprite("sprites/sharkLeft.txt", "sharkLeft");
    RM.loadSprite("sprites/sharkRightRed.txt", "sharkRightRed");
    RM.loadSprite("sprites/sharkLeftRed.txt", "sharkLeftRed");
    RM.loadSprite("sprites/spawner.txt", "spawner");
    RM.loadSprite("sprites/harpoonLeft.txt", "harpoonLeft");
    RM.loadSprite("sprites/harpoonRight.txt", "harpoonRight");
    RM.loadSprite("sprites/coin.txt", "coin");
    RM.loadSprite("sprites/gameOver.txt", "gameover");
    RM.loadSprite("sprites/gameStart.txt", "title");

    RM.loadMusic("sounds/Theme_Idea.wav", "themeMusic");
    RM.loadMusic("sounds/Game_Title_Music.wav", "titleMusic");

    RM.loadSound("sounds/Harpoon.wav", "harpoon");
    RM.loadSound("sounds/spawnerCreated.wav", "spawnerCreated");
    RM.loadSound("sounds/bubbles.wav", "bubbles");
    RM.loadSound("sounds/waterLazerSound.wav", "laser");
    RM.loadSound("sounds/coin.wav", "coin");
    RM.loadSound("sounds/gameSFX2.wav", "SFX2");
    RM.loadSound("sounds/hitSub.wav", "hit");
    RM.loadSound("sounds/hitShark.wav", "hitShark");
    RM.loadSound("sounds/sharkDie.wav", "dieShark");
    RM.loadSound("sounds/gameOVer.wav", "gameOver");
}

//Adds objects to game
void populateWorld(void) {
    //Create a game start
    new GameStart;

    //Create 100 bubbles
    for (int i = 0; i < 100; i++) {
        new Bubble(true);
    }
}

