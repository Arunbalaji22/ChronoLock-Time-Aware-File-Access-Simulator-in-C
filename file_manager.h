#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

typedef struct VirtualFile {
    char filename[100];
    char owner_username[50];
    int start_hour;             // e.g., 9 for 09:00
    int end_hour;               // e.g., 17 for 17:00
    struct VirtualFile* next;
} VirtualFile;

void create_file(const char* filename, const char* owner_username, int start_hour, int end_hour);
VirtualFile* find_file(const char* filename);
void display_files();
void free_all_files();

#endif // FILE_MANAGER_H
