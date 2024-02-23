#pragma once
#include <string>
#include <vector>
#include "Manager.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"

#define RM df::ResourceManager::getInstance()


namespace df {
// Maximum number of unique sprites in game.
const int MAX_SPRITES = 1000;
const int MAX_SOUNDS = 128;
const int MAX_MUSICS = 128;

// Delimiters used to parse Sprite files -
// the ResourceManager `knows' file format.
const std::string HEADER_TOKEN = "HEADER";
const std::string BODY_TOKEN = "BODY";
const std::string FOOTER_TOKEN = "FOOTER";
const std::string FRAMES_TOKEN = "frames";
const std::string HEIGHT_TOKEN = "height";
const std::string WIDTH_TOKEN = "width";
const std::string COLOR_TOKEN = "color";
const std::string END_FRAME_TOKEN = "end";
const std::string VERSION_TOKEN = "version";

class ResourceManager : public Manager {

private:
	ResourceManager();                         // Private (a singleton).
	ResourceManager(ResourceManager const&);  // Don't allow copy.
	void operator=(ResourceManager const&);    // Don't allow assignment.
	Sprite* p_sprite[MAX_SPRITES];  // Array of (pointers to) sprites.
	int sprite_count;               // Count of number of loaded sprites.
	Sound* sound[MAX_SOUNDS];      // Array of sound buffers.
	int sound_count;              // Count of number of loaded sounds.
	Music* music[MAX_MUSICS];      // Array of music buffers.
	int music_count;              // Count of number of loaded musics
public:
	~ResourceManager();

	// Get the one and only instance of the ResourceManager.
	static ResourceManager& getInstance();

	// Get manager ready for resources.
	int startUp();

	// Shut down manager, freeing up any allocated Sprites.
	void shutDown();

	// Load Sprite from file.
	// Assign indicated label to sprite.
	// Return 0 if ok, else -1.
	int loadSprite(std::string filename, std::string label);

	//Changes the color from a String to DF color
	Color convertColor(std::string color);

	// Unload Sprite with indicated label.
	// Return 0 if ok, else -1.
	int unloadSprite(std::string label);

	// Find Sprite with indicated label.
	// Return pointer to it if found, else NULL.
	Sprite* getSprite(std::string label) const;

	// Get next line from file, with error checking ("" means error).
	std::string getLine(std::ifstream* p_file);

	// Read in next section of data from file as vector of strings.
	// Return vector (empty if error).
	std::vector<std::string> readData(std::ifstream* p_file, std::string delimiter);

	// Match token in vector of lines (e.g., "frames 5").
	// Return corresponding value (e.g., 5) (-1 if not found).
	// Remove any line that matches from vector.
	int matchLineInt(std::vector<std::string>* p_data, const char* token);

	// Match token in vector of lines (e.g., "color green").
	// Return corresponding string (e.g., "green") ("" if not found).
	// Remove any line that matches from vector.
	std::string matchLineString(std::vector<std::string>* p_data, const char* token);

	// Match frame lines until "end", clearing all from vector.
	// Return Frame.
	Frame readFrame(std::vector<std::string>* p_data, int width, int height);

	// Load Sound from file.
    // Return 0 if ok, else -1.
	int loadSound(std::string filename, std::string label);

	// Remove Sound with indicated label.
	// Return 0 if ok, else -1.
	int unloadSound(std::string label);

	// Find Sound with indicated label.
	// Return pointer to it if found, else NULL.
	Sound* getSound(std::string label);

	// Associate file with Music.
	// Return 0 if ok, else -1.
	int loadMusic(std::string filename, std::string label);

	// Remove label for Music with indicated label.
	// Return 0 if ok, else -1.
	int unloadMusic(std::string label);

	// Find Music with indicated label.
	// Return pointer to it if found, else NULL.
	Music* getMusic(std::string label);

};

}