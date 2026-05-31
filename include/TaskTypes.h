#ifndef TASK_TYPES_H
#define TASK_TYPES_H

#include <string>

using namespace std;

enum class TaskStatus { Active, Archived };
enum class TaskPriority { Low, Medium, High, Urgent };
enum class TaskStage { Backlog, ToDo, InProgress, Review, Done };

string toString(TaskStatus value);
string toString(TaskPriority value);
string toString(TaskStage value);
TaskStatus statusFromString(const string &value);
TaskPriority priorityFromInt(int value);
TaskPriority priorityFromString(const string &value);
TaskStage stageFromInt(int value);
TaskStage stageFromString(const string &value);

#endif


