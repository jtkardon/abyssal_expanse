#pragma once
#include <string>
#include <SFML/Audio.hpp>

class Music {

private:
	sf::Music music;              // The SFML music.
	std::string label;            // Text label to identify music.
	Music(Music const&);         // SFML doesn't allow music copy.
	void operator=(Music const&); // SFML doesn't allow music assignment.

public:
	Music();

	// Associate music buffer with file.
	// Return 0 if ok, else -1.
	int loadMusic(std::string filename);

	// Set label associated with music.
	void setLabel(std::string new_label);

	// Get label associated with music.
	std::string getLabel() const;

	// Play music.
	// If loop is true, repeat play when done.
	void play(bool loop = true);

	// Stop music.
	void stop();

	// Pause music.
	void pause();

	// Return SFML music.
	sf::Music* getMusic();
};
