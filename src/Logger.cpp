#include "Logger.h"
#include <iostream>

using std::cerr;
using std::endl;

void Logger::log(const string& message_){
	cerr << "[Log]:     " << message_ << endl;
}

void Logger::warning(const string& message_){
	cerr << "[Warning]: " << message_ << endl;
}

void Logger::error(const string& message_){
	cerr << "[Error]:   " << message_ << endl;
}
