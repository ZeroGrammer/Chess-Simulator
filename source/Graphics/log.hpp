
#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <stdio.h>
#include <cstdarg>
#include <string>

namespace Graphics {

// the number are the color codes for the terminal
enum LogLevel {
    INFO = 97,
    WAR = 93,
    ERR = 91
};

void log(LogLevel log_level, const char *message, ...);

} // namespace Graphics

#endif // _LOG_HPP_
