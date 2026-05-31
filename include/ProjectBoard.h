#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include "Project.h"

#include <string>
#include <vector>

using namespace std;

class ProjectBoard {
    string name;
    vector<Project> projects;

public:
    ProjectBoard(string name = "Default Board");
    const string &getName() const;
    vector<Project> &getProjects();
    const vector<Project> &getProjects() const;
    void addProject(const Project &project);
    bool removeProject(int projectId);
    void showProjects() const;
};

#endif


