#include "../include/TaskTypes.h"

using namespace std;

string toString(TaskStatus value)
{
    return value == TaskStatus::Active ? "Active" : "Archived";
}

string toString(TaskPriority value)
{
    switch (value) {
    case TaskPriority::Low: return "Low";
    case TaskPriority::Medium: return "Medium";
    case TaskPriority::High: return "High";
    case TaskPriority::Urgent: return "Urgent";
    }
    return "Low";
}

string toString(TaskStage value)
{
    switch (value) {
    case TaskStage::Backlog: return "Backlog";
    case TaskStage::ToDo: return "To Do";
    case TaskStage::InProgress: return "In Progress";
    case TaskStage::Review: return "Review";
    case TaskStage::Done: return "Done";
    }
    return "Backlog";
}

TaskStatus statusFromString(const string &value)
{
    return value == "Archived" ? TaskStatus::Archived : TaskStatus::Active;
}

TaskPriority priorityFromInt(int value)
{
    if (value == 2) return TaskPriority::Medium;
    if (value == 3) return TaskPriority::High;
    if (value == 4) return TaskPriority::Urgent;
    return TaskPriority::Low;
}

TaskPriority priorityFromString(const string &value)
{
    if (value == "Medium") return TaskPriority::Medium;
    if (value == "High") return TaskPriority::High;
    if (value == "Urgent") return TaskPriority::Urgent;
    return TaskPriority::Low;
}

TaskStage stageFromInt(int value)
{
    if (value == 2) return TaskStage::ToDo;
    if (value == 3) return TaskStage::InProgress;
    if (value == 4) return TaskStage::Review;
    if (value == 5) return TaskStage::Done;
    return TaskStage::Backlog;
}

TaskStage stageFromString(const string &value)
{
    if (value == "To Do") return TaskStage::ToDo;
    if (value == "In Progress") return TaskStage::InProgress;
    if (value == "Review") return TaskStage::Review;
    if (value == "Done") return TaskStage::Done;
    return TaskStage::Backlog;
}


