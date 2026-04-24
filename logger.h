#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>

void init_logger(const char* filepath);
void log_access(const char* username, const char* filename, time_t timestamp, const char* result);
void view_logs();

#endif // LOGGER_H
