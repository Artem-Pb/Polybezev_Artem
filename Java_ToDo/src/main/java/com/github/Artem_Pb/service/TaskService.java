package com.github.Artem_Pb.service;

import com.github.Artem_Pb.domain.MegaTask;
import com.github.Artem_Pb.domain.SimpleTask;
import com.github.Artem_Pb.domain.Status;
import com.github.Artem_Pb.domain.Task;

import java.util.List;

public interface TaskService {
    SimpleTask createTask(String title);
    MegaTask createMegaTask(String title, List<String> subTaskTitle);

    List<Task> getAllTasks();
    Task getById(Long id);

    void updateStatus(Long taskId, Status status);
    void updateSubTaskStatus(Long megaTaskId, Long subTaskId, Status status);

    void updateTitle(Long taskId, String newTitle);

    void deleteTask(Long id);

    List<Task> search(String keyword);
}
