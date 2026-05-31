#ifndef ACTIVITY_LOG_H
#define ACTIVITY_LOG_H

#include <string>

using namespace std;

class ActivityLog {
    string action;
    string date;

public:
    ActivityLog(string action = "", string date = "");
    const string &getAction() const;
    const string &getDate() const;
    void displayInfo() const;
};

#endif


