package com.github.Artem_Pb.exception;

import org.springframework.http.HttpStatus;

public final class TaskNotFoundException extends AppException {

    public TaskNotFoundException(Long id) {
        super("Task not found: " + id, "TASK_NOT_FOUND", HttpStatus.NOT_FOUND);
    }
}
