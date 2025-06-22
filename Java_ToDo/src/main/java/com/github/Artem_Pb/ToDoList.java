package com.github.Artem_Pb;

import java.io.Serial;
import java.io.Serializable;
import java.util.*;

public class ToDoList implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;

    private final Map<Integer, Task> tasks;
    private transient InputHandler inputHandler;

    public ToDoList(InputHandler inputHandler) {
        this.tasks = new LinkedHashMap<>();
        this.inputHandler = Objects.requireNonNull(inputHandler);
    }

    public void addTask(Task task) {
        tasks.put(task.getId(), Objects.requireNonNull(task));
    }

    public boolean removeTask(int id) {
        return tasks.remove(id) != null;
    }

    public Task getTask(int id) {
        return tasks.get(id);
    }

    public void editTask(int id) {
        Task task = tasks.get(id);
        if (task == null) {
            inputHandler.println("Задача не найдена");
            return;
        }

        if (task instanceof CompositeTask compositeTask) {
            editCompositeTask(compositeTask);
        } else {
            editSimpleTask((SimpleTask) task);
        }
    }

    private void editSimpleTask(SimpleTask task) {
        inputHandler.println("Текущее описание: " + task.getDescription());
        inputHandler.print("Новое описание: ");
        task.setDescription(inputHandler.readLine());
    }

    private void editCompositeTask(CompositeTask task) {
        while (true) {
            inputHandler.println("\nРедактирование задачи: " + task.getTitle());
            inputHandler.println("1. Изменить заголовок");
            inputHandler.println("2. Редактировать подзадачу");
            inputHandler.println("3. Удалить подзадачу");
            inputHandler.println("4. Добавить подзадачу");
            inputHandler.println("5. Назад");

            switch (inputHandler.readIntRange(1, 5)) {
                case 1 -> {
                    inputHandler.print("Новый заголовок: ");
                    task.setTitle(inputHandler.readLine());
                }
                case 2 -> editSubTaskDescription(task);
                case 3 -> removeSubTaskInteractive(task);
                case 4 -> addSubTaskInteractive(task);
                case 5 -> { return; }
            }
        }
    }

    public void updateTaskStatus(int taskId, Integer subTaskId, Status newStatus) {
        Task task = tasks.get(taskId);
        if (task == null) {
            inputHandler.println("Задача не найдена");
            return;
        }

        if (task instanceof SimpleTask) {
            task.setStatus(newStatus);
            inputHandler.printf("Задача №%d переведена в статус '%s'%n",
                    taskId, newStatus.getDisplayName());
        } else if (task instanceof CompositeTask compositeTask) {
            if (subTaskId != null) {
                Task subTask = compositeTask.getSubTasks().get(subTaskId);
                subTask.setStatus(newStatus);
                inputHandler.printf("✅ Подзадача №%d переведена в статус '%s'%n",
                        taskId, newStatus.getDisplayName());

                updateParentTaskStatus(compositeTask);
            } else {
                compositeTask.setStatus(newStatus);
                inputHandler.printf("Составная задача №%d переведена в статус '%s'%n",
                        taskId, newStatus.getDisplayName());
            }
        }
    }

    private void updateParentTaskStatus(CompositeTask task) {
        long completedCount = task.getSubTasks().stream()
                .filter(t -> t.getStatus() == Status.COMPLETED)
                .count();

        if (completedCount == task.getSubTasks().size()) {
            task.setStatus(Status.COMPLETED);
        } else if (completedCount > 0) {
            task.setStatus(Status.IN_PROGRESS);
        } else {
            task.setStatus(Status.NOT_STARTED);
        }
    }

    public void setTaskInProgress(int taskId, Integer subTaskId) {
        Task task = tasks.get(taskId);
        if (task == null) {
            inputHandler.println("Задача не найдена");
            return;
        }

        if (task instanceof SimpleTask) {
            task.setStatus(Status.IN_PROGRESS);
            inputHandler.println("Задача #" + taskId + " переведена в статус 'В процессе'");
        }
        else if (task instanceof CompositeTask compositeTask) {
            if (subTaskId != null) {
                Task subTask = compositeTask.getSubTasks().get(subTaskId);
                subTask.setStatus(Status.IN_PROGRESS);
                inputHandler.println("Подзадача #" + subTaskId + " переведена в статус 'В процессе'");

                // Автоматически переводим родительскую задачу
                if (compositeTask.getStatus() != Status.IN_PROGRESS) {
                    compositeTask.setStatus(Status.IN_PROGRESS);
                }
            } else {
                compositeTask.setStatus(Status.IN_PROGRESS);
                inputHandler.println("Составная задача #" + taskId + " переведена в статус 'В процессе'");
            }
        }
    }

