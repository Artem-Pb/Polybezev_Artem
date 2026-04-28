package com.github.Artem_Pb.controller.dto;

import jakarta.validation.constraints.NotBlank;

public record CreateTaskRequest(@NotBlank(message = "Давай не выебывайся! Поле не может быть пустым, Вася!")
                                String title) {
}
