package com.javarush.task.pro.task07.task0708;

/* 
Правильные типы
*/

public class Solution {
    public static byte a;
    public static short b;
    public static int c;
    public static long d;

    public static void main(String[] args) {
        setValues(100);
    }

    public static void setValues(long value){
        a = (byte)value;
        System.out.println(a);
        b = (short)value;
        System.out.println(b);
        c = (int)value;
        System.out.println(c);
        d = value;
        System.out.println(d);
    }
}
