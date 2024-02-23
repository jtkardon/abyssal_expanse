#pragma once
#include "Event.h"


namespace df {

	const std::string KEYBOARD_EVENT = "df::keyboard";

	// Types of keyboard actions Dragonfly recognizes.
	enum EventKeyboardAction {
		UNDEFINED_KEYBOARD_ACTION = -1, // Undefined
		KEY_PRESSED,                    // Was down
		KEY_RELEASED,                   // Was released
		KEY_DOWN,                       // Is down
	};

	// Keys Dragonfly recognizes.
	namespace Keyboard { // New namespace for clarity
		/*enum Key {
			UNDEFINED_KEY = -1,
			SPACE, RETURN, ESCAPE, TAB, LEFTARROW, RIGHTARROW,
			UPARROW, DOWNARROW, PAUSE, MINUS, PLUS, TILDE, PERIOD,
			COMMA, SLASH, LEFTCONTROL, RIGHTCONTROL, LEFTSHIFT,
			RIGHTSHIFT, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11,
			F12, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R,
			S, T, U, V, W, X, Y, Z, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6,
			NUM7, NUM8, NUM9, NUM0,
		};*/
		enum Key {
			UNDEFINED_KEY = -1, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R,
			S, T, U, V, W, X, Y, Z, NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6,
			NUM7, NUM8, NUM9, ESCAPE, LEFTCONTROL, LEFTSHIFT, LEFTALT, LEFTSYSTEM, 
			RIGHTCONTROL, RIGHTSHIFT, RIGHTALT, RIGHTSYSTEM, MENU, LEFTBRACKET, RIGHTBRACKET,
			SEMICOLON, COMMA, PERIOD, APOSTROPHE, SLASH, BACKSLASH, GRAVE, EQUAL,
			HYPHEN, SPACE, ENTER, BACKSPACE, TAB, PAGEUP, PAGEDOWN, END, HOME, INSERT, DELETE,
			ADD, SUBTRACT, MULTIPLY, DIVIDE, LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW, NUMPAD0,
			NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9, F1, F2,
			F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, PAUSE,
			
		};
	} // end of namespace input

	class EventKeyboard : public Event {

	private:
		Keyboard::Key key_val;                  // Key value.
		EventKeyboardAction keyboard_action;    // Key action.

	public:
		EventKeyboard();
		EventKeyboard(Keyboard::Key key, EventKeyboardAction action);


		// Set key in event.
		void setKey(Keyboard::Key new_key);

		// Get key from event.
		Keyboard::Key getKey() const;

		// Set keyboard event action.
		void setKeyboardAction(EventKeyboardAction new_action);

		// Get keyboard event action.
		EventKeyboardAction getKeyboardAction() const;
	};
}