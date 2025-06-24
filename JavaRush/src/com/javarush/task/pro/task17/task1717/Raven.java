package com.javarush.task.pro.task17.task1717;

public class Raven implements Flyable {
    private final int maxSpeed;

    Raven(int maxSpeed) {
        this.maxSpeed = maxSpeed;
    }
    public int getMaxSpeed () {
        return maxSpeed;
    }
}
