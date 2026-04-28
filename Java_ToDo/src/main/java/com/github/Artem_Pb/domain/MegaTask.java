package com.github.Artem_Pb.domain;

import jakarta.persistence.*;

import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "mega_tasks")
public class MegaTask implements CompositeTask {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "task_seq")
    @SequenceGenerator(name = "task_seq", sequenceName = "task_sequence", allocationSize = 1)
    private Long id;

    @Column(nullable = false)
    private String title;

    @Enumerated(EnumType.STRING)
    private Status status;

    @OneToMany(cascade = CascadeType.ALL, orphanRemoval = true, fetch = FetchType.EAGER)
    @JoinColumn(name = "mega_task_id")
    private List<SimpleTask> subTasks;

    public MegaTask(String title) {
        this.title = title;
        this.status = Status.NOT_STARTED;
        this.subTasks = new ArrayList<>();
    }

    protected MegaTask() {

    }

    @Override
    public Long getId() {
        return this.id;
    }

    @Override
    public Status getStatus() {
        return this.status;
    }

    @Override
    public String getTitle() {
        return this.title;
    }

    @Override
    public List<SimpleTask> getSubTasks() {
        return this.subTasks;
    }

    @Override
    public void addSubTask(SimpleTask task) {
        this.subTasks.add(task);
    }

    @Override
    public void setStatus(Status status) {
        this.status = status;
    }

    @Override
    public void setTitle(String title) {
        this.title = title;
    }

    @Override
    public String toString() {
        return "MegaTask{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", status=" + status +
                ", subTasks=" + subTasks +
                '}';
    }
}
