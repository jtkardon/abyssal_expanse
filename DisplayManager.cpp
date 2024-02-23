#include "DisplayManager.h"
#include "LogManager.h"
#include "WorldManager.h"

df::DisplayManager::DisplayManager() {
    setType("displayManager");
    p_window = NULL;
    window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
    window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
    window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
    window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
}


df::DisplayManager& df::DisplayManager::getInstance()
{
    static DisplayManager displayManager;
    return displayManager;
}

// Open graphics window ready for text-based display.
// Return 0 if ok, else -1.
int df::DisplayManager::startUp()
{
    if (p_window != NULL) {
        return 0;
    }

    p_window =
        new sf::RenderWindow(sf::VideoMode(WINDOW_HORIZONTAL_PIXELS_DEFAULT, WINDOW_VERTICAL_PIXELS_DEFAULT), WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);
    if (!p_window) {
        LM.writeLog("Error! Unable to allocate RenderWindow.");
        return -1;
    }

    // Turn off mouse cursor for window.
    p_window->setMouseCursorVisible(false);

    // Synchronize refresh rate with monitor.
    p_window->setVerticalSyncEnabled(true);


    // Load font.
     if (font.loadFromFile(FONT_FILE_DEFAULT) == false) {
         LM.writeLog("Error! Unable to load font 'df-font.otf'.");
        return -1;
    }

     Manager::startUp();
     return 0;
}

// Close graphics window.
void df::DisplayManager::shutDown()
{
    Manager::shutDown();
    p_window->close();
    p_window = NULL;
}

// Draw a character at screen location (x,y) with color.
// Return 0 if ok, else -1.
int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const
{
    //Make sure window is allocated
    if (p_window == NULL)
        return -1;
    
    // Convert spaces (x,y) to pixels (x,y).
    Vector pixel_pos = spacesToPixels(worldToView(world_pos));

    // Draw background rectangle since text is "see through" in SFML.
    static sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(charWidth(), charHeight() - 1));
    rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
    rectangle.setPosition(pixel_pos.getX() + charWidth() / 10,
        pixel_pos.getY() + charHeight() / 5);
    p_window->draw(rectangle);

    // Create character text to draw.
    static sf::Text text("", font);
    text.setString(ch);
    text.setStyle(sf::Text::Bold); // Make bold, since looks better. 

    // Scale to right size.
    if (charWidth() < charHeight())
        text.setCharacterSize(charWidth() * 2);
    else
        text.setCharacterSize(charHeight() * 2);
 
    // Set SFML color based on Dragonfly color.
    switch (color) {
    case YELLOW:
        text.setFillColor(sf::Color::Yellow);
        break;
    case RED:
        text.setFillColor(sf::Color::Red);
        break;
    case BLACK:
        text.setFillColor(sf::Color::Black);
        break;
    case GREEN:
        text.setFillColor(sf::Color::Green);
        break;
    case BLUE:
        text.setFillColor(sf::Color::Blue);
        break;
    case MAGENTA:
        text.setFillColor(sf::Color::Magenta);
        break;
    case CYAN:
        text.setFillColor(sf::Color::Cyan);
        break;
    default:
        text.setFillColor(sf::Color::White);
        break;
     
    }

    // Set position in window (in pixels).
    text.setPosition(pixel_pos.getX(), pixel_pos.getY());

    // Draw character.
    p_window->draw(text);

    return 0;
}

// Return window's horizontal maximum (in characters).
int df::DisplayManager::getHorizontal() const
{
    return window_horizontal_chars;
}

// Return window's vertical maximum (in characters).
int df::DisplayManager::getVertical() const
{
    return window_vertical_chars;
}

// Return window's horizontal maximum (in pixels).
int df::DisplayManager::getHorizontalPixels() const
{
    return window_horizontal_pixels;
}

// Return window's vertical maximum (in pixels).
int df::DisplayManager::getVerticalPixels() const
{
    return window_vertical_pixels;
}

// Render current display buffer.
// Return 0 if ok, else -1.
int df::DisplayManager::swapBuffers()
{
    // Make sure window is allocated.
    if (p_window == NULL)
        return -1;

    // Display current window.
    p_window->display();

    // Clear window to get ready for next draw.
    p_window->clear(WINDOW_BACKGROUND_COLOR_DEFAULT);

    return 0; // Success.

}

// Return pointer to SFML drawing window.
sf::RenderWindow* df::DisplayManager::getWindow() const
{
    return p_window;
}

// Compute character height, based on window size and font.
float df::DisplayManager::charHeight() const
{
    return getVerticalPixels() / getVertical();
}

// Compute character width, based on window size and font.
float df::DisplayManager::charWidth() const
{
    return getHorizontalPixels() / getHorizontal();
}

// Convert ASCII spaces (x,y) to window pixels (x,y).
df::Vector df::DisplayManager::spacesToPixels(Vector spaces) const
{
    spaces.setXY(spaces.getX() * charWidth(), spaces.getY() * charHeight());
    return spaces;
}

// Convert window pixels (x,y) to ASCII spaces (x,y).
df::Vector df::DisplayManager::pixelsToSpaces(Vector pixels) const
{
    pixels.setXY(pixels.getX() / charWidth(), pixels.getY() / charHeight());
    return pixels;
}

// Draw string at screen location (x,y) with color.
// Justified LEFT, CENTER or RIGHT.
// Return 0 if ok, else -1.
int df::DisplayManager::drawString(Vector world_pos, std::string str, Justification just, Color color) const
{
    // Get starting position.
    Vector starting_pos = world_pos;
    switch (just) {
        case CENTER_JUSTIFIED:
            starting_pos.setX(world_pos.getX() - str.size() / 2.0);
            break;
        case RIGHT_JUSTIFIED:
            starting_pos.setX(world_pos.getX() - str.size());
            break;
        case LEFT_JUSTIFIED:
        default:
            break;
    }
             

    // Draw string character by character.
    for (int i = 0; i < str.size(); i++) {
        Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
        if (drawCh(temp_pos, str[i], color) == -1)
            return -1;
    }
    return 0;

}

//Checks whether a given point in outside the world bounds
bool df::DisplayManager::isPointOutside(Vector pos) const
{
    bool left = pos.getX() < 0;
    bool right = pos.getX() > getHorizontal();
    bool up = pos.getY() < 0;
    bool down = pos.getY() > getVertical();
    return left || right || up || down;
}

//Convert world position to view position
df::Vector df::DisplayManager::worldToView(Vector world_pos) const
{
    Vector view_origin = WM.getView().getCorner();
    float viewX = view_origin.getX();
    float viewY = view_origin.getY();

    return Vector(world_pos.getX() - viewX, world_pos.getY() - viewY);
}

//Convert view position to world position
df::Vector df::DisplayManager::viewToWorld(Vector view_pos) const
{
    Vector view_origin = WM.getView().getCorner();
    float viewX = view_origin.getX();
    float viewY = view_origin.getY();
    return Vector(view_pos.getX() + viewX, view_pos.getY() + viewY);
}