//    private void updateSubTaskStatus(CompositeTask task, Integer subTaskId) {
//        try {
//            Task subTask = task.getSubTasks().get(subTaskId);
//            subTask.setStatus(Status.COMPLETED);
//            inputHandler.println("Подзадача №" + subTaskId + " выполнена!");
//
//            if (task.getSubTasks().stream().allMatch(t -> t.getStatus() == Status.COMPLETED)) {
//                task.setStatus(Status.COMPLETED);
//                inputHandler.println("Все подзадачи выполнены!");
//            }
//        } catch (IndexOutOfBoundsException e) {
//            inputHandler.println("Неверный номер подзадачи!");
//        }
//    }

    public void showStatistics() {
        int total = tasks.size();
        long completed = tasks.values().stream()
                .filter(t -> t.getStatus() == Status.COMPLETED).count();
        long inProgress = tasks.values().stream()
                .filter(t -> t.getStatus() == Status.IN_PROGRESS).count();

        inputHandler.println("\nСтатистика:");
        inputHandler.println("Всего задач: " + total);
        inputHandler.println("Выполнено: " + completed + " (" + (total > 0 ? completed*100/total : 0) + "%)");
        inputHandler.println("В процессе: " + inProgress);

        // Статистика по типам задач
        long megaTasks = tasks.values().stream()
                .filter(t -> t instanceof CompositeTask)
                .count();
        inputHandler.println("Составных задач: " + megaTasks);
    }

    public void searchTasks(String keyword) {
        inputHandler.println("\nРезультаты поиска по '" + keyword + "':");

        tasks.values().stream()
                .filter(task -> matchesSearch(task, keyword))
                .forEach(task -> inputHandler.println(
                        task.getId() + ": " +
                                (task instanceof CompositeTask ?
                                        ((CompositeTask)task).getTitle() :
                                        task.getDescription())
                ));
    }

    private boolean matchesSearch(Task task, String keyword) {
        String searchPattern = keyword.toLowerCase();

        if (task instanceof CompositeTask ct) {
            return ct.getTitle().toLowerCase().contains(searchPattern) ||
                    ct.getSubTasks().stream()
                            .anyMatch(sub -> sub.getDescription().toLowerCase().contains(searchPattern));
        }
        return task.getDescription().toLowerCase().contains(searchPattern);
    }

    private void editSubTaskDescription(CompositeTask task) {
        List<Task> subTasks = task.getSubTasks();
        printSubTasks(subTasks);

        inputHandler.print("Выберите подзадачу: ");
        int index = inputHandler.readIntRange(0, subTasks.size() - 1);

        inputHandler.print("Новое описание: ");
        String newDesc = inputHandler.readLine();

        Task subTask = subTasks.get(index);
        if (subTask instanceof SimpleTask simpleTask) {
            simpleTask.setDescription(newDesc);
        }
    }

    private void addSubTaskInteractive(CompositeTask task) {
        inputHandler.print("Описание новой подзадачи: ");
        task.addSubTask(new SimpleTask(inputHandler.readLine(), Status.NOT_STARTED));
    }

    private void removeSubTaskInteractive(CompositeTask task) {
        List<Task> subTasks = task.getSubTasks();
        printSubTasks(subTasks);
        inputHandler.print("Выберите подзадачу для удаления: ");
        task.removeSubTask(inputHandler.readIntRange(0, subTasks.size() - 1));
    }

    private void printSubTasks(List<Task> subTasks) {
        for (int i = 0; i < subTasks.size(); i++) {
            inputHandler.println(i + ". " + subTasks.get(i).getDescription());
        }
    }

    public Map<Integer, Task> getAllTasks() {
        return Collections.unmodifiableMap(tasks);
    }

    @Serial
    private Object readResolve() {
        this.inputHandler = InputHandler.getInstance();
        return this;
    }
}