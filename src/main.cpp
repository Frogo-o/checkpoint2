#include "../include/ProjectBoard.h"
#include "../include/StorageManager.h"
#include "../include/TaskController.h"
#include "../include/TaskTypes.h"
#include "../include/Utils.h"

#include <iostream>
#include <vector>

using namespace std;

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

int calculateNextId(const vector<ProjectBoard> &boards)
{
    int maxId = 0;
    for (const auto &board : boards) {
        for (const auto &project : board.getProjects()) {
            if (project.getId() > maxId) maxId = project.getId();
            for (const auto &task : project.getTasks()) {
                if (task.getId() > maxId) maxId = task.getId();
            }
        }
    }
    return maxId + 1;
}

ProjectBoard *activeBoard(vector<ProjectBoard> &boards, int activeIndex)
{
    if (boards.empty() || activeIndex < 0 || activeIndex >= static_cast<int>(boards.size())) return nullptr;
    return &boards[activeIndex];
}

void showBoards(const vector<ProjectBoard> &boards, int activeIndex)
{
    cout << "\nPROJECT BOARDS\n";
    for (int i = 0; i < static_cast<int>(boards.size()); ++i) {
        cout << (i == activeIndex ? "* " : "  ") << (i + 1) << ". " << boards[i].getName()
             << " | projects: " << boards[i].getProjects().size() << "\n";
    }
}

void showTasks(Project &project)
{
    for (const auto &task : project.getTasks()) task.displayInfo();
}

void printTasks(const vector<Task *> &tasks)
{
    if (tasks.empty()) {
        cout << "No matching tasks.\n";
        return;
    }
    for (const auto *task : tasks) task->displayInfo();
}

void seedData(vector<ProjectBoard> &boards, int &nextId)
{
    ProjectBoard school("School Board");
    Project oop(nextId++, "OOP Checkpoint", "Terminal task and project manager", "2026-05-01", "2026-06-15");
    Task hierarchy(nextId++, "Implement class hierarchy", "BoardItem, Project, Task and helper classes",
                   TaskPriority::High, TaskStage::Done, "2026-05-17", Member("Martin", "martin@example.com"));
    hierarchy.addTag("oop");
    hierarchy.addChecklistItem("Create abstract BoardItem");
    hierarchy.getChecklist()[0].markDone();
    oop.addTask(hierarchy);
    oop.addTask(Task(nextId++, "Add persistence", "Save and load project data from file",
                     TaskPriority::Medium, TaskStage::InProgress, "2026-06-10", Member("Martin", "")));
    oop.addTask(Task(nextId++, "Write documentation", "Explain changed design decisions",
                     TaskPriority::Low, TaskStage::ToDo, "2026-06-12", Member("Martin", "")));
    school.addProject(oop);

    ProjectBoard personal("Personal Board");
    Project chores(nextId++, "Personal Tasks", "Example personal project", "2026-05-31", "2026-06-30");
    chores.addTask(Task(nextId++, "Organize files", "Clean project folders",
                        TaskPriority::Low, TaskStage::Backlog, "2026-06-20", Member("Martin", "")));
    personal.addProject(chores);

    boards.push_back(school);
    boards.push_back(personal);
}

void editProject(Project &project)
{
    string title = readLine("New title: ");
    string description = readLine("New description: ");
    string start = readLine("New start date (YYYY-MM-DD): ");
    string due = readLine("New due date (YYYY-MM-DD): ");
    if (!title.empty()) project.setTitle(title);
    if (!description.empty()) project.setDescription(description);
    if (!start.empty()) project.setStartDate(start);
    if (!due.empty()) project.setDueDate(due);
}

void editTask(Task &task)
{
    string title = readLine("New title: ");
    string description = readLine("New description: ");
    int priority = readInt("Priority 1.Low 2.Medium 3.High 4.Urgent: ");
    int stage = readInt("Stage 1.Backlog 2.ToDo 3.InProgress 4.Review 5.Done: ");
    string due = readLine("New due date (YYYY-MM-DD): ");
    string assignee = readLine("New assignee name: ");
    if (!title.empty()) task.setTitle(title);
    if (!description.empty()) task.setDescription(description);
    task.setPriority(priorityFromInt(priority));
    task.setStage(stageFromInt(stage));
    if (!due.empty()) task.setDueDate(due);
    if (!assignee.empty()) task.setAssignee(Member(assignee, ""));
}

