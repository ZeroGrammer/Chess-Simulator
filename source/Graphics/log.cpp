
#include "log.hpp"

void Graphics::log(LogLevel log_level, const char *message, ...) {

    va_list args;
    va_start(args, message);

    char buffer[1024] = { };

    std::vsnprintf(buffer, sizeof(buffer), message, args);

    va_end(args);

    if (log_level == INFO) printf("\033[%dmINFO: %s", log_level, buffer);
    if (log_level == WAR)  printf("\033[%dmWARNING: %s", log_level, buffer);
    if (log_level == ERR)  printf("\033[%dmERROR: %s", log_level, buffer);

    printf("\033[0m"); // reseting the color
    printf("\n");
}
