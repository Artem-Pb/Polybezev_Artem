package com.javarush.task.pro.task16.task1607;

import java.time.LocalDate;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

/* 
Освоение нового API
*/

public class Solution {

    public static void main(String[] args) {
        System.out.println(nowExample());
        System.out.println(ofExample());
        System.out.println(ofYearDayExample());
        System.out.println(ofEpochDayExample());
    }

    static LocalDate nowExample() {
        return LocalDate.now();
    }

    static LocalDate ofExample() {
        return LocalDate.of(2020, 9, 12);
    }

    static LocalDate ofYearDayExample() {
        int i;
        LocalDate date = LocalDate.of(2020, 1, 1);
        LocalDate date1 = LocalDate.of(2020, 9,12);
       for (i = 1; i < 365;) {
           date = date.plusDays(1);
           i++;
            if (date.equals(date1)) break;
        }
        System.out.println(i);
        return LocalDate.ofYearDay(2020, i);
    }

    static LocalDate ofEpochDayExample() {
        int i;
        LocalDate date = LocalDate.of(1970, 1, 1);
        LocalDate date1 = LocalDate.of(2020, 9,12);
        for (i = 0; i < 100000;) {
            date = date.plusDays(1);
            i++;
            if (date.equals(date1)) break;
        }
        System.out.println(i);
        return LocalDate.ofEpochDay(i);
    }
}
