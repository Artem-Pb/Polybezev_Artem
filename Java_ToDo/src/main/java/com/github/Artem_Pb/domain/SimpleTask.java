package com.github.Artem_Pb.domain;

import jakarta.persistence.*;

@Entity
@Table(name = "tasks")
public class SimpleTask implements Task {

    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "task_seq")
    @SequenceGenerator(name = "task_seq", sequenceName = "task_sequence", allocationSize = 1)
    private Long id;

    @Column(nullable = false)
    private String title;

    @Enumerated(EnumType.STRING)
    private Status status;

    public SimpleTask(String title) {
        this.title = title;
        this.status = Status.NOT_STARTED;
    }

    protected SimpleTask() {

    }

    @Override
    public Long getId() {
        return id;
    }

    @Override
    public String getTitle() {
        return this.title;
    }

    @Override
    public Status getStatus() {
        return this.status;
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
        return "SimpleTask{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", status=" + status +
                '}';
    }
}
