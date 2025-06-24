package com.javarush.task.pro.task17.task1717;

public class Eagle implements Flyable {

    private final int maxSpeed;

    Eagle(int maxSpeed) {
        this.maxSpeed = maxSpeed;
    }
    public int getMaxSpeed () {
        return maxSpeed;
    }
}
