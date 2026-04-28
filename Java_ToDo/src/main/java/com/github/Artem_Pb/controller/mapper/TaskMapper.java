package com.github.Artem_Pb.controller.mapper;

import com.github.Artem_Pb.controller.dto.SubTaskResponse;
import com.github.Artem_Pb.controller.dto.TaskResponse;
import com.github.Artem_Pb.domain.MegaTask;
import com.github.Artem_Pb.domain.Task;

import java.util.List;

public class TaskMapper {
    private TaskMapper() {
    }

    public static TaskResponse toResponse(Task task) {
        if (task instanceof MegaTask mega) {
            List<SubTaskResponse> subTasks = mega.getSubTasks().stream()
                    .map(sub -> new SubTaskResponse(sub.getId(), sub.getTitle(), sub.getStatus().getDisplayName()))
                    .toList();
            return new TaskResponse(mega.getId(), mega.getTitle(), mega.getStatus().getDisplayName(), "COMPOSITE", subTasks);
        }
        return new TaskResponse(task.getId(), task.getTitle(), task.getStatus().getDisplayName(), "SIMPLE", List.of());
    }
}
