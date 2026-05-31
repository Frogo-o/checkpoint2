#ifndef CHECKLIST_ITEM_H
#define CHECKLIST_ITEM_H

#include <string>

using namespace std;

class ChecklistItem {
    string text;
    bool completed;

public:
    ChecklistItem(string text = "", bool completed = false);
    const string &getText() const;
    bool isCompleted() const;
    void markDone();
    void displayInfo() const;
};

#endif


