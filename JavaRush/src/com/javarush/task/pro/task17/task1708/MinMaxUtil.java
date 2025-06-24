package com.javarush.task.pro.task17.task1708;

/* 
Минимальное и максимальное
*/

public class MinMaxUtil {
    public static int min (int num, int num1) {
        return Math.min(num, num1);
    }

    public static int min (int num, int num1, int num2) {
        return Math.min(num, Math.min(num1, num2));
    }

    public static int min (int num, int num1, int num2, int num3) {
        return Math.min(num, Math.min(num1, Math.min(num2, num3)));
    }

    public static int min (int num, int num1, int num2, int num3, int num4) {
        return Math.min(num, Math.min(num1 ,Math.min(num2 ,Math.min(num3, num4))));
    }

    public static int max (int num, int num1) {
        return Math.max(num, num1);
    }

    public static int max (int num, int num1, int num2) {
        return Math.max(num, Math.max(num1, num2));
    }

    public static int max (int num, int num1, int num2, int num3) {
        return Math.max(num, Math.max(num1, Math.max(num2, num3)));
    }

    public static int max (int num, int num1, int num2, int num3, int num4) {
        return Math.max(num, Math.max(num1 ,Math.max(num2 ,Math.max(num3, num4))));
    }

    public static void main(String[] args) {
        System.out.printf("%d - min(2), %d - min(3), %d - min(4), %d - min(5);\n%d - max(2), %d - max(3), %d - max(4), %d - max(5);",
                min(2,3), min(2, 5, 99), min(4, 5, 0, -12), min(39, 99, 54, 69, 93),
                max(4, 0), max(43,-12, 912), max(-323, -123, -232, -32), max(0, -1, -43, 124, 394));

    }
}
