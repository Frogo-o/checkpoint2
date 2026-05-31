#include "../include/Task.h"
#include "../include/Utils.h"

#include <iostream>
#include <utility>

using namespace std;

Task::Task(int id, string title, string description, TaskPriority priority,
           TaskStage stage, string dueDate, Member assignee, TaskStatus status, bool addCreationLog)
    : BoardItem(id, move(title), move(description), todayDate()),
      status(status), priority(priority), stage(stage), dueDate(move(dueDate)), assignee(move(assignee))
{
    if (addCreationLog) history.emplace_back("Task created");
}

TaskStatus Task::getStatus() const { return status; }
TaskStage Task::getStage() const { return stage; }
TaskPriority Task::getPriority() const { return priority; }
const string &Task::getDueDate() const { return dueDate; }
const Member &Task::getAssignee() const { return assignee; }
const vector<Tag> &Task::getTags() const { return tags; }
vector<ChecklistItem> &Task::getChecklist() { return checklist; }
const vector<ChecklistItem> &Task::getChecklist() const { return checklist; }
const vector<ActivityLog> &Task::getHistory() const { return history; }
bool Task::isDone() const { return stage == TaskStage::Done; }
bool Task::isOverdue() const { return !isDone() && !dueDate.empty() && dueDate < todayDate(); }

void Task::setStatus(TaskStatus value)
{
    status = value;
    history.emplace_back("Status changed to " + toString(value));
}

void Task::setPriority(TaskPriority value)
{
    priority = value;
    history.emplace_back("Priority changed to " + toString(value));
}

void Task::setStage(TaskStage value)
{
    stage = value;
    history.emplace_back("Stage changed to " + toString(value));
}

void Task::setDueDate(const string &value)
{
    dueDate = value;
    history.emplace_back("Due date changed to " + value);
}

void Task::setAssignee(const Member &value)
{
    assignee = value;
    history.emplace_back("Assignee changed to " + value.getName());
}

void Task::addTag(const string &name)
{
    tags.emplace_back(name);
    history.emplace_back("Tag added: " + name);
}

void Task::loadTag(const string &name) { tags.emplace_back(name); }

void Task::addChecklistItem(const string &text)
{
    checklist.emplace_back(text);
    history.emplace_back("Checklist item added: " + text);
}

void Task::loadChecklistItem(const string &text, bool completed) { checklist.emplace_back(text, completed); }
void Task::loadHistoryEntry(const string &action, const string &date) { history.emplace_back(action, date); }

void Task::displayInfo() const
{
    cout << "[" << id << "] " << title << " | " << toString(stage) << " | "
              << toString(priority) << " | " << toString(status) << " | due: " << dueDate
              << " | assigned to: " << assignee.getName();
    if (isOverdue()) cout << " | OVERDUE";
    cout << "\n    " << description << "\n";
    if (!tags.empty()) {
        cout << "    Tags: ";
        for (const auto &tag : tags) cout << "#" << tag.getName() << " ";
        cout << "\n";
    }
    if (!checklist.empty()) {
        cout << "    Checklist:\n";
        for (const auto &item : checklist) {
            cout << "    ";
            item.displayInfo();
        }
    }
}


