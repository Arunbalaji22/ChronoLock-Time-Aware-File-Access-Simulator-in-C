#include <stdio.h>
#include <time.h>
#include <string.h>
#include "logger.h"

static char log_filepath[256];

void init_logger(const char* filepath) {
    strncpy(log_filepath, filepath, sizeof(log_filepath) - 1);
    log_filepath[sizeof(log_filepath) - 1] = '\0';
}

void log_access(const char* username, const char* filename, time_t timestamp, const char* result) {
    FILE* file = fopen(log_filepath, "a");
    if (!file) {
        printf("Error: Could not open log file %s\n", log_filepath);
        return;
    }

    struct tm* timeinfo = localtime(&timestamp);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(file, "[%s] User: %-15s | File: %-20s | Result: %s\n", time_str, username, filename, result);
    fclose(file);
}

void view_logs() {
    FILE* file = fopen(log_filepath, "r");
    if (!file) {
        printf("No logs found or unable to open log file %s.\n", log_filepath);
        return;
    }

    printf("\n--- System Access Logs ---\n");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    printf("--------------------------\n");
    fclose(file);
}
