import java.util.List;
import java.util.Map;

/**
 * Главный класс приложения для управления списком задач.
 */
public class Main {
    private static final InputHandler input = InputHandler.getInstance();
    private static FileManager fileManager = FileManager.getInstance();

    public static void main(String[] args) {
        ToDoList todo = initializeTodoList();
        boolean isRunning = true;

        while (isRunning) {
            clearConsole();
            Command.printMenu();
            try {
                Command cmd = getSelectedCommand();
                isRunning = processCommand(cmd, todo);
            } catch (IllegalArgumentException e) {
                input.println("Ошибка: " + e.getMessage());
            }
        }

        fileManager.save(todo);
        input.println(Command.BY.getCommand());
    }

    private static ToDoList initializeTodoList() {
        ToDoList todo = fileManager.load();
        if (todo == null) {
            input.println("Создан новый список задач");
            return new ToDoList(input);
        }
        return todo;
    }

    private static Command getSelectedCommand() {
        input.print("Выберите команду: ");
        return Command.getByNumber(input.readIntRange(1, Command.values().length - 3));
    }

    private static boolean processCommand(Command cmd, ToDoList todo) {
        switch (cmd) {
            case ADD_SIMPLE -> addSimpleTask(todo);
            case ADD_MEGA -> addMegaTask(todo);
            case SHOW_TODO -> showAllTasks(todo);
            case DEL_TASK -> deleteTask(todo);
            case UPDATE_TASK -> updateTask(todo);
            case DEL_TODO -> todo = clearTodoList(todo);
            case SHOW_COMPLETE -> showCompletedTasks(todo);
            case STATS -> todo.showStatistics();
            case SEARCH -> {
                input.print("Введите поисковый запрос: ");
                todo.searchTasks(input.readLine());
            }
            case START_TASK -> {
                updateStatus(todo, Status.IN_PROGRESS);
            }
            case COMPLETE_TASK -> updateStatus(todo, Status.COMPLETED);
            case RESET_TASK -> updateStatus(todo, Status.NOT_STARTED);
            case EXIT -> { return false; }
            default -> throw new IllegalArgumentException("Неизвестная команда");
        }
        return true;
    }

    private static void addSimpleTask(ToDoList todo) {
        input.println(Command.ADD_SIMPLE.getCommand());
        Task task = SimpleTask.createInteractive(input);
        todo.addTask(task);
        input.println("Добавлена задача №" + task.getId());
    }

    private static void addMegaTask(ToDoList todo) {
        input.println(Command.ADD_MEGA.getCommand());
        Task task = MegaTask.createInteractive(input);
        todo.addTask(task);
        input.println("Добавлена мегазадача №" + task.getId());
    }

    private static void showAllTasks(ToDoList todo) {
        input.println(Command.SHOW_TODO.getCommand());
        Map<Integer, Task> tasks = todo.getAllTasks();
        if (tasks.isEmpty()) {
            input.println("Список задач пуст");
            return;
        }
        tasks.forEach((id, task) -> input.println(id + ": " + task.getDescription()));
    }

    private static void deleteTask(ToDoList todo) {
        input.println(Command.DEL_TASK.getCommand());
        showAllTasks(todo);
        input.print("Введите ID задачи для удаления: ");
        int id = input.readInt();
        if (todo.removeTask(id)) {
            input.println("Задача удалена");
        } else {
            input.println("Задача не найдена");
        }
    }

    private static void updateTask(ToDoList todo) {
        input.println(Command.UPDATE_TASK.getCommand());
        showAllTasks(todo);
        input.print("Введите ID задачи для редактирования: ");
        todo.editTask(input.readInt());
    }

    private static void updateStatus(ToDoList todo, Status status) {
        input.println("Список задач:");
        todo.getAllTasks().forEach((id, task) ->
                input.println(id + ": " + task.getDescription())
        );

        input.print("Введите ID задачи: ");
        int taskId = input.readInt();

        if (todo.getTask(taskId) instanceof CompositeTask ct) {
            if (!ct.getSubTasks().isEmpty()) {
                input.println("Подзадачи:");
                ct.getSubTasks().forEach(sub ->
                        input.println(ct.getSubTasks().indexOf(sub) + ": " + sub.getDescription())
                );
                input.print("Введите номер подзадачи (или -1 для всей задачи): ");
                int subTaskId = input.readIntRange(-1, ct.getSubTasks().size()-1);
                todo.updateTaskStatus(taskId, subTaskId >= 0 ? subTaskId : null, status);
            } else {
                todo.updateTaskStatus(taskId, null, status);
            }
        } else {
            todo.updateTaskStatus(taskId, null, status);
        }
    }

    private static ToDoList clearTodoList(ToDoList todo) {
        input.println(Command.DEL_TODO.getCommand());
        input.print("Вы уверены? (да/нет): ");
        if (input.readLine().equalsIgnoreCase("да")) {
            todo = new ToDoList(input);
            input.println("Список задач очищен");
        }
        return todo;
    }

    private static void showCompletedTasks(ToDoList todo) {
        input.println(Command.SHOW_COMPLETE.getCommand());
        todo.getAllTasks().values().stream()
                .filter(task -> task.getStatus() == Status.COMPLETED)
                .forEach(task -> input.println(task.getDescription()));
    }

    private static void clearConsole() {
        input.print("\033[H\033[2J");
    }
}