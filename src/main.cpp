#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class BoardItem {
protected:
    int id;
    string title;
    string description;
    string createdAt;

public:
    BoardItem(int id, string title, string description, string createdAt = "2026-05-17")
        : id(id), title(move(title)), description(move(description)), createdAt(move(createdAt)) {}
    virtual ~BoardItem() = default;
    int getId() const { return id; }
    const string &getTitle() const { return title; }
    virtual void displayInfo() const = 0;
};

enum class TaskStatus { Active, Archived };
enum class TaskPriority { Low, Medium, High, Urgent };
enum class TaskStage { Backlog, ToDo, InProgress, Review, Done };

class Project : public BoardItem {
public:
    Project(int id, string title, string description) : BoardItem(id, move(title), move(description)) {}
    void displayInfo() const override { cout << "Project: " << title << "\n"; }
};

class Task : public BoardItem {
public:
    Task(int id, string title, string description) : BoardItem(id, move(title), move(description)) {}
    void displayInfo() const override { cout << "Task: " << title << "\n"; }
};

int main()
{
    Project project(1, "OOP Checkpoint", "Task manager project");
    Task task(2, "Implement class hierarchy", "BoardItem inheritance");
    project.displayInfo();
    task.displayInfo();
    return 0;
}
