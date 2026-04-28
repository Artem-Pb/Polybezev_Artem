package com.github.Artem_Pb.domain;

public interface Task {
    Long getId();
    String getTitle();
    Status getStatus();
    void setStatus(Status status);
    void setTitle(String title);
}