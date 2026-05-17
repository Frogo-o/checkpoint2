# Test Plan

Manual checks used for the checkpoint:

1. Build the program with `g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o task_manager.exe`.
2. Start the executable and confirm that the menu opens.
3. Show projects and tasks from the seeded board.
4. Add a checklist item to a task.
5. Move a task between kanban stages.
6. Save to `data.txt`.
7. Load from `data.txt` and confirm projects and tasks are restored.
