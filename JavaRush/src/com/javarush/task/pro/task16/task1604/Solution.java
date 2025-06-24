package com.javarush.task.pro.task16.task1604;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

/* 
День недели рождения твоего
*/

public class Solution {
    static String monday = "Понедельник";
    static String tuesday = "Вторник";
    static String wednesday = "Среда";
    static String thursday = "Четверг";
    static String friday = "Пятница";
    static String saturday = "Суббота";
    static String sunday = "Воскресенье";


    static Calendar birthDate = new GregorianCalendar(1997, Calendar.JANUARY, 1);

    public static void main(String[] args) {
        System.out.println(getDayOfWeek(birthDate));
    }

    static String getDayOfWeek(Calendar calendar) {
        int calendar1 = calendar.get(Calendar.DAY_OF_WEEK);
        switch (calendar1) {
            case Calendar.SUNDAY:
                return sunday;
            case Calendar.MONDAY:
                return monday;
            case Calendar.TUESDAY:
                return tuesday;
            case Calendar.WEDNESDAY:
                return wednesday;
            case Calendar.THURSDAY:
                return thursday;
            case Calendar.FRIDAY:
                return friday;
            case Calendar.SATURDAY:
                return saturday;
        }
        return null;
    }
}
