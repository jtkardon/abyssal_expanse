#include <iostream>
#include "Sound.h"
#include "GameManager.h"
#include "LogManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "Start up" << std::endl;
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    LM.setFlush(true);

    LM.writeLog("LogTest2\n");
    GM.shutDown();
}