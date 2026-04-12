# ChronoLock: Time-Aware File Access Simulator in C

This project simulates an intelligent virtual file system where file access depends on time rules, user behavior patterns, and dynamic permissions. 

## Features
- **Virtual File System:** Creates files virtually using custom structures, tracking filename, owner, missing hours.
- **Time-Based Access Control:** Allows file access only during configured time boundaries.
- **User Behavior Tracking:** Logs user sessions and tracks the number of accesses.
- **Rule Engine:** Dynamically restricts privileges if suspicious behavior (e.g. repeated access attempts in a short timeframe) is detected.
- **Logging System:** Records persistent access logs locally (`logs.txt`).
- **Standard C:** Written purely in standard C implementation. No external dependencies needed. 

## How to Build
Navigate into the projects directory and compile utilizing `gcc`:

```bash
gcc main.c file_manager.c logger.c user_tracker.c rule_engine.c -o chronolock -Wall -Wextra
```

## How to Run

1. Simply run the output executable inside your terminal:
   ```bash
   ./chronolock
   ```
2. Interact with the system through the Command Line Menu. Example of creating a system user and testing access restrictions. 
