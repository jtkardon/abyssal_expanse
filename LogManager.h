#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

// System includes.
#include <stdio.h>
#include <string>
// Engine includes.
#include "Manager.h"
// Two-letter acronym for easier access to manager.
#define LM df::LogManager::getInstance()

namespace df {

	const std::string LOGFILE_NAME = "dragonfly.log";

	class LogManager : public Manager {
	private:
		LogManager();                      // Private (a singleton).
		LogManager(LogManager const&);    // No copying.
		void operator=(LogManager const&); // No assignment.
		bool do_flush;                     // True if fflush after each write.
		FILE* p_f;                         // Pointer to logfile structure.
	public:
		// If logfile is open, close it.
		~LogManager();

		// Get the one and only instance of the LogManager.
		static LogManager& getInstance();

		// Start up the LogManager (open logfile "dragonfly.log").
		int startUp();

		// Shut down the LogManager (close logfile).
		void shutDown();

		// Set flush of logfile after each write.
		void setFlush(bool do_flush = true);

		// Write to logfile. Supports printf() formatting.
		// Return number of bytes written, -1 if error.
		int writeLog(const char* fmt, ...);
	};
} // end of namespace df
#endif // __LOG_MANAGER_H__