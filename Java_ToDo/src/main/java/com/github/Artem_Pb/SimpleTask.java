package com.github.Artem_Pb;

import java.io.Serializable;
import java.util.Objects;

/**
 * Класс простой задачи. Реализует интерфейс Task и Serializable для сохранения состояния.
 */
public final class SimpleTask implements Task, Serializable {
    private static final long serialVersionUID = 1L;

    private final int id;
    private String description;
    private Status status;

    public SimpleTask(String description, Status status) {
        this.id = TaskIdGenerator.generateId();
        setDescription(description);
        setStatus(status);
    }

    public static SimpleTask createInteractive(InputHandler inputHandler) {
        Objects.requireNonNull(inputHandler);
        inputHandler.println("Введите описание задачи:");
        String description = inputHandler.readLine();
        return new SimpleTask(description, Status.NOT_STARTED);
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public String getDescription() {
        return String.format("%s [%s]", description, status.getDisplayName());
    }

    public void setDescription(String description) {
        this.description = Objects.requireNonNull(description).trim();
    }

    @Override
    public Status getStatus() {
        return status;
    }

    @Override
    public void setStatus(Status status) {
        this.status = Objects.requireNonNull(status);
    }

    /* 6 public void markCompleted() {
    //      this.status = Status.COMPLETED;
       }
    */
    @Override
    public String toString() {
        return String.format("SimpleTask[id=%d, description='%s', status=%s]",
                id, description, status.getDisplayName());
    }
}