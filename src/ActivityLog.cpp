#include "../include/ActivityLog.h"
#include "../include/Utils.h"

#include <iostream>
#include <utility>

using namespace std;

ActivityLog::ActivityLog(string action, string date)
    : action(move(action)), date(date.empty() ? todayDate() : move(date)) {}

const string &ActivityLog::getAction() const { return action; }
const string &ActivityLog::getDate() const { return date; }
void ActivityLog::displayInfo() const { cout << date << " - " << action << "\n"; }


