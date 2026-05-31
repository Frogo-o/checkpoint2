#include "../include/ProjectBoard.h"

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

ProjectBoard::ProjectBoard(string name) : name(move(name)) {}
const string &ProjectBoard::getName() const { return name; }
vector<Project> &ProjectBoard::getProjects() { return projects; }
const vector<Project> &ProjectBoard::getProjects() const { return projects; }
void ProjectBoard::addProject(const Project &project) { projects.push_back(project); }

bool ProjectBoard::removeProject(int projectId)
{
    auto oldSize = projects.size();
    projects.erase(remove_if(projects.begin(), projects.end(), [projectId](const Project &project) {
                       return project.getId() == projectId;
                   }),
                   projects.end());
    return projects.size() != oldSize;
}

void ProjectBoard::showProjects() const
{
    cout << "\nBOARD: " << name << "\n";
    for (const auto &project : projects) project.displayInfo();
}


