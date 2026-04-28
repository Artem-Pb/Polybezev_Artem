package com.github.Artem_Pb.controller;

import com.github.Artem_Pb.controller.dto.CreateMegaTaskRequest;
import com.github.Artem_Pb.controller.dto.CreateTaskRequest;
import com.github.Artem_Pb.controller.dto.TaskResponse;
import com.github.Artem_Pb.controller.dto.UpdateStatusRequest;
import com.github.Artem_Pb.controller.mapper.TaskMapper;
import com.github.Artem_Pb.domain.MegaTask;
import com.github.Artem_Pb.domain.SimpleTask;
import com.github.Artem_Pb.service.TaskService;
import jakarta.validation.Valid;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

import static com.github.Artem_Pb.controller.mapper.TaskMapper.toResponse;

@RestController
@RequestMapping("/api/tasks")
public class TaskController {
    private final TaskService taskService;

    public TaskController(TaskService taskService) {
        this.taskService = taskService;
    }

    @GetMapping
    public List<TaskResponse> getAll() {
        return taskService.getAllTasks().stream()
                .map(TaskMapper::toResponse)
                .toList();
    }
    @GetMapping("/{id}")
    public TaskResponse getById(@PathVariable Long id) {
        return toResponse(taskService.getById(id));
    }

    @GetMapping("/search")
    public List<TaskResponse> search(@RequestParam String keyword) {
        return taskService.search(keyword).stream()
                .map(TaskMapper::toResponse)
                .toList();
    }

    @PostMapping
    public ResponseEntity<TaskResponse> create(@RequestBody @Valid CreateTaskRequest request) {
        SimpleTask task = taskService.createTask(request.title());
        return ResponseEntity.status(201).body(TaskMapper.toResponse(task));
    }

    @PutMapping("/{id}/status")
    public ResponseEntity<Void> updateStatus(@PathVariable Long id, @RequestBody @Valid UpdateStatusRequest request) {
        taskService.updateStatus(id, request.newStatus());
        return ResponseEntity.noContent().build();
    }

    @PostMapping("/mega")
    public ResponseEntity<TaskResponse> createMega(
            @RequestBody @Valid CreateMegaTaskRequest request) {
        MegaTask task = taskService.createMegaTask(request.title(),
                request.subTaskTitles());
        return ResponseEntity.status(201).body(TaskMapper.toResponse(task));
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        taskService.deleteTask(id);
        return ResponseEntity.noContent().build();
    }
}
