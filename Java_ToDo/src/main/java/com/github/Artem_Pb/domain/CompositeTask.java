package com.github.Artem_Pb.domain;

import java.util.List;

public interface CompositeTask extends Task {
    List<SimpleTask> getSubTasks();
    void addSubTask(SimpleTask task);
default boolean hasSubTasks() {
        return !getSubTasks().isEmpty();
    }
}
