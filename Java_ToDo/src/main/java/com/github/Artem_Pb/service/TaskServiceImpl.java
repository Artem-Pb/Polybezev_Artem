package com.github.Artem_Pb.service;

import com.github.Artem_Pb.domain.MegaTask;
import com.github.Artem_Pb.domain.SimpleTask;
import com.github.Artem_Pb.domain.Status;
import com.github.Artem_Pb.domain.Task;
import com.github.Artem_Pb.exception.InvalidTaskOperationException;
import com.github.Artem_Pb.exception.TaskNotFoundException;
import com.github.Artem_Pb.repository.MegaTaskRepository;
import com.github.Artem_Pb.repository.SimpleTaskRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;

@Service
@Transactional
public class TaskServiceImpl implements TaskService {
    private final SimpleTaskRepository simpleTaskRepository;
    private final MegaTaskRepository megaTaskRepository;

    public TaskServiceImpl(SimpleTaskRepository simpleTaskRepository,
                           MegaTaskRepository megaTaskRepository) {
        this.simpleTaskRepository = simpleTaskRepository;
        this.megaTaskRepository = megaTaskRepository;
    }

    @Override
    public SimpleTask createTask(String title) {
        if (title == null || title.isBlank())
            throw new InvalidTaskOperationException("Title cannot be blank");

        SimpleTask simpleTask = new SimpleTask(title);
        return simpleTaskRepository.save(simpleTask);
    }

    @Override
    public Task getById(Long id) {
        Optional<SimpleTask> simple = simpleTaskRepository.findById(id);
        if (simple.isPresent()) return simple.get();

        Optional<MegaTask> mega = megaTaskRepository.findById(id);
        if (mega.isPresent()) return mega.get();

        throw new TaskNotFoundException(id);
    }

    @Override
    public MegaTask createMegaTask(String title, List<String> subTaskTitle) {
        if (title == null || title.isBlank())
            throw new InvalidTaskOperationException("Title cannot be blank");

        MegaTask mega = new MegaTask(title);

        if (subTaskTitle == null || subTaskTitle.isEmpty()) {
            throw new InvalidTaskOperationException("MegaTask must have at least on subtask");
        }

        for (String subTitle : subTaskTitle) {

            if (subTitle != null && !subTitle.isBlank()) {
                SimpleTask sub = new SimpleTask(subTitle);
                mega.addSubTask(sub);
            }
        }

        return megaTaskRepository.save(mega);
    }

    @Override
    public List<Task> getAllTasks() {
        List<Task> allTasks = new ArrayList<>();

        allTasks.addAll(simpleTaskRepository.findAllTopLevel());
        allTasks.addAll(megaTaskRepository.findAll());
        allTasks.sort(Comparator.comparing(Task::getId));

        return allTasks;
    }

    @Override
    public void deleteTask(Long id) {
        Task task = getById(id);

        if (task instanceof SimpleTask)
            simpleTaskRepository.deleteById(id);
        else
            megaTaskRepository.deleteById(id);
    }

    @Override
    public void updateTitle(Long taskId, String newTitle) {
        if (newTitle == null || newTitle.isBlank())
            throw new InvalidTaskOperationException("Title cannot be blank");

        Task task = getById(taskId);
        task.setTitle(newTitle);
    }

    @Override
    public void updateStatus(Long taskId, Status status) {
        Task task = getById(taskId);
        task.setStatus(status);
    }

    @Override
    public void updateSubTaskStatus(Long megaTaskId, Long subTaskId, Status status) {
        Task task = getById(megaTaskId);

        if (!(task instanceof MegaTask mega))
            throw new InvalidTaskOperationException("Task is not a composite task");

        SimpleTask subTask = mega.getSubTasks().stream()
                .filter(t -> t.getId().equals(subTaskId))
                .findFirst()
                .orElseThrow(() -> new TaskNotFoundException(subTaskId));

        subTask.setStatus(status);

        updateParentStatus(mega);
    }

    @Override
    public List<Task> search(String keyword) {
        if (keyword == null || keyword.isBlank())
            throw new InvalidTaskOperationException("Search keyword cannot be blank");

        List<Task> result = new ArrayList<>();
        result.addAll(simpleTaskRepository.findTopLevelByTitleContaining(keyword));
        result.addAll(megaTaskRepository.findByTitleOrSubTaskTitleContaining(keyword));
        return result;
    }

    private void updateParentStatus(MegaTask mega) {
        List<SimpleTask> subs = mega.getSubTasks();
        long completed = subs.stream()
                .filter(t -> t.getStatus() == Status.COMPLETED)
                .count();

        if (completed == subs.size()) mega.setStatus(Status.COMPLETED);
        else if (completed > 0) mega.setStatus(Status.IN_PROGRESS);
        else mega.setStatus(Status.NOT_STARTED);
    }
}