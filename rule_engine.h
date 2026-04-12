#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include "user_tracker.h"
#include "file_manager.h"

#define SUSPICIOUS_ATTEMPTS_LIMIT 5
#define ATTEMPTS_WINDOW_SECONDS 60

int check_file_time_access(VirtualFile* file);
void record_access_attempt(User* user);
void execute_rule_engine(User* user);
int request_file_access(User* user, VirtualFile* file);

#endif // RULE_ENGINE_H
