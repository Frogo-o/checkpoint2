#include "../include/TaskController.h"

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

vector<Task *> TaskController::searchTasks(ProjectBoard &board, const string &keyword)
{
    vector<Task *> found;
    for (auto &project : board.getProjects()) {
        for (auto &task : project.getTasks()) {
            if (task.getTitle().find(keyword) != string::npos ||
                task.getDescription().find(keyword) != string::npos) {
                found.push_back(&task);
            }
        }
    }
    return found;
}

vector<Task *> TaskController::filterByStage(ProjectBoard &board, TaskStage stage)
{
    vector<Task *> found;
    for (auto &project : board.getProjects()) {
        for (auto &task : project.getTasks()) {
            if (task.getStage() == stage) found.push_back(&task);
        }
    }
    return found;
}

vector<Task *> TaskController::filterByPriority(ProjectBoard &board, TaskPriority priority)
{
    vector<Task *> found;
    for (auto &project : board.getProjects()) {
        for (auto &task : project.getTasks()) {
            if (task.getPriority() == priority) found.push_back(&task);
        }
    }
    return found;
}

vector<Task *> TaskController::filterByTag(ProjectBoard &board, const string &tagName)
{
    vector<Task *> found;
    for (auto &project : board.getProjects()) {
        for (auto &task : project.getTasks()) {
            for (const auto &tag : task.getTags()) {
                if (tag.getName() == tagName) {
                    found.push_back(&task);
                    break;
                }
            }
        }
    }
    return found;
}

vector<Task *> TaskController::filterByAssignee(ProjectBoard &board, const string &assigneeName)
{
    vector<Task *> found;
    for (auto &project : board.getProjects()) {
        for (auto &task : project.getTasks()) {
            if (task.getAssignee().getName() == assigneeName) found.push_back(&task);
        }
    }
    return found;
}

vector<Task *> TaskController::filterByDueDate(ProjectBoard &board, const string &dueDate)
{
    vector<Task *> found;
    for (auto &project : board.getProjects()) {
        for (auto &task : project.getTasks()) {
            if (task.getDueDate() == dueDate) found.push_back(&task);
        }
    }
    return found;
}

void TaskController::sortTasksByDueDate(vector<Task> &tasks)
{
    sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.getDueDate() < b.getDueDate();
    });
}

void TaskController::sortTasksByPriority(vector<Task> &tasks)
{
    sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return static_cast<int>(a.getPriority()) > static_cast<int>(b.getPriority());
    });
}

void TaskController::sortTasksByTitle(vector<Task> &tasks)
{
    sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.getTitle() < b.getTitle();
    });
}

void TaskController::sortTasksByStage(vector<Task> &tasks)
{
    sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return static_cast<int>(a.getStage()) < static_cast<int>(b.getStage());
    });
}

void TaskController::showStatistics(const ProjectBoard &board)
{
    int total = 0;
    int completed = 0;
    int overdue = 0;
    map<string, int> byStage;
    map<string, int> byPriority;

    for (const auto &project : board.getProjects()) {
        for (const auto &task : project.getTasks()) {
            ++total;
            if (task.isDone()) ++completed;
            if (task.isOverdue()) ++overdue;
            byStage[toString(task.getStage())]++;
            byPriority[toString(task.getPriority())]++;
        }
    }

    cout << "\nStatistics\n";
    cout << "Total tasks: " << total << "\n";
    cout << "Completed tasks: " << completed << "\n";
    cout << "Overdue tasks: " << overdue << "\n";
    cout << "By stage:\n";
    for (const auto &entry : byStage) cout << "  " << entry.first << ": " << entry.second << "\n";
    cout << "By priority:\n";
    for (const auto &entry : byPriority) cout << "  " << entry.first << ": " << entry.second << "\n";
}


