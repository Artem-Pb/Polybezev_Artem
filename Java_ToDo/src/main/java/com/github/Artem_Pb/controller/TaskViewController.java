package com.github.Artem_Pb.controller;

import com.github.Artem_Pb.controller.dto.CreateTaskRequest;
import com.github.Artem_Pb.controller.dto.TaskResponse;
import com.github.Artem_Pb.controller.mapper.TaskMapper;
import com.github.Artem_Pb.domain.Status;
import com.github.Artem_Pb.domain.Task;
import com.github.Artem_Pb.service.TaskService;
import jakarta.validation.Valid;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.validation.BindingResult;

import java.util.List;

@Controller
@RequestMapping("/tasks")
public class TaskViewController {

    private final TaskService taskService;

    public TaskViewController(TaskService taskService) {
        this.taskService = taskService;
    }

    @GetMapping
    public String listTasks(@RequestParam(required = false) String q, Model
            model) {
        List<Task> tasks = (q != null && !q.isBlank())
                ? taskService.search(q)
                : taskService.getAllTasks();

        model.addAttribute("tasks",
                tasks.stream().map(TaskMapper::toResponse).toList());
        model.addAttribute("q", q);
        return "tasks/list";
    }

    @GetMapping("/new")
    public String newTaskForm(Model model) {
        model.addAttribute("task", new CreateTaskRequest(""));
        return "tasks/form";
    }

    @PostMapping
    public String createTask(@ModelAttribute("task") @Valid CreateTaskRequest request, BindingResult result, Model model) {
        if (result.hasErrors())
            return "tasks/form";

        taskService.createTask(request.title());
        return "redirect:/tasks";
    }

    @PostMapping("/{id}/status")
    public String updateStatus(@PathVariable Long id, @RequestParam Status status) {
        taskService.updateStatus(id, status);
        return "redirect:/tasks";
    }

    @PostMapping("/{id}/delete")
    public String deleteTask(@PathVariable Long id) {
        taskService.deleteTask(id);
        return "redirect:/tasks";
    }

    @PostMapping("/{id}/subtasks/{subId}/status")
    public String updateSubTaskStatus(@PathVariable Long id, @PathVariable Long subId, @RequestParam Status status) {
        taskService.updateSubTaskStatus(id, subId, status);
        return "redirect:/tasks";
    }

    @GetMapping("/mega/new")
    public String newMegaTaskForm() {
        return "tasks/mega_form";
    }

    @PostMapping("/mega")
    public String createMegaTask(@RequestParam String title, @RequestParam List<String> subTaskTitles) {
        taskService.createMegaTask(title, subTaskTitles);
        return "redirect:/tasks";
    }

    @GetMapping("/{id}/edit")
    public String editTaskForm(@PathVariable Long id, Model model) {
        Task task = taskService.getById(id);
        model.addAttribute("task", new CreateTaskRequest(task.getTitle()));
        model.addAttribute("taskId", id);
        return "tasks/edit";
    }

    @PostMapping("/{id}/edit")
    public String updateTitle(@PathVariable Long id,
                              @ModelAttribute("task") @Valid
                              CreateTaskRequest request,
                              BindingResult result,
                              Model model) {
        if (result.hasErrors()) {
            model.addAttribute("taskId", id);
            return "tasks/edit";
        }
        taskService.updateTitle(id, request.title());
        return "redirect:/tasks";
    }

    @GetMapping("/{megaId}/subtasks/{subId}/edit")
    public String editSubTaskForm(@PathVariable Long megaId,
                                  @PathVariable Long subId,
                                  Model model) {
        Task sub = taskService.getById(subId);
        model.addAttribute("task", new CreateTaskRequest(sub.getTitle()));
        model.addAttribute("megaId", megaId);
        model.addAttribute("subId", subId);
        return "tasks/edit";
    }

    @PostMapping("/{megaId}/subtasks/{subId}/edit")
    public String updateSubTaskTitle(@PathVariable Long megaId,
                                     @PathVariable Long subId,
                                     @ModelAttribute("task") @Valid
                                     CreateTaskRequest request,
                                     BindingResult result,
                                     Model model) {
        if (result.hasErrors()) {
            model.addAttribute("megaId", megaId);
            model.addAttribute("subId", subId);
            return "tasks/edit";
        }
        taskService.updateTitle(subId, request.title());
        return "redirect:/tasks";
    }
}
