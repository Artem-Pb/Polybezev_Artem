package com.javarush.task.pro.task17.task1717;

public class Aircraft implements Flyable {
    private final int maxSpeed;

    Aircraft(int maxSpeed) {
        this.maxSpeed = maxSpeed;
    }
    public int getMaxSpeed () {
        return maxSpeed;
    }


    public static void main(String[] args) {
        Aircraft aircraft = new Aircraft(1200);
        Raven raven = new Raven(48);
        Eagle eagle = new Eagle(180);

        System.out.println(aircraft.getMaxSpeed());
        System.out.println(raven.getMaxSpeed());
        System.out.println(eagle.getMaxSpeed());
    }
}
