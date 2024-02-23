#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "LogManager.h"
#include "Sprite.h"
using namespace std;

df::ResourceManager::ResourceManager() {
	setType("ResourceManager");
	sprite_count = 0;

}

df::ResourceManager::~ResourceManager()
{
	for (int i = 0; i < sprite_count; i++) {
		if (p_sprite[i] != NULL) {
			delete p_sprite[i];
		}
	}
}

// Get the one and only instance of the ResourceManager.
df::ResourceManager& df::ResourceManager::getInstance()
{
	static ResourceManager resourceManager;
	return resourceManager;
}

// Get manager ready for resources.
int df::ResourceManager::startUp()
{
	Manager::startUp();
	return 0;
}

// Shut down manager, freeing up any allocated Sprites.
void df::ResourceManager::shutDown()
{
	Manager::shutDown();
}


// Load Sprite from file.
// Assign indicated label to sprite.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSprite(std::string filename, std::string label)
{
	ifstream file;//(filename);
	file.open(filename);

	//Open file
	if (file.is_open()) {
		//Header
		vector<string> header = readData(&file, "HEADER");
		int numFrames = matchLineInt(&header, "frames");
		Sprite* sprite = new Sprite(numFrames);
		sprite->setWidth(matchLineInt(&header, "width"));
		sprite->setHeight(matchLineInt(&header, "height"));
		sprite->setColor(convertColor(matchLineString(&header, "color")));
		sprite->setSlowdown(matchLineInt(&header, "slowdown"));
		string transparencyString = matchLineString(&header, "transparency");
		if (transparencyString != "")
			sprite->setTransparency(transparencyString[0]);
		
		sprite->setLabel(label);
		//Body
		vector<string> body = readData(&file, "BODY");
		for (int i = 0; i < numFrames; i++) {
			Frame f = readFrame(&body, sprite->getWidth(), sprite->getHeight());
			Frame* fp = new Frame(f.getWidth(), f.getHeight(), f.getString());
			sprite->addFrame(*fp);
		}
		p_sprite[sprite_count] = sprite;
		sprite_count++;
	}
	else {
		LM.writeLog("ResourceManager::loadSprite() file %s did not open\n", filename);
		return -1;
	}

	file.close();
	return 0;
}


//Changes the color from a String to DF color
df::Color df::ResourceManager::convertColor(std::string color) {
	if (color == "black") {
		return BLACK;
	}
	else if (color == "red") {
		return RED;
	}
	else if (color == "green") {
		return GREEN;
	} else if (color == "yellow") {
		return YELLOW;
	}
	else if (color == "blue") {
		return BLUE;
	}
	else if (color == "magenta") {
		return MAGENTA;
	}
	else if (color == "cyan") {
		return CYAN;
	}
	else {
		return COLOR_DEFAULT;
	}
}

// Unload Sprite with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSprite(std::string label)
{
	for (int i = 0; i < sprite_count; i++) {
		if (label == p_sprite[i]->getLabel()) {
			delete p_sprite[i];

			//Scoot over remaining sprites
			for (int j = i; j < sprite_count - 1; j++) {
				p_sprite[j] = p_sprite[j + 1];
			}
			sprite_count--;
			return 0;
		}
	}
	LM.writeLog("ResourceManager::unloadSprite() sprite %s not found\n", label.c_str());
	return -1;
}

// Find Sprite with indicated label.
// Return pointer to it if found, else NULL.
df::Sprite* df::ResourceManager::getSprite(std::string label) const
{
	for (int i = 0; i < sprite_count; i++) {
		if (label == p_sprite[i]->getLabel())
			return p_sprite[i];
	}
	LM.writeLog("ResourceManager::getSprite() sprite %s not found\n", label.c_str());
	return NULL; //Sprite not found
}

// Get next line from file, with error checking ("" means error).
std::string df::ResourceManager::getLine(std::ifstream* p_file)
{
	std::string line;
	getline(*p_file, line);
	if (!p_file->good()) {
		LM.writeLog("ResourceManager::getLine() p_file is not good\n");
		return "";
	}
	return line;
}


// Read in next section of data from file as vector of strings.
// Return vector (empty if error).
std::vector<std::string> df::ResourceManager::readData(std::ifstream* p_file, std::string delimiter)
{
	string begin = "<" + delimiter + ">"; //Section beginning
	string end = "</" + delimiter + ">"; //Section ending
	vector<string> data;
	//Check for beginning
	string s = getLine(p_file);
	if (s != begin) {
		LM.writeLog("ResourceManager::readData() s != begin\n");
		return data;
	}

	//Read in data until ending (or not found)
	s = getLine(p_file);
	while (s != end && !s.empty()) {
		data.push_back(s);
		s = getLine(p_file);
	}

	//If ending not found than error
	if (s.empty()) {
		LM.writeLog("ResourceManager::readData() ending not found\n");
		return vector<string>();
	}
	return data;
}

