# Design Notes

The design follows the Checkpoint 1 plan and keeps the class hierarchy from the UML diagram:

- `BoardItem` is an abstract base class.
- `Project` and `Task` inherit from `BoardItem`.
- `ProjectBoard` owns projects.
- `Project` owns tasks.
- `Task` owns tags, checklist items and activity history entries.
- `TaskController` handles searching, filtering, sorting and statistics.
- `StorageManager` handles saving and loading data.

The checkpoint version was initially implemented in one source file. For the final version this
was changed to a normal multi-file structure with separate `.h` and `.cpp` files for the classes.
This better matches the final requirement and makes the class responsibilities clearer.

Implemented functional areas in the final version:

1. Multiple project boards and project management.
2. Full task management.
3. Kanban stages and task movement.
4. Checklist items.
5. Priorities, deadlines and assignees as task fields.
6. Tags.
7. Search, filtering and sorting through `TaskController`.
8. Activity history.
9. Statistics and project progress.
10. Save and load for all boards through `StorageManager`.

The final version follows the original Checkpoint 1 plan as a terminal application. The main
design change is structural: the first checkpoint implementation started in a single source file,
while the final version uses separate files for the classes.
