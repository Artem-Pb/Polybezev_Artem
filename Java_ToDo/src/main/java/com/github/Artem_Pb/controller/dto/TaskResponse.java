package com.github.Artem_Pb.controller.dto;

import java.util.List;

public record TaskResponse(Long id, String title, String status, String type, List<SubTaskResponse> subTask) {
}
