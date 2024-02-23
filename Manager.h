#ifndef __MANAGER_H__
#define __MANAGER_H__
#include <string>
#include "Event.h"

namespace df {

	class Manager {
	private:
		std::string m_type; //Maanger type identifier
		bool m_is_started; //True when started successfully
	protected:
		//Set type identifier of manager
		void setType(std::string type);

	public:
		Manager();
		virtual ~Manager();

		// Get type of Manager
		std::string getType() const;

		// Startup Manager
		// Return 0 if ok, else negative number
		virtual int startUp();

		// Shutdown Manager
		virtual void shutDown();

		//return true when startUp() was executed ok, else false
		bool isStarted() const;

		//Send event to all Objects
		//Return count of number of events sent
		int onEvent(const Event* p_event);
	};
}
#endif