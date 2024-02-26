Jason Kardon
jkardon@wpi.edu

Colin Gallagher
cjgallagher@wpi.edu

Game: Abyssal Expanse 
Platform: Windows

All .cpp and .h files are in the base project folder of abyssal_expanse

Built in Microsoft VS Code 2022

The game can be run by opening up abyssal_expanse.sln in Visual Studio and
building and running the code

The game start is main.cpp

We created the files:
.h files:
Bubble.h
Coin.h
EventAfterUpdate.h
EventSub.h
Generator.h
Harpoon.h
Laser.h
Shark.
Spawner.h
Sub.h

.cpp files:
Bubble.cpp
Coin.cpp
EventAfterUpdate.cpp
EventSub.cpp
Generator.cpp
Harpoon.cpp
Laser.cpp
Shark.cpp
Spawner.cpp
Sub.cpp
main.cpp

All sprites are stored in the sprites folder:
Sprites we created:
coin.txt
harpoonLeft.txt
harpoonRight.txt
laserLeft.txt
laserRight.txt
sharkLeft.txt
sharkLeftRed.txt
sharkRight.txt
sharkRightRed.txt
spawner.txt
subLeft.txt
subRight.txt

To play our game: 
The objective of Abyssal Expanse is to survive as long as possible and accumalate as many points as you can. 
You can move in all 4 direction and have a laser and harpoon attack
Shark Spawners will randomly appear across the map
Spawners have 5 hit points
They take 2 damage from the laser but 1 damage from the harpoon

Every few seconds, a shark spawner will spawn a shark.
The sharks have 2 hit points
they will take 1 damage from the laser and 2 damage from the harpoon
Destroying both sharks and the shark spawners will give you points
Sharks will die when they hit you and will deal 1 damage

You have 3 hit points and when it goes to 0, the game will be over and the program will close.

Coins will spawn randomly across the map and can be collected to add to your score

How to play:

Controls

Mouse
Left-click: Laser
Right-click: Harpoon

Movement
W: Sub goes up
A: Sub goes right
S: Sub goes down
D: Sub goes right
Q: Quits the game


Game Implementations:
-Sub (player)
-Coin
-Weapons: Harpoon & Lazer
-Shark (Eniemes)
-Bubbles that create a background
-Health for sub, shark and spawners
-Points
-Spawner (Place were sharks spawn from)
-Generator which is invisible for helping to create spawners and coins
