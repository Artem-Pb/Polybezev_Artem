package com.javarush.task.task14.task1408;

public class UkrainianHen extends Hen {

    int getCountOfEggsPerMonth() {
        return 12;
    }

    public String getDescription() {
        String country = Country.UKRAINE;
        return super.getDescription() + String.format(" Моя страна - %s. Я несу %d яиц в месяц.",
                 country, getCountOfEggsPerMonth());
    }
}
