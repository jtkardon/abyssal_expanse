#ifndef __EVENT_H__
#define __EVENT_H__
#include <string>
namespace df {


	const std::string UNDEFINED_EVENT = "df::undefined";

	class Event {

	private:
		std::string event_type;  // Holds event type.

	public:
		// Create base event.
		Event();

		// Destructor.
		virtual ~Event();

		// Set event type.
		void setType(std::string new_type);

		// Get event type.
		std::string getType() const;
	};

}
#endif