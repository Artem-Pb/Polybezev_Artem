package com.javarush.task.pro.task10.task1001;

/* 
Создадим небоскреб
*/

public class Skyscraper {

    public String skyscraper;

    public Skyscraper() {
        this.skyscraper = "Небоскреб построен.";
        System.out.print(skyscraper);
    }

    public static void main(String[] args) {
        Skyscraper skyscraper = new Skyscraper();
    }
}
