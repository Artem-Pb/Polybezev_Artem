package com.github.Artem_Pb;

import java.io.Serial;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Objects;

/**
 * Составная задача, содержащая подзадачи.
 */
public final class MegaTask implements CompositeTask, Serializable {
    @Serial
    private static final long serialVersionUID = 1L;

    private final int id;
    private String title;
    private Status status;
    private final List<Task> subTasks;
    private transient InputHandler inputHandler;

    public MegaTask(String title, Status status, List<Task> initialSubTasks) {
        this.id = TaskIdGenerator.generateId();
        setTitle(title);
        this.status = Objects.requireNonNull(status);
        this.subTasks = new ArrayList<>(Objects.requireNonNull(initialSubTasks));
    }

    public static MegaTask createInteractive(InputHandler inputHandler) {
        Objects.requireNonNull(inputHandler);

        inputHandler.println("Введите заголовок MegaTask:");
        String title = inputHandler.readLine();

        inputHandler.println("Сколько будет подзадач?");
        int count = inputHandler.readIntRange(1, 100);

        List<Task> subTasks = new ArrayList<>();
        for (int i = 0; i < count; i++) {
            inputHandler.println("Введите описание подзадачи " + (i+1) + ":");
            subTasks.add(new SimpleTask(inputHandler.readLine(), Status.NOT_STARTED));
        }

        return new MegaTask(title, Status.NOT_STARTED, subTasks);
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public String getTitle() {
        return title;
    }

    @Override
    public void setTitle(String title) {
        this.title = Objects.requireNonNull(title).trim();
    }

    @Override
    public String getDescription() {
        StringBuilder sb = new StringBuilder(title)
                .append(" [").append(status).append("]\n");
        for (Task task : subTasks) {
            sb.append("— ").append(task.getDescription()).append("\n");
        }
        return sb.toString();
    }

    @Override
    public Status getStatus() {
        return status;
    }

    @Override
    public void setStatus(Status status) {
        this.status = Objects.requireNonNull(status);
    }

    @Override
    public List<Task> getSubTasks() {
        return Collections.unmodifiableList(subTasks);
    }

    @Override
    public void addSubTask(Task task) {
        subTasks.add(Objects.requireNonNull(task));
    }

    @Override
    public void removeSubTask(int index) {
        if (index < 0 || index >= subTasks.size()) {
            throw new IllegalArgumentException("Неверный индекс подзадачи");
        }
        subTasks.remove(index);
    }

    @Override
    public String toString() {
        return String.format("MegaTask[id=%d, title='%s', status=%s, subTasks=%d]",
                id, title, status.getDisplayName(), subTasks.size());
    }

    @Serial
    private Object readResolve() {
        this.inputHandler = InputHandler.getInstance();
        return this;
    }
}