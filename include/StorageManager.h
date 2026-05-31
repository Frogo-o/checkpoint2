#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include "ProjectBoard.h"

#include <string>
#include <vector>

using namespace std;

class StorageManager {
public:
    static void saveToFile(const ProjectBoard &board, const string &fileName);
    static bool loadFromFile(ProjectBoard &board, const string &fileName);
    static void saveToFile(const vector<ProjectBoard> &boards, const string &fileName);
    static bool loadFromFile(vector<ProjectBoard> &boards, const string &fileName);
};

#endif


