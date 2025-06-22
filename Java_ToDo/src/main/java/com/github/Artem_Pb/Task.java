package com.github.Artem_Pb;

/**
 * Базовый интерфейс для всех типов задач.
 */
public interface Task {
    String getDescription();
    Status getStatus();
    void setStatus(Status status);
    int getId();
}