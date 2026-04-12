#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_tracker.h"

static User* head_user = NULL;

void register_user(const char* username) {
    if (find_user(username) != NULL) {
        printf("User '%s' is already registered.\n", username);
        return;
    }

    User* new_user = (User*)malloc(sizeof(User));
    if (!new_user) {
        printf("Memory allocation failed for new user '%s'.\n", username);
        return;
    }

    strncpy(new_user->username, username, sizeof(new_user->username) - 1);
    new_user->username[sizeof(new_user->username) - 1] = '\0';
    new_user->access_attempts_window = 0;
    new_user->first_attempt_time = 0;
    new_user->is_restricted = 0; // default to allowed
    new_user->next = head_user;
    
    head_user = new_user;
    printf("User '%s' registered successfully.\n", username);
}

User* find_user(const char* username) {
    User* current = head_user;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void display_users() {
    User* current = head_user;
    if (current == NULL) {
        printf("No users registered.\n");
        return;
    }

    printf("\n--- Registered Users ---\n");
    while (current != NULL) {
        printf("Username: %-15s | Status: %s | Access Attempts (Window): %d\n",
               current->username,
               current->is_restricted ? "\033[31mRESTRICTED\033[0m" : "\033[32mACTIVE\033[0m",
               current->access_attempts_window);
        current = current->next;
    }
    printf("------------------------\n");
}

void free_all_users() {
    User* current = head_user;
    while (current != NULL) {
        User* temp = current;
        current = current->next;
        free(temp);
    }
    head_user = NULL;
}
