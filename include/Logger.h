#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <string>

using std::string;

/**
* Class used for logging.
* No instances are needed, all the methods are static.
*/
class Logger {

	public:
		/**
		* The default logger.
		* Logs the desired message with a "Log: " prefix.
		* @param message_ : the message to log.
		*/
		static void log(const string& message_);

		/**
		* The logger for warnings.
		* Logs the desired message with a "Warning: " prefix.
		* @param message_ : the message to log.
		*/
		static void warning(const string& message_);

		/**
		* The logger for errors.
		* Logs the desired message with an "Error: " prefix.
		* @param message_ : the message to log.
		*/
		static void error(const string& message_);

};

#endif //INCLUDE_LOGGER_H
