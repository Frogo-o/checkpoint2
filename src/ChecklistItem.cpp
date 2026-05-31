#include "../include/ChecklistItem.h"

#include <iostream>
#include <utility>

using namespace std;

ChecklistItem::ChecklistItem(string text, bool completed)
    : text(move(text)), completed(completed) {}

const string &ChecklistItem::getText() const { return text; }
bool ChecklistItem::isCompleted() const { return completed; }
void ChecklistItem::markDone() { completed = true; }
void ChecklistItem::displayInfo() const { cout << (completed ? "[x] " : "[ ] ") << text << "\n"; }