Project *promptProject(ProjectBoard &board)
{
    board.showProjects();
    Project *project = findProject(board, readInt("Project id: "));
    if (!project) cout << "Project not found.\n";
    return project;
}

Task *promptTask(Project &project)
{
    showTasks(project);
    Task *task = findTask(project, readInt("Task id: "));
    if (!task) cout << "Task not found.\n";
    return task;
}

void filterTasks(ProjectBoard &board)
{
    cout << "1. By stage\n";
    cout << "2. By priority\n";
    cout << "3. By tag\n";
    cout << "4. By assignee\n";
    cout << "5. By due date\n";
    int choice = readInt("Filter option: ");
    if (choice == 1) {
        int stage = readInt("Stage 1.Backlog 2.ToDo 3.InProgress 4.Review 5.Done: ");
        printTasks(TaskController::filterByStage(board, stageFromInt(stage)));
    } else if (choice == 2) {
        int priority = readInt("Priority 1.Low 2.Medium 3.High 4.Urgent: ");
        printTasks(TaskController::filterByPriority(board, priorityFromInt(priority)));
    } else if (choice == 3) {
        printTasks(TaskController::filterByTag(board, readLine("Tag: ")));
    } else if (choice == 4) {
        printTasks(TaskController::filterByAssignee(board, readLine("Assignee: ")));
    } else if (choice == 5) {
        printTasks(TaskController::filterByDueDate(board, readLine("Due date (YYYY-MM-DD): ")));
    }
}

void sortTasks(ProjectBoard &board)
{
    Project *project = promptProject(board);
    if (!project) return;
    cout << "1. By priority\n";
    cout << "2. By due date\n";
    cout << "3. By title\n";
    cout << "4. By stage\n";
    int choice = readInt("Sort option: ");
    if (choice == 1) TaskController::sortTasksByPriority(project->getTasks());
    else if (choice == 2) TaskController::sortTasksByDueDate(project->getTasks());
    else if (choice == 3) TaskController::sortTasksByTitle(project->getTasks());
    else if (choice == 4) TaskController::sortTasksByStage(project->getTasks());
    showTasks(*project);
}

void showReports(ProjectBoard &board)
{
    board.showProjects();
    TaskController::showStatistics(board);
}