// Match token in vector of lines (e.g., "frames 5").
// Return corresponding value (e.g., 5) (-1 if not found).
// Remove any line that matches from vector.
int df::ResourceManager::matchLineInt(std::vector<std::string>* p_data, const char* token)
{
	int number = -1;
	//Loop through all lines
	for (auto i = p_data->begin(); i != p_data->end();) {
		if ((*i).find(token) != std::string::npos) {
			string s = *i;
			number = atoi(s.substr(strlen(token)).c_str());
			i = p_data->erase(i); //clear from vector
		} else {
			i++;
		}
	}
	if (number == -1) {
		LM.writeLog("ResourceManager::matchLineInt() Value: \"%s\" not found in sprite file/number == -1\n", token);
	}
	return number;
}

// Match token in vector of lines (e.g., "color green").
// Return corresponding string (e.g., "green") ("" if not found).
// Remove any line that matches from vector.
std::string df::ResourceManager::matchLineString(std::vector<std::string>* p_data, const char* token)
{
	
	string output = "";
	//Loop through all lines
	auto i = p_data->begin(); //Vector iterator
	for (auto i = p_data->begin(); i != p_data->end();) {
		if ((*i).find(token) != std::string::npos) {
			string s = *i;
			output = s.substr(strlen(token) + 1).c_str();
			i = p_data->erase(i); //clear from vector
		}
		else {
			i++;
		}

	}
	if(output == "") {
		LM.writeLog("ResourceManager::matchLineString() Value: \"%s\" not found or ouput == \"\"\n", token);
	}
	return output;
}

// Match frame lines until "end", clearing all from vector.
// Return Frame.
df::Frame df::ResourceManager::readFrame(std::vector<std::string>* p_data, int width, int height)
{
	string line, frame_str;
	int count = 0;
	for (auto i = p_data->begin(); count < height;) {
		line = *i;
		if (line.length() != width) {
			LM.writeLog("ResourceManager::readFrame() line.length (%d) mismatch with width (%d) -- line: %s\n", line.length(), width, line.c_str());

			return Frame();
		}
		frame_str += line;
		i = p_data->erase(i);
		count++;
	}
	line = p_data->front();
	if (line != "end") {
		LM.writeLog("ResourceManager::readFrame() \"end\" not found in frame\n");
		return Frame();
	}
	p_data->erase(p_data->begin()); //Erasing end
	return Frame(width, height, frame_str);
}

// Load Sound from file.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSound(std::string filename, std::string label)
{
	if (sound_count == MAX_SOUNDS) {
		LM.writeLog("ResourceManager::loadSound() error: Sound array full\n");
		return -1;
	}
	Sound* newSound = new Sound();
	if (newSound->loadSound(filename) == -1) {
		LM.writeLog("ResourceManager::loadSound() error: Unable to load from file using filename:%s\n", filename.c_str());
		return -1;
	}

	newSound->setLabel(label);
	sound[sound_count] = newSound;
	sound_count++;
	return 0;
}

// Remove Sound with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSound(std::string label)
{
	for (int i = 0; i < sound_count; i++) {
		if (label == sound[i]->getLabel()) {
			sound[i]->stop();
			sound[i]->getSound().resetBuffer();

			//Scoot over remaining sounds
			for (int j = i; j < sound_count - 1; j++) {
				sound[j] = sound[j + 1];
			}
			sound_count--;
			return 0;
		}
	}
	LM.writeLog("ResourceManager::unloadSound() Sound %s not found\n", label.c_str());
	return -1;
}

// Find Sound with indicated label.
// Return pointer to it if found, else NULL.
df::Sound* df::ResourceManager::getSound(std::string label)
{
	for (int i = 0; i < sound_count; i++) {
		if (label == sound[i]->getLabel())
			return sound[i];
	}
	LM.writeLog("ResourceManager::getSound() sound %s not found\n", label.c_str());
	return NULL; //sound not found
}

// Associate file with Music.
// Return 0 if ok, else -1.
int df::ResourceManager::loadMusic(std::string filename, std::string label)
{
	if (music_count == MAX_MUSICS) {
		LM.writeLog("ResourceManager::loadMusic() error: Music array full\n");
		return -1;
	}

	Music* newMusic = new Music();
	if (newMusic->loadMusic(filename) == -1) {
		LM.writeLog("ResourceManager::loadMusic() error: Unable to load from file using filename:%s\n", filename.c_str());
		return -1;
	}

	newMusic->setLabel(label);
	music[music_count] = newMusic;
	music_count++;
	return 0;
}

// Remove label for Music with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadMusic(std::string label)
{
	for (int i = 0; i < music_count; i++) {
		if (label == music[i]->getLabel()) {
			music[i]->stop();
			music[i]->setLabel("");
			return 0;
		}
	}
	LM.writeLog("ResourceManager::unloadMusic() Music %s not found\n", label.c_str());
	return -1;
}

// Find Music with indicated label.
// Return pointer to it if found, else NULL.
Music* df::ResourceManager::getMusic(std::string label)
{
	for (int i = 0; i < music_count; i++) {
		if (label == music[i]->getLabel())
			return music[i];
	}
	LM.writeLog("ResourceManager::getSound() sound %s not found\n", label.c_str());
	return NULL; //music not found
}
