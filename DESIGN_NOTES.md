# Design Notes

The design follows the Checkpoint 1 plan and keeps the class hierarchy from the UML diagram:

- `BoardItem` is an abstract base class.
- `Project` and `Task` inherit from `BoardItem`.
- `ProjectBoard` owns projects.
- `Project` owns tasks.
- `Task` owns tags, checklist items and activity history entries.
- `TaskController` handles searching, filtering, sorting and statistics.
- `StorageManager` handles saving and loading data.

The main design change is that the project is implemented in one source file instead of separate
`.h` and `.cpp` files. This was done to make the project easier to compile and review for the
checkpoint. The OOP structure is still preserved through separate classes, encapsulated fields,
inheritance, composition and enum types for task stage, priority and status.

Implemented functional areas in this checkpoint:

1. Project board and project management.
2. Task management.
3. Kanban stages and task movement.
4. Checklist items.
5. Priorities, deadlines and assignees as task fields.
6. Save and load through `StorageManager`.

Some planned features from Checkpoint 1 are intentionally left as future work. The classes
`Tag`, `ActivityLog` and the controller-style separation are represented in the code, but full
menu workflows for search, filtering, sorting, statistics and tag management were not completed
for this checkpoint.
