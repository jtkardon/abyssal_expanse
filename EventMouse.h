#pragma once
#include "Event.h"
#include "Vector.h"

namespace df {


	const std::string MOUSE_EVENT = "df::mouse";

	// Set of mouse buttons recognized by Dragonfly.
	namespace Mouse {
		enum Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,
		};
	}
	// Set of mouse actions recognized by Dragonfly.
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED,
		RELEASED,
	};

	class EventMouse : public Event {

	private:
		EventMouseAction mouse_action;  // Mouse action.
		Mouse::Button mouse_button;     // Mouse button.
		Vector mouse_xy;                // Mouse (x,y) coordinates.
	public:
		EventMouse();

		// Load mouse event's action.
		void setMouseAction(EventMouseAction new_mouse_action);

		// Get mouse event's action.
		EventMouseAction getMouseAction() const;

		// Set mouse event's button.
		void setMouseButton(Mouse::Button new_mouse_button);

		// Get mouse event's button.
		Mouse::Button getMouseButton() const;

		// Set mouse event's position.
		void setMousePosition(Vector new_mouse_xy);

		// Get mouse event's y position.
		Vector getMousePosition() const;
	};
}