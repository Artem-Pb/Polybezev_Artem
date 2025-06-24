package com.javarush.task.pro.task06.task0608;

/* 
Кубический калькулятор
*/

public class Solution {
    public static void main(String[] args) {
        System.out.println(cube(5));
    }

    public static long cube(long x) {
        x *= x * x;
        return x;

    }
}

