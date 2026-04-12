#include <stdio.h>
#include <time.h>
#include "rule_engine.h"
#include "logger.h"

int check_file_time_access(VirtualFile* file) {
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    int current_hour = timeinfo->tm_hour;

    if (file->start_hour < file->end_hour) {
        if (current_hour >= file->start_hour && current_hour < file->end_hour) {
            return 1;
        }
    } else if (file->start_hour > file->end_hour) {
        // Over-night access (e.g., 22:00 to 06:00)
        if (current_hour >= file->start_hour || current_hour < file->end_hour) {
            return 1;
        }
    } else {
        // Start == End, accessible 24/7 or inaccessible? Let's assume 24/7
        return 1;
    }
    
    return 0; // Out of bounds
}

void record_access_attempt(User* user) {
    time_t now = time(NULL);
    
    // If the window has expired, reset the tracking window
    if (difftime(now, user->first_attempt_time) > ATTEMPTS_WINDOW_SECONDS) {
        user->first_attempt_time = now;
        user->access_attempts_window = 1;
    } else {
        user->access_attempts_window++;
    }
}

void execute_rule_engine(User* user) {
    if (user->is_restricted) {
        return; // Already restricted
    }

    if (user->access_attempts_window > SUSPICIOUS_ATTEMPTS_LIMIT) {
        printf("\n\033[31m[WARNING] Suspicious activity detected for user '%s'. Restricting access.\033[0m\n", user->username);
        user->is_restricted = 1;
    }
}

int request_file_access(User* user, VirtualFile* file) {
    time_t now = time(NULL);
    
    if (user->is_restricted) {
        printf("Access Denied: User '%s' is currently restricted due to suspicious activity.\n", user->username);
        log_access(user->username, file->filename, now, "DENIED (Restricted)");
        return 0;
    }

    record_access_attempt(user);
    execute_rule_engine(user);

    // If user got restricted right after the attempt was recorded
    if (user->is_restricted) {
        printf("Access Denied: User '%s' has just been restricted due to suspicious activity.\n", user->username);
        log_access(user->username, file->filename, now, "DENIED (Restricted)");
        return 0;
    }

    if (!check_file_time_access(file)) {
        printf("Access Denied: File '%s' is only accessible between %02d:00 and %02d:00.\n", 
               file->filename, file->start_hour, file->end_hour);
        log_access(user->username, file->filename, now, "DENIED (Time Bounds)");
        return 0;
    }

    printf("Access Granted: User '%s' accessed file '%s' successfully.\n", user->username, file->filename);
    log_access(user->username, file->filename, now, "GRANTED");
    return 1;
}
