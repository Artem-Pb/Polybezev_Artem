package com.javarush.task.task14.task1408;

public class MoldovanHen extends Hen{

    int getCountOfEggsPerMonth() {
        return 9;
    }

    public String getDescription() {
        String country = Country.MOLDOVA;
        return  super.getDescription() + String.format(" Моя страна - %s. Я несу %d яиц в месяц.",
                country, getCountOfEggsPerMonth());
    }
}
