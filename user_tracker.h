#ifndef USER_TRACKER_H
#define USER_TRACKER_H

#include <time.h>

typedef struct User {
    char username[50];
    int access_attempts_window; // Number of accesses inside the current time window
    time_t first_attempt_time;  // Start of the tracking window
    int is_restricted;          // 1 = banned by rule engine, 0 = allowed
    struct User* next;
} User;

void register_user(const char* username);
User* find_user(const char* username);
void display_users();
void free_all_users();

#endif // USER_TRACKER_H
