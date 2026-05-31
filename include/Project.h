#ifndef PROJECT_H
#define PROJECT_H

#include "BoardItem.h"
#include "Task.h"

#include <vector>

using namespace std;

class Project : public BoardItem {
    string startDate;
    string dueDate;
    vector<Task> tasks;

public:
    Project(int id = 0, string title = "", string description = "",
            string startDate = "", string dueDate = "");
    vector<Task> &getTasks();
    const vector<Task> &getTasks() const;
    const string &getStartDate() const;
    const string &getDueDate() const;
    void setStartDate(const string &value);
    void setDueDate(const string &value);
    void addTask(const Task &task);
    bool removeTask(int taskId);
    double calculateProgress() const;
    void displayInfo() const override;
};

#endif


