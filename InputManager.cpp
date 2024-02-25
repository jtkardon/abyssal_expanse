#include "InputManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "LogManager.h"
#include "GameManager.h"


df::InputManager::InputManager() {
    setType("InputManager");
}
// Get the one and only instance of the InputManager.
df::InputManager& df::InputManager::getInstance()
{
    static InputManager inputManager;
    return inputManager;
}

// Get terminal ready to capture input.
// Return 0 if ok, else return -1.
int df::InputManager::startUp()
{
    if (!DM.isStarted())
        return -1;

    
    // Disable keyboard repeat (only do once).
    DM.getWindow()->setKeyRepeatEnabled(false);

    Manager::startUp();
    return 0;
}

// Revert back to normal terminal mode.
void df::InputManager::shutDown()
{
    DM.getWindow()->setKeyRepeatEnabled(true);
    Manager::shutDown();
}

// Get input from the keyboard and mouse.
// Pass event along to all Objects.
void df::InputManager::getInput()
{
    sf::Event event;
    while (DM.getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) { //KeyPressed
            EventKeyboard ek(Keyboard::Key(event.key.code), EventKeyboardAction::KEY_PRESSED);
            onEvent(&ek);
        }
        else if (event.type == sf::Event::KeyReleased) { //KeyReleased
            EventKeyboard ek(Keyboard::Key(event.key.code), EventKeyboardAction::KEY_RELEASED);
            onEvent(&ek);
        }
        else if (event.type == sf::Event::MouseMoved) { //MouseMoved
            EventMouse em;
            em.setMouseAction(EventMouseAction::MOVED);
            em.setMouseButton(Mouse::Button(event.mouseButton.button));
            em.setMousePosition(Vector(event.mouseMove.x, event.mouseMove.y));
            onEvent(&em);
        }
        else if (event.type == sf::Event::MouseButtonPressed) { //MousePressed
            EventMouse em;
            em.setMouseAction(EventMouseAction::PRESSED);
            em.setMouseButton(Mouse::Button(event.mouseButton.button));
            em.setMousePosition(Vector(event.mouseButton.x, event.mouseButton.y));
            onEvent(&em);
        }
        else if (event.type == sf::Event::MouseButtonReleased) { //MouseReleased
            EventMouse em;
            em.setMouseAction(EventMouseAction::RELEASED);
            em.setMouseButton(Mouse::Button(event.mouseButton.button));
            em.setMousePosition(Vector(event.mouseButton.x, event.mouseButton.y));
            onEvent(&em);
        }
        else if (event.type == sf::Event::Closed) {
            GM.setGameOver();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        EventKeyboard ek(Keyboard::W, EventKeyboardAction::KEY_DOWN);
        onEvent(&ek);
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        EventKeyboard ek(Keyboard::A, EventKeyboardAction::KEY_DOWN);
        onEvent(&ek);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        EventKeyboard ek(Keyboard::S, EventKeyboardAction::KEY_DOWN);
        onEvent(&ek);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        EventKeyboard ek(Keyboard::D, EventKeyboardAction::KEY_DOWN);
        onEvent(&ek);
    }

}
