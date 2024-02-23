#pragma once
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Manager.h"
#include "Vector.h"

#define DM df::DisplayManager::getInstance()

namespace df {
	// Defaults for SFML window.
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1040;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar | sf::Style::Close;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	class DisplayManager : public Manager {

	private:
		DisplayManager();
		DisplayManager(DisplayManager const&);
		void operator=(DisplayManager const&);
		sf::Font font;                // Font used for ASCII graphics.
		sf::RenderWindow* p_window;   // Pointer to SFML window.
		int window_horizontal_pixels; // Horizontal pixels in window.
		int window_vertical_pixels;   // Vertical pixels in window.
		int window_horizontal_chars;  // Horizontal ASCII spaces in window.
		int window_vertical_chars;    // Vertical ASCII spaces in window.

	public:
		static DisplayManager& getInstance();
		// Open graphics window ready for text-based display.
	// Return 0 if ok, else -1.
		int startUp();

		// Close graphics window.
		void shutDown();

		// Draw a character at screen location (x,y) with color.
		// Return 0 if ok, else -1.
		int drawCh(Vector world_pos, char ch, Color color) const;

		// Return window's horizontal maximum (in characters).
		int getHorizontal() const;

		// Return window's vertical maximum (in characters).
		int getVertical() const;

		// Return window's horizontal maximum (in pixels).
		int getHorizontalPixels() const;

		// Return window's vertical maximum (in pixels).
		int getVerticalPixels() const;

		// Render current display buffer.
		// Return 0 if ok, else -1.
		int swapBuffers();

		// Return pointer to SFML drawing window.
		sf::RenderWindow* getWindow() const;

		// Compute character height, based on window size and font.
		float charHeight() const;

		// Compute character width, based on window size and font.
		float charWidth() const;

		// Convert ASCII spaces (x,y) to window pixels (x,y).
		Vector spacesToPixels(Vector spaces) const;

		// Convert window pixels (x,y) to ASCII spaces (x,y).
		Vector pixelsToSpaces(Vector pixels) const;

		// Draw string at screen location (x,y) with color.
		// Justified LEFT, CENTER or RIGHT.
		// Return 0 if ok, else -1.
		int drawString(Vector world_pos, std::string str, Justification just, Color color) const;

		//Checks whether a given point in outside the world bounds
		bool isPointOutside(Vector pos) const;

		//Convert world position to view position
		Vector worldToView(Vector world_pos) const;

		//Convert view position to world position
		Vector viewToWorld(Vector view_pos) const;
	};
}