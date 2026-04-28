package com.github.Artem_Pb.controller.dto;

import com.github.Artem_Pb.domain.Status;
import jakarta.validation.constraints.NotNull;

public record UpdateStatusRequest(@NotNull Status newStatus) {
}
