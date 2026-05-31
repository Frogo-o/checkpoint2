#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

#include "ProjectBoard.h"
#include "TaskTypes.h"

#include <vector>

using namespace std;

class TaskController {
public:
    static vector<Task *> searchTasks(ProjectBoard &board, const string &keyword);
    static vector<Task *> filterByStage(ProjectBoard &board, TaskStage stage);
    static vector<Task *> filterByPriority(ProjectBoard &board, TaskPriority priority);
    static vector<Task *> filterByTag(ProjectBoard &board, const string &tagName);
    static vector<Task *> filterByAssignee(ProjectBoard &board, const string &assigneeName);
    static vector<Task *> filterByDueDate(ProjectBoard &board, const string &dueDate);
    static void sortTasksByDueDate(vector<Task> &tasks);
    static void sortTasksByPriority(vector<Task> &tasks);
    static void sortTasksByTitle(vector<Task> &tasks);
    static void sortTasksByStage(vector<Task> &tasks);
    static void showStatistics(const ProjectBoard &board);
};

#endif


