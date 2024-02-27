#include <iostream>
#include "Sound.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "Sub.h"
#include "Bubble.h"
#include "Generator.h"
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
    RM.loadMusic("Theme_idea.wav", "themeMusic");
    RM.loadSound("Harpoon.wav", "harpoon");
    RM.loadSound("sharkNoise.wav", "sharkNoise");
    RM.loadSound("bubbles", "bubbles");
    RM.loadSound("waterLazerSounds", )
}

//Adds objects to game
void populateWorld(void) {
    new Generator;

    for (int i = 0; i < 100; i++) {
        new Bubble(true);
    }
}

