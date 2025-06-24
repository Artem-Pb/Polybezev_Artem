package com.javarush.task.pro.task08.task0801;

import static java.lang.Math.toRadians;

/* 
Утильный класс: часть 1
*/

public class Solution {

    public static double sin(double a) {
        a = Math.sin(Math.toRadians(a));
        return a;
    }

    public static double cos(double a) {
        a = Math.cos(Math.toRadians(a));
        return a;
    }

    public static double tan(double a) {
        a = Math.tan(Math.toRadians(a));
        return a;
    }

    public static void main(String[] args) {
        System.out.println(tan(1.0));
        System.out.println(sin(2.0));
        System.out.println(cos(3.0));
    }
}
