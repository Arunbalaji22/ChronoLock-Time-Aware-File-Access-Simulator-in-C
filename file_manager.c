#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_manager.h"

static VirtualFile* head_file = NULL;

void create_file(const char* filename, const char* owner_username, int start_hour, int end_hour) {
    if (find_file(filename) != NULL) {
        printf("File '%s' already exists.\n", filename);
        return;
    }

    if (start_hour < 0 || start_hour > 23 || end_hour < 0 || end_hour > 23) {
        printf("Invalid access hours. Must be between 0 and 23.\n");
        return;
    }

    VirtualFile* new_file = (VirtualFile*)malloc(sizeof(VirtualFile));
    if (!new_file) {
        printf("Memory allocation failed for new file '%s'.\n", filename);
        return;
    }

    strncpy(new_file->filename, filename, sizeof(new_file->filename) - 1);
    new_file->filename[sizeof(new_file->filename) - 1] = '\0';
    
    strncpy(new_file->owner_username, owner_username, sizeof(new_file->owner_username) - 1);
    new_file->owner_username[sizeof(new_file->owner_username) - 1] = '\0';

    new_file->start_hour = start_hour;
    new_file->end_hour = end_hour;
    new_file->next = head_file;
    
    head_file = new_file;
    printf("File '%s' created successfully by owner '%s' (Access: %02d:00 - %02d:00).\n", filename, owner_username, start_hour, end_hour);
}

VirtualFile* find_file(const char* filename) {
    VirtualFile* current = head_file;
    while (current != NULL) {
        if (strcmp(current->filename, filename) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void display_files() {
    VirtualFile* current = head_file;
    if (current == NULL) {
        printf("No virtual files exist.\n");
        return;
    }

    printf("\n--- Virtual File System ---\n");
    while (current != NULL) {
        printf("File: %-20s | Owner: %-15s | Allowed Hours: %02d:00 to %02d:00\n",
               current->filename, current->owner_username, current->start_hour, current->end_hour);
        current = current->next;
    }
    printf("---------------------------\n");
}

void free_all_files() {
    VirtualFile* current = head_file;
    while (current != NULL) {
        VirtualFile* temp = current;
        current = current->next;
        free(temp);
    }
    head_file = NULL;
}
