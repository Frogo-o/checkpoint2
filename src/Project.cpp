#include "../include/Project.h"
#include "../include/Utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>

using namespace std;

Project::Project(int id, string title, string description, string startDate, string dueDate)
    : BoardItem(id, move(title), move(description), todayDate()),
      startDate(startDate.empty() ? todayDate() : move(startDate)), dueDate(move(dueDate)) {}

vector<Task> &Project::getTasks() { return tasks; }
const vector<Task> &Project::getTasks() const { return tasks; }
const string &Project::getStartDate() const { return startDate; }
const string &Project::getDueDate() const { return dueDate; }
void Project::setStartDate(const string &value) { startDate = value; }
void Project::setDueDate(const string &value) { dueDate = value; }
void Project::addTask(const Task &task) { tasks.push_back(task); }

bool Project::removeTask(int taskId)
{
    auto oldSize = tasks.size();
    tasks.erase(remove_if(tasks.begin(), tasks.end(), [taskId](const Task &task) {
                    return task.getId() == taskId;
                }),
                tasks.end());
    return tasks.size() != oldSize;
}

double Project::calculateProgress() const
{
    if (tasks.empty()) return 0.0;
    int done = count_if(tasks.begin(), tasks.end(), [](const Task &task) { return task.isDone(); });
    return done * 100.0 / tasks.size();
}

void Project::displayInfo() const
{
    cout << "[" << id << "] " << title << " | " << startDate << " -> " << dueDate
              << " | tasks: " << tasks.size() << " | progress: " << fixed
              << setprecision(0) << calculateProgress() << "%\n";
    cout << "    " << description << "\n";
}


