#include "Music.h"
#include "LogManager.h"

Music::Music()
{
	label = "";
}

// Associate music buffer with file.
// Return 0 if ok, else -1.
int Music::loadMusic(std::string filename)
{
	if (!music.openFromFile(filename)) {
		LM.writeLog("Music::loadMusic() error loading music from file: %s\n", filename.c_str());
		return -1;
	}
	return 0;
}

// Set label associated with music.
void Music::setLabel(std::string new_label)
{
	label = new_label;
}

// Get label associated with music.
std::string Music::getLabel() const
{
	return label;
}

// Play music.
// If loop is true, repeat play when done.
void Music::play(bool loop)
{
	music.setLoop(loop);
	music.play();
}

// Stop music.
void Music::stop()
{
	music.stop();
}

// Pause music.
void Music::pause()
{
	music.pause();
}

// Return SFML music.
sf::Music* Music::getMusic()
{
	return &music;
}
