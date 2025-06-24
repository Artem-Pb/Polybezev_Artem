package com.javarush.task.pro.task10.task1017;

/* 
Создание материков
*/

public class Earth {
    public static void main(String[] args) {
        Africa africa = new Africa(92_000_000 / 3);
        Antarctica antarctica = new Antarctica(92_000_000 / 6);
        Australia australia = new Australia(180_000_000 / (3 * 5));
        Eurasia eurasia = new Eurasia(92_000_000 / 2);
        NorthAmerica northAmerica = new NorthAmerica(92_000_000 / 4);
        SouthAmerica southAmerica = new SouthAmerica(92_000_000);

    }
}
