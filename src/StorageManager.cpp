#include "../include/StorageManager.h"
#include "../include/TaskTypes.h"
#include "../include/Utils.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void StorageManager::saveToFile(const ProjectBoard &board, const string &fileName)
{
    vector<ProjectBoard> boards;
    boards.push_back(board);
    saveToFile(boards, fileName);
}

void StorageManager::saveToFile(const vector<ProjectBoard> &boards, const string &fileName)
{
    ofstream file(fileName);
    for (const auto &board : boards) {
        file << "BOARD|" << board.getName() << "\n";
    for (const auto &project : board.getProjects()) {
        file << "PROJECT|" << project.getId() << "|" << project.getTitle() << "|"
             << project.getDescription() << "|" << project.getStartDate() << "|"
             << project.getDueDate() << "\n";
        for (const auto &task : project.getTasks()) {
            file << "TASK|" << task.getId() << "|" << task.getTitle() << "|" << task.getDescription()
                 << "|" << toString(task.getStatus()) << "|" << toString(task.getPriority())
                 << "|" << toString(task.getStage()) << "|" << task.getDueDate() << "|"
                 << task.getAssignee().getName() << "|" << task.getAssignee().getEmail() << "\n";
            for (const auto &tag : task.getTags()) file << "TAG|" << tag.getName() << "\n";
            for (const auto &item : task.getChecklist()) {
                file << "CHECK|" << (item.isCompleted() ? "1" : "0") << "|" << item.getText() << "\n";
            }
            for (const auto &entry : task.getHistory()) {
                file << "HISTORY|" << entry.getDate() << "|" << entry.getAction() << "\n";
            }
        }
    }
    }
}

bool StorageManager::loadFromFile(ProjectBoard &board, const string &fileName)
{
    vector<ProjectBoard> boards;
    if (!loadFromFile(boards, fileName) || boards.empty()) return false;
    board = boards.front();
    return true;
}

bool StorageManager::loadFromFile(vector<ProjectBoard> &boards, const string &fileName)
{
    ifstream file(fileName);
    if (!file) return false;
    boards.clear();
    string line;
    Project *currentProject = nullptr;
    Task *currentTask = nullptr;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> parts;
        string part;
        while (getline(ss, part, '|')) parts.push_back(part);
        if (parts.empty()) continue;
        if (parts[0] == "BOARD" && parts.size() > 1) {
            boards.emplace_back(parts[1]);
            currentProject = nullptr;
            currentTask = nullptr;
        } else if (parts[0] == "PROJECT" && parts.size() >= 6) {
            if (boards.empty()) boards.emplace_back("Loaded Board");
            boards.back().addProject(Project(stoi(parts[1]), parts[2], parts[3], parts[4], parts[5]));
            currentProject = &boards.back().getProjects().back();
            currentTask = nullptr;
        } else if (parts[0] == "TASK" && parts.size() >= 9 && currentProject) {
            string email = parts.size() >= 10 ? parts[9] : "";
            currentProject->addTask(Task(stoi(parts[1]), parts[2], parts[3],
                                         priorityFromString(parts[5]), stageFromString(parts[6]),
                                         parts[7], Member(parts[8], email), statusFromString(parts[4]), false));
            currentTask = &currentProject->getTasks().back();
        } else if (parts[0] == "TAG" && parts.size() >= 2 && currentTask) {
            currentTask->loadTag(parts[1]);
        } else if (parts[0] == "CHECK" && parts.size() >= 3 && currentTask) {
            currentTask->loadChecklistItem(parts[2], parts[1] == "1");
        } else if (parts[0] == "HISTORY" && parts.size() >= 3 && currentTask) {
            currentTask->loadHistoryEntry(parts[2], parts[1]);
        }
    }
    return true;
}


