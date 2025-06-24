package com.javarush.task.task15.task1507;

/* 
ООП - Перегрузка
*/

import java.beans.Introspector;

public class Solution {
    public static void main(String[] args) {
        printMatrix(2, 3, "8");
        printMatrix(1,5,127);
        printMatrix(2,2, 122f);
        printMatrix(3,2, 12232L);
        printMatrix(1,3,true);
        printMatrix(1,4, 3.4);
        printMatrix(1,3, (short)34);
        printMatrix(2,2,'c');
    }


    public static void printMatrix(int m, int n, String value) {
        System.out.println("Заполняем объектами String");
        printMatrix(m, n, (Object) value);
    }

    public static void printMatrix(int m, int n, Object value) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(value);
            }
            System.out.println();
        }
    }

    public static void printMatrix(int m, int n, Float value) {
        System.out.println("Заполняем объектами float");
        printMatrix(m, n, (Float) value);
    }

    public static void printMatrix(int m, int n, Double value) {
        System.out.println("Заполняем объектами Double");
        printMatrix(m, n, (Double) value);
    }

    public static void printMatrix(int m, int n, Character value) {
        System.out.println("Заполняем объектами char");
        printMatrix(m, n, (Character) value);
    }

    public static void printMatrix(int m, int n, Byte value) {
        System.out.println("Заполняем объектами byte");
        printMatrix(m, n, (Byte) value);
    }

    public static void printMatrix(int m, int n, Short value) {
        System.out.println("Заполняем объектами short");
        printMatrix(m, n, (Short) value);
    }

    public static void printMatrix(int m, int n,Long value) {
        System.out.println("Заполняем объектами long");
        printMatrix(m, n, (Long) value);
    }

    public static void printMatrix(int m, int n, Boolean value) {
        System.out.println("Заполняем объектами boolean");
        printMatrix(m, n, (Boolean) value);
    }

    public static void printMatrix(int m, int n, Integer value) {
        System.out.println("Заполняем объектами int");
        printMatrix(m, n, (Integer) value);
    }
}
