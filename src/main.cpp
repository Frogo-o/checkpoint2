#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string todayDate()
{
    time_t now = time(nullptr);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif
    ostringstream out;
    out << put_time(&local, "%Y-%m-%d");
    return out.str();
}

string readLine(const string &prompt)
{
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

int readInt(const string &prompt)
{
    cout << prompt;
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

class BoardItem {
protected:
    int id;
    string title;
    string description;
    string createdAt;

public:
    BoardItem(int id, string title, string description, string createdAt = todayDate())
        : id(id), title(move(title)), description(move(description)), createdAt(move(createdAt)) {}
    virtual ~BoardItem() = default;
    int getId() const { return id; }
    const string &getTitle() const { return title; }
    const string &getDescription() const { return description; }
    const string &getCreatedAt() const { return createdAt; }
    void setTitle(const string &value) { title = value; }
    void setDescription(const string &value) { description = value; }
    virtual void displayInfo() const = 0;
};

enum class TaskStatus { Active, Archived };
enum class TaskPriority { Low, Medium, High, Urgent };
enum class TaskStage { Backlog, ToDo, InProgress, Review, Done };

string toString(TaskStatus value) { return value == TaskStatus::Active ? "Active" : "Archived"; }

TaskStatus statusFromString(const string &value)
{
    return value == "Archived" ? TaskStatus::Archived : TaskStatus::Active;
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

class ChecklistItem {
    string text;
    bool completed;

public:
    ChecklistItem(string text = "", bool completed = false) : text(move(text)), completed(completed) {}
    const string &getText() const { return text; }
    bool isCompleted() const { return completed; }
    void markDone() { completed = true; }
    void displayInfo() const { cout << (completed ? "[x] " : "[ ] ") << text << "\n"; }
};

class Member {
    string name;
    string email;

public:
    Member(string name = "Unassigned", string email = "") : name(move(name)), email(move(email)) {}
    const string &getName() const { return name; }
    const string &getEmail() const { return email; }
    string serialize() const { return name + "<" + email + ">"; }
};

class Tag {
    string name;

public:
    Tag(string name = "") : name(move(name)) {}
    const string &getName() const { return name; }
};

class ActivityLog {
    string action;
    string date;

public:
    ActivityLog(string action = "", string date = todayDate()) : action(move(action)), date(move(date)) {}
    const string &getAction() const { return action; }
    const string &getDate() const { return date; }
    void displayInfo() const { cout << date << " - " << action << "\n"; }
};

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
    Task(int id = 0, string title = "", string description = "", TaskPriority priority = TaskPriority::Medium,
         TaskStage stage = TaskStage::Backlog, string dueDate = "", Member assignee = Member(),
         TaskStatus status = TaskStatus::Active, bool addCreationLog = true)
        : BoardItem(id, move(title), move(description)), status(status), priority(priority),
          stage(stage), dueDate(move(dueDate)), assignee(move(assignee))
    {
        if (addCreationLog) history.emplace_back("Task created");
    }

    TaskStatus getStatus() const { return status; }
    TaskStage getStage() const { return stage; }
    TaskPriority getPriority() const { return priority; }
    const string &getDueDate() const { return dueDate; }
    const Member &getAssignee() const { return assignee; }
    const vector<Tag> &getTags() const { return tags; }
    vector<ChecklistItem> &getChecklist() { return checklist; }
    const vector<ChecklistItem> &getChecklist() const { return checklist; }
    const vector<ActivityLog> &getHistory() const { return history; }
    bool isDone() const { return stage == TaskStage::Done; }
    bool isOverdue() const { return !isDone() && !dueDate.empty() && dueDate < todayDate(); }

    void setStatus(TaskStatus value)
    {
        status = value;
        history.emplace_back("Status changed to " + toString(value));
    }

    void setPriority(TaskPriority value)
    {
        priority = value;
        history.emplace_back("Priority changed to " + toString(value));
    }

    void setStage(TaskStage value)
    {
        stage = value;
        history.emplace_back("Stage changed to " + toString(value));
    }

    void addTag(const string &name)
    {
        tags.emplace_back(name);
        history.emplace_back("Tag added: " + name);
    }

    void loadTag(const string &name) { tags.emplace_back(name); }

    void addChecklistItem(const string &text)
    {
        checklist.emplace_back(text);
        history.emplace_back("Checklist item added: " + text);
    }

    void loadChecklistItem(const string &text, bool completed) { checklist.emplace_back(text, completed); }

    void loadHistoryEntry(const string &action, const string &date) { history.emplace_back(action, date); }

    void displayInfo() const override
    {
        cout << "[" << id << "] " << title << " | " << toString(stage) << " | "
             << toString(priority) << " | " << toString(status) << " | due: " << dueDate
             << " | assigned to: " << assignee.getName();
        if (isOverdue()) cout << " | OVERDUE";
        cout << "\n";
        cout << "    " << description << "\n";
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
};

class Project : public BoardItem {
    string startDate;
    string dueDate;
    vector<Task> tasks;

public:
    Project(int id = 0, string title = "", string description = "", string startDate = todayDate(), string dueDate = "")
        : BoardItem(id, move(title), move(description)), startDate(move(startDate)), dueDate(move(dueDate)) {}

    vector<Task> &getTasks() { return tasks; }
    const vector<Task> &getTasks() const { return tasks; }
    const string &getStartDate() const { return startDate; }
    const string &getDueDate() const { return dueDate; }
    void addTask(const Task &task) { tasks.push_back(task); }
    bool removeTask(int taskId)
    {
        auto oldSize = tasks.size();
        tasks.erase(remove_if(tasks.begin(), tasks.end(), [taskId](const Task &task) { return task.getId() == taskId; }), tasks.end());
        return tasks.size() != oldSize;
    }

    double calculateProgress() const
    {
        if (tasks.empty()) return 0.0;
        int done = count_if(tasks.begin(), tasks.end(), [](const Task &task) { return task.isDone(); });
        return done * 100.0 / tasks.size();
    }

    void displayInfo() const override
    {
        cout << "[" << id << "] " << title << " | " << startDate << " -> " << dueDate
             << " | tasks: " << tasks.size() << " | progress: " << fixed << setprecision(0)
             << calculateProgress() << "%\n";
        cout << "    " << description << "\n";
    }
};

class ProjectBoard {
    string name;
    vector<Project> projects;

public:
    ProjectBoard(string name = "Default Board") : name(move(name)) {}
    const string &getName() const { return name; }
    vector<Project> &getProjects() { return projects; }
    const vector<Project> &getProjects() const { return projects; }
    void addProject(const Project &project) { projects.push_back(project); }
    bool removeProject(int projectId)
    {
        auto oldSize = projects.size();
        projects.erase(remove_if(projects.begin(), projects.end(), [projectId](const Project &project) {
                           return project.getId() == projectId;
                       }),
                       projects.end());
        return projects.size() != oldSize;
    }

    void showProjects() const
    {
        cout << "\nBOARD: " << name << "\n";
        for (const auto &project : projects) project.displayInfo();
    }
};

class StorageManager {
public:
    static void saveToFile(const ProjectBoard &board, const string &fileName)
    {
        ofstream file(fileName);
        file << "BOARD|" << board.getName() << "\n";
        for (const auto &project : board.getProjects()) {
            file << "PROJECT|" << project.getId() << "|" << project.getTitle() << "|" << project.getDescription()
                 << "|" << project.getStartDate() << "|" << project.getDueDate() << "\n";
            for (const auto &task : project.getTasks()) {
                file << "TASK|" << task.getId() << "|" << task.getTitle() << "|" << task.getDescription() << "|"
                     << toString(task.getStatus()) << "|" << toString(task.getPriority()) << "|"
                     << toString(task.getStage()) << "|" << task.getDueDate() << "|"
                     << task.getAssignee().getName() << "|" << task.getAssignee().getEmail() << "\n";
                for (const auto &tag : task.getTags()) {
                    file << "TAG|" << tag.getName() << "\n";
                }
                for (const auto &item : task.getChecklist()) {
                    file << "CHECK|" << (item.isCompleted() ? "1" : "0") << "|" << item.getText() << "\n";
                }
                for (const auto &entry : task.getHistory()) {
                    file << "HISTORY|" << entry.getDate() << "|" << entry.getAction() << "\n";
                }
            }
        }
    }

    static bool loadFromFile(ProjectBoard &board, const string &fileName)
    {
        ifstream file(fileName);
        if (!file) return false;
        string line;
        Project *currentProject = nullptr;
        Task *currentTask = nullptr;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> parts;
            string part;
            while (getline(ss, part, '|')) parts.push_back(part);
            if (parts.empty()) continue;
            if (parts[0] == "BOARD" && parts.size() > 1) {
                board = ProjectBoard(parts[1]);
                currentProject = nullptr;
                currentTask = nullptr;
            } else if (parts[0] == "PROJECT" && parts.size() >= 6) {
                board.addProject(Project(stoi(parts[1]), parts[2], parts[3], parts[4], parts[5]));
                currentProject = &board.getProjects().back();
                currentTask = nullptr;
            } else if (parts[0] == "TASK" && parts.size() >= 9 && currentProject) {
                string email = parts.size() >= 10 ? parts[9] : "";
                currentProject->addTask(Task(stoi(parts[1]), parts[2], parts[3], priorityFromString(parts[5]),
                                             stageFromString(parts[6]), parts[7], Member(parts[8], email),
                                             statusFromString(parts[4]), false));
                currentTask = &currentProject->getTasks().back();
            } else if (parts[0] == "TAG" && parts.size() >= 2 && currentTask) {
                currentTask->loadTag(parts[1]);
            } else if (parts[0] == "CHECK" && parts.size() >= 3 && currentTask) {
                currentTask->loadChecklistItem(parts[2], parts[1] == "1");
            } else if (parts[0] == "HISTORY" && parts.size() >= 3 && currentTask) {
                currentTask->loadHistoryEntry(parts[2], parts[1]);
            }
        }
        return true;
    }
};

Project *findProject(ProjectBoard &board, int id)
{
    for (auto &project : board.getProjects()) {
        if (project.getId() == id) return &project;
    }
    return nullptr;
}

Task *findTask(Project &project, int id)
{
    for (auto &task : project.getTasks()) {
        if (task.getId() == id) return &task;
    }
    return nullptr;
}

void seedData(ProjectBoard &board, int &nextId)
{
    Project oop(nextId++, "OOP Checkpoint", "Terminal task and project manager", "2026-05-01", "2026-05-30");
    Task hierarchy(nextId++, "Implement class hierarchy", "BoardItem, Project, Task and helper classes", TaskPriority::High, TaskStage::Done, "2026-05-17", Member("Martin", "martin@example.com"));
    hierarchy.addTag("oop");
    hierarchy.addChecklistItem("Create abstract BoardItem");
    hierarchy.getChecklist()[0].markDone();
    oop.addTask(hierarchy);
    oop.addTask(Task(nextId++, "Add persistence", "Save and load project data from file", TaskPriority::Medium, TaskStage::InProgress, "2026-05-20", Member("Martin", "")));
    oop.addTask(Task(nextId++, "Write documentation", "Explain changed design decisions", TaskPriority::Low, TaskStage::ToDo, "2026-05-25", Member("Martin", "")));
    board.addProject(oop);
}

int main()
{
    int nextId = 1;
    ProjectBoard board("School Board");
    seedData(board, nextId);

    while (true) {
        cout << "\n====================================\n";
        cout << "PROJECT BOARD SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Show projects\n";
        cout << "2. Add project\n";
        cout << "3. Add task\n";
        cout << "4. Show tasks in project\n";
        cout << "5. Move task\n";
        cout << "6. Add checklist item\n";
        cout << "7. Save data\n";
        cout << "8. Load data\n";
        cout << "0. Exit\n";

        int choice = readInt("Choose option: ");
        if (choice == 0) break;

        if (choice == 1) {
            board.showProjects();
        } else if (choice == 2) {
            string title = readLine("Project title: ");
            string description = readLine("Description: ");
            string due = readLine("Due date (YYYY-MM-DD): ");
            board.addProject(Project(nextId++, title, description, todayDate(), due));
        } else if (choice == 3) {
            board.showProjects();
            Project *project = findProject(board, readInt("Project id: "));
            if (!project) {
                cout << "Project not found.\n";
                continue;
            }
            string title = readLine("Task title: ");
            string description = readLine("Description: ");
            int priority = readInt("Priority 1.Low 2.Medium 3.High 4.Urgent: ");
            string due = readLine("Due date (YYYY-MM-DD): ");
            string assignee = readLine("Assignee name: ");
            project->addTask(Task(nextId++, title, description, priorityFromInt(priority), TaskStage::Backlog, due, Member(assignee, "")));
        } else if (choice == 4) {
            board.showProjects();
            Project *project = findProject(board, readInt("Project id: "));
            if (project) {
                for (const auto &task : project->getTasks()) task.displayInfo();
            }
        } else if (choice == 5) {
            board.showProjects();
            Project *project = findProject(board, readInt("Project id: "));
            if (!project) continue;
            for (const auto &task : project->getTasks()) task.displayInfo();
            Task *task = findTask(*project, readInt("Task id: "));
            if (task) task->setStage(stageFromInt(readInt("Stage 1.Backlog 2.ToDo 3.InProgress 4.Review 5.Done: ")));
        } else if (choice == 6) {
            board.showProjects();
            Project *project = findProject(board, readInt("Project id: "));
            if (!project) continue;
            for (const auto &task : project->getTasks()) task.displayInfo();
            Task *task = findTask(*project, readInt("Task id: "));
            if (task) task->addChecklistItem(readLine("Checklist item: "));
        } else if (choice == 7) {
            StorageManager::saveToFile(board, "data.txt");
            cout << "Saved to data.txt\n";
        } else if (choice == 8) {
            cout << (StorageManager::loadFromFile(board, "data.txt") ? "Loaded data.txt\n" : "No data.txt found\n");
        }
    }

    return 0;
}
