#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"
#include "user_tracker.h"
#include "file_manager.h"
#include "rule_engine.h"

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    init_logger("logs.txt");
    
    int choice;
    char username[50];
    char filename[100];
    int st_hr, end_hr;

    // Optional: Pre-populate some data for ease of demonstration if desired,
    // but the requirements say "interactive menu".

    printf("========================================================\n");
    printf("   ChronoLock: Time-Aware File Access Simulator in C    \n");
    printf("========================================================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create File\n");
        printf("2. Register User\n");
        printf("3. Access File\n");
        printf("4. View Logs\n");
        printf("5. System Status (Users & Files)\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            flush_input();
            continue;
        }
        flush_input();

        switch (choice) {
            case 1:
                printf("Enter filename: ");
                if (fgets(filename, sizeof(filename), stdin)) {
                    filename[strcspn(filename, "\n")] = '\0';
                }
                printf("Enter owner username: ");
                if (fgets(username, sizeof(username), stdin)) {
                    username[strcspn(username, "\n")] = '\0';
                }
                printf("Enter start hour (0-23): ");
                scanf("%d", &st_hr);
                printf("Enter end hour (0-23): ");
                scanf("%d", &end_hr);
                flush_input();
                
                create_file(filename, username, st_hr, end_hr);
                break;
                
            case 2:
                printf("Enter new username: ");
                if (fgets(username, sizeof(username), stdin)) {
                    username[strcspn(username, "\n")] = '\0';
                }
                register_user(username);
                break;
                
            case 3:
                printf("Enter your username: ");
                if (fgets(username, sizeof(username), stdin)) {
                    username[strcspn(username, "\n")] = '\0';
                }
                printf("Enter the filename you want to access: ");
                if (fgets(filename, sizeof(filename), stdin)) {
                    filename[strcspn(filename, "\n")] = '\0';
                }
                
                User* u = find_user(username);
                if (!u) {
                    printf("User '%s' not found. Please register first.\n", username);
                    break;
                }
                
                VirtualFile* f = find_file(filename);
                if (!f) {
                    printf("File '%s' not found in the virtual file system.\n", filename);
                    break;
                }
                
                request_file_access(u, f);
                break;
                
            case 4:
                view_logs();
                break;
                
            case 5:
                display_users();
                display_files();
                break;

            case 6:
                printf("Exiting ChronoLock simulator. Freeing memory...\n");
                free_all_users();
                free_all_files();
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
