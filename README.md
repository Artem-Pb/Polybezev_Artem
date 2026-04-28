# TodoList

CLI task manager implemented twice — in Java and in C — with the same feature set.

Team project (3 developers).

## Implementations

### Java — `Java_ToDo/`

| Class | Role |
|-------|------|
| `Task` | Interface for all task types |
| `SimpleTask` | Leaf task (Composite pattern) |
| `MegaTask` | Composite task containing subtasks |
| `TaskIdGenerator` | Singleton — unique IDs across sessions |
| `FileManager` | Serialization to disk (`Serializable`) |
| `ToDoList` | Main data structure |
| `InputHandler` | CLI input parsing |
| `Command` | Enum for CLI dispatch |

Build and run:

```
cd Java_ToDo
mvn package
java -jar target/ToDoList.jar
```

### C — `C_ToDo/`

| Module | Role |
|--------|------|
| `task.h/c` | Task struct, CRUD operations |
| `list.h/c` | Linked list of tasks |
| `serialization.h/c` | Binary serialization to disk |
| `tech_funct.h/c` | Utility functions |

Build and run:

```
cd C_ToDo
make
./build/todo_app
```

## Features

- Add, edit, delete tasks
- Set status (done / not done)
- Assign categories and priorities
- Persist data between sessions (serialization)
