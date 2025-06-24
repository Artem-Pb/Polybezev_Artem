package com.javarush.task.pro.task17.task1716;

public class Car implements Vehicle {

    public void move() {
        System.out.println("Еду со средней скоростью 70 км/ч.");
    }


    public static void main(String[] args) {
        Car car = new Car();
        Bus bus = new Bus();
        car.start();
        car.move();
        car.stop();

        bus.start();
        bus.move();
        bus.stop();
    }
}
