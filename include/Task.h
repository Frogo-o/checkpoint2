#ifndef TASK_H
#define TASK_H

#include "ActivityLog.h"
#include "BoardItem.h"
#include "ChecklistItem.h"
#include "Member.h"
#include "Tag.h"
#include "TaskTypes.h"

#include <vector>

using namespace std;

class Task : public BoardItem {
    TaskStatus status;
    TaskPriority priority;
    TaskStage stage;
    string dueDate;
    Member assignee;
    vector<Tag> tags;
    vector<ChecklistItem> checklist;
    vector<ActivityLog> history;

public:
    Task(int id = 0, string title = "", string description = "",
         TaskPriority priority = TaskPriority::Medium, TaskStage stage = TaskStage::Backlog,
         string dueDate = "", Member assignee = Member(),
         TaskStatus status = TaskStatus::Active, bool addCreationLog = true);

    TaskStatus getStatus() const;
    TaskStage getStage() const;
    TaskPriority getPriority() const;
    const string &getDueDate() const;
    const Member &getAssignee() const;
    const vector<Tag> &getTags() const;
    vector<ChecklistItem> &getChecklist();
    const vector<ChecklistItem> &getChecklist() const;
    const vector<ActivityLog> &getHistory() const;
    bool isDone() const;
    bool isOverdue() const;
    void setStatus(TaskStatus value);
    void setPriority(TaskPriority value);
    void setStage(TaskStage value);
    void setDueDate(const string &value);
    void setAssignee(const Member &value);
    void addTag(const string &name);
    void loadTag(const string &name);
    void addChecklistItem(const string &text);
    void loadChecklistItem(const string &text, bool completed);
    void loadHistoryEntry(const string &action, const string &date);
    void displayInfo() const override;
};

#endif