int main()
{
    int nextId = 1;
    vector<ProjectBoard> boards;
    seedData(boards, nextId);
    int activeIndex = 0;

    while (true) {
        ProjectBoard *board = activeBoard(boards, activeIndex);
        cout << "\n====================================\n";
        cout << "PROJECT BOARD SYSTEM";
        if (board) cout << " | ACTIVE: " << board->getName();
        cout << "\n====================================\n";
        cout << "1. Show boards\n";
        cout << "2. Create board\n";
        cout << "3. Select board\n";
        cout << "4. Show projects\n";
        cout << "5. Add project\n";
        cout << "6. Edit project\n";
        cout << "7. Delete project\n";
        cout << "8. Add task\n";
        cout << "9. Edit task\n";
        cout << "10. Delete task\n";
        cout << "11. Show tasks in project\n";
        cout << "12. Move task\n";
        cout << "13. Add checklist item\n";
        cout << "14. Mark checklist item done\n";
        cout << "15. Add tag to task\n";
        cout << "16. Search tasks\n";
        cout << "17. Filter tasks\n";
        cout << "18. Sort project tasks\n";
        cout << "19. View task history\n";
        cout << "20. Project reports\n";
        cout << "21. Save data\n";
        cout << "22. Load data\n";
        cout << "0. Exit\n";

        int choice = readInt("Choose option: ");
        if (choice == 0) break;

        if (choice == 1) {
            showBoards(boards, activeIndex);
        } else if (choice == 2) {
            boards.emplace_back(readLine("Board name: "));
            activeIndex = static_cast<int>(boards.size()) - 1;
        } else if (choice == 3) {
            showBoards(boards, activeIndex);
            int index = readInt("Board number: ") - 1;
            if (index >= 0 && index < static_cast<int>(boards.size())) activeIndex = index;
            else cout << "Invalid board.\n";
        } else if (!board) {
            cout << "No active board.\n";
        } else if (choice == 4) {
            board->showProjects();
        } else if (choice == 5) {
            string title = readLine("Project title: ");
            string description = readLine("Description: ");
            string due = readLine("Due date (YYYY-MM-DD): ");
            board->addProject(Project(nextId++, title, description, todayDate(), due));
        } else if (choice == 6) {
            Project *project = promptProject(*board);
            if (project) editProject(*project);
        } else if (choice == 7) {
            board->showProjects();
            cout << (board->removeProject(readInt("Project id: ")) ? "Project deleted.\n" : "Project not found.\n");
        } else if (choice == 8) {
            Project *project = promptProject(*board);
            if (!project) continue;
            string title = readLine("Task title: ");
            string description = readLine("Description: ");
            int priority = readInt("Priority 1.Low 2.Medium 3.High 4.Urgent: ");
            string due = readLine("Due date (YYYY-MM-DD): ");
            string assignee = readLine("Assignee name: ");
            project->addTask(Task(nextId++, title, description, priorityFromInt(priority),
                                  TaskStage::Backlog, due, Member(assignee, "")));
        } else if (choice == 9) {
            Project *project = promptProject(*board);
            if (!project) continue;
            Task *task = promptTask(*project);
            if (task) editTask(*task);
        } else if (choice == 10) {
            Project *project = promptProject(*board);
            if (!project) continue;
            showTasks(*project);
            cout << (project->removeTask(readInt("Task id: ")) ? "Task deleted.\n" : "Task not found.\n");
        } else if (choice == 11) {
            Project *project = promptProject(*board);
            if (project) showTasks(*project);
        } else if (choice == 12) {
            Project *project = promptProject(*board);
            if (!project) continue;
            Task *task = promptTask(*project);
            if (task) task->setStage(stageFromInt(readInt("Stage 1.Backlog 2.ToDo 3.InProgress 4.Review 5.Done: ")));
        } else if (choice == 13) {
            Project *project = promptProject(*board);
            if (!project) continue;
            Task *task = promptTask(*project);
            if (task) task->addChecklistItem(readLine("Checklist item: "));
        } else if (choice == 14) {
            Project *project = promptProject(*board);
            if (!project) continue;
            Task *task = promptTask(*project);
            if (!task) continue;
            auto &items = task->getChecklist();
            for (int i = 0; i < static_cast<int>(items.size()); ++i) {
                cout << (i + 1) << ". ";
                items[i].displayInfo();
            }
            int index = readInt("Checklist item number: ") - 1;
            if (index >= 0 && index < static_cast<int>(items.size())) items[index].markDone();
            else cout << "Invalid checklist item.\n";
        } else if (choice == 15) {
            Project *project = promptProject(*board);
            if (!project) continue;
            Task *task = promptTask(*project);
            if (task) task->addTag(readLine("Tag name: "));
        } else if (choice == 16) {
            printTasks(TaskController::searchTasks(*board, readLine("Keyword: ")));
        } else if (choice == 17) {
            filterTasks(*board);
        } else if (choice == 18) {
            sortTasks(*board);
        } else if (choice == 19) {
            Project *project = promptProject(*board);
            if (!project) continue;
            Task *task = promptTask(*project);
            if (task) {
                cout << "History for " << task->getTitle() << ":\n";
                for (const auto &entry : task->getHistory()) entry.displayInfo();
            }
        } else if (choice == 20) {
            showReports(*board);
        } else if (choice == 21) {
            StorageManager::saveToFile(boards, "data.txt");
            cout << "Saved to data.txt\n";
        } else if (choice == 22) {
            if (StorageManager::loadFromFile(boards, "data.txt")) {
                activeIndex = boards.empty() ? -1 : 0;
                nextId = calculateNextId(boards);
                cout << "Loaded data.txt\n";
            } else {
                cout << "No data.txt found\n";
            }
        }
    }

    return 0;
}
