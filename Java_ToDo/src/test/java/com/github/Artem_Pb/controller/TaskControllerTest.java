package com.github.Artem_Pb.controller;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.github.Artem_Pb.controller.dto.CreateTaskRequest;
import com.github.Artem_Pb.domain.SimpleTask;
import com.github.Artem_Pb.exception.TaskNotFoundException;
import com.github.Artem_Pb.service.TaskService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;

import java.util.List;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.when;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

// @WebMvcTest(TaskController.class) — загружает только TaskController + GlobalExceptionHandler.
// Нет JPA, нет базы. Быстрее @SpringBootTest в 5-10 раз.
@WebMvcTest(TaskController.class)
class TaskControllerTest {

    // MockMvc — HTTP клиент для тестов. Отправляет запросы прямо в контроллер без реального сервера.
    @Autowired
    private MockMvc mockMvc;

    // ObjectMapper — сериализует Java объекты в JSON для тела запроса.
    @Autowired
    private ObjectMapper objectMapper;

    // @MockBean — создаёт мок и регистрирует его как Spring бин.
    // Отличие от @Mock: Spring инжектит его в контроллер автоматически.
    @MockBean
    private TaskService taskService;

    @Test
    void getAll_emptyList_returns200WithEmptyArray() throws Exception {
        when(taskService.getAllTasks()).thenReturn(List.of());

        mockMvc.perform(get("/api/tasks"))
                .andExpect(status().isOk())
                .andExpect(content().json("[]"));
    }

    @Test
    void createTask_validRequest_returns201WithBody() throws Exception {
        SimpleTask saved = new SimpleTask("Buy milk");
        when(taskService.createTask("Buy milk")).thenReturn(saved);

        mockMvc.perform(post("/api/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(objectMapper.writeValueAsString(new CreateTaskRequest("Buy milk"))))
                // status().isCreated() — проверяет HTTP 201.
                .andExpect(status().isCreated())
                // jsonPath — XPath для JSON. $.title — поле title в корне ответа.
                .andExpect(jsonPath("$.title").value("Buy milk"))
                .andExpect(jsonPath("$.status").value("Not started"))
                .andExpect(jsonPath("$.type").value("SIMPLE"));
    }

    @Test
    void createTask_blankTitle_returns400() throws Exception {
        // Валидация @NotBlank срабатывает до вызова сервиса — Spring возвращает 400.
        mockMvc.perform(post("/api/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(objectMapper.writeValueAsString(new CreateTaskRequest(""))))
                .andExpect(status().isBadRequest());
    }

    @Test
    void getById_notFound_returns404() throws Exception {
        // Сервис бросает TaskNotFoundException → GlobalExceptionHandler → 404.
        when(taskService.getById(99L)).thenThrow(new TaskNotFoundException(99L));

        mockMvc.perform(get("/api/tasks/99"))
                .andExpect(status().isNotFound())
                // Проверяем поле errorCode в теле ответа.
                .andExpect(jsonPath("$.code").value("TASK_NOT_FOUND"));
    }

    @Test
    void getById_exists_returns200() throws Exception {
        SimpleTask task = new SimpleTask("Walk dog");
        when(taskService.getById(1L)).thenReturn(task);

        mockMvc.perform(get("/api/tasks/1"))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.title").value("Walk dog"));
    }
}
