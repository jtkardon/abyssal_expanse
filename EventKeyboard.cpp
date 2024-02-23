#include "EventKeyboard.h"

df::EventKeyboard::EventKeyboard()
{
	setType(KEYBOARD_EVENT);
}

df::EventKeyboard::EventKeyboard(Keyboard::Key key, EventKeyboardAction action) {
	key_val = key;
	keyboard_action = action;
	setType(KEYBOARD_EVENT);
}

// Set key in event.
void df::EventKeyboard::setKey(Keyboard::Key new_key)
{
	key_val = new_key;
}

// Get key from event.
df::Keyboard::Key df::EventKeyboard::getKey() const
{
	return key_val;
}

// Set keyboard event action.
void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action)
{
	keyboard_action = new_action;
}

// Get keyboard event action.
df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const
{
	return keyboard_action;
}
