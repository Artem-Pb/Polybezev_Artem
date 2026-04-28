package com.github.Artem_Pb.controller.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotEmpty;

import java.util.List;

public record CreateMegaTaskRequest(@NotBlank String title, @NotEmpty List<String> subTaskTitles) {
}
