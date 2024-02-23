#include "LogManager.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>


df::LogManager::LogManager() {
	setType("LogManager");
}

// If logfile is open, close it.
df::LogManager::~LogManager()
{
	shutDown();
}

// Get the one and only instance of the LogManager.
df::LogManager& df::LogManager::getInstance()
{
	static LogManager logManager;
	return logManager;
}

// Start up the LogManager (open logfile "dragonfly.log").
int df::LogManager::startUp()
{	
	Manager::startUp();
	fopen_s(&p_f, LOGFILE_NAME.c_str(), "w");
	return 0;
}

// Shut down the LogManager (close logfile).
void df::LogManager::shutDown()
{
	Manager::shutDown();
	if (p_f != NULL) {
		fclose(p_f);
	}
}

// Set flush of logfile after each write.
void df::LogManager::setFlush(bool do_flush)
{
	this->do_flush = do_flush;
}

// Write to logfile. Supports printf() formatting.
// Return number of bytes written, -1 if error.
int df::LogManager::writeLog(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int output = vfprintf(p_f, fmt, args);
	if (do_flush)
		fflush(p_f);
	va_end(args);
	return output;
	
}
