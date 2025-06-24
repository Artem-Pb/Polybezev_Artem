package com.javarush.task.pro.task06.task0606;

/* 
Универсальный солдат
*/

import java.util.Arrays;

public class Solution {

    public static void main(String[] args) {
        universalMethod(1,1.0,2.0);
        universalMethod(5);
        universalMethod(7f);
        universalMethod("beer");

    }

    public static void universalMethod(int balance, double payment, double sum1) {
        sum1 = balance + payment * 0.1;
        System.out.println(sum1);
    }

    public static void universalMethod(int[] tabOfPayment, int sum) {
        tabOfPayment = new int[5];
        for (int i = 0; i < tabOfPayment.length; i++) {
            tabOfPayment[i] = sum;
            String s = Arrays.toString(tabOfPayment);
            System.out.println(s);
        }
    }
    public static void universalMethod(String beer) {
        beer = "non-alcoholic";
        System.out.println(beer);
    }
    public static void universalMethod(String[][] beer) {
        for (int i = 0; i < beer.length; i++) {
            for (int j = 0; j < beer.length;j++) {
                beer[i][j] = "beer!=alcohol";
            }
        }
        String s = Arrays.deepToString(beer);
        System.out.println(s);
    }
    public static void universalMethod(float y) {
        y = 1.1f;
        System.out.println(y);
    }
    public static void universalMethod(int h) {
        h = 5;
        System.out.println(h);
    }
    public static void universalMethod(int[] pop) {
        Arrays.fill(pop,10);
        String s = Arrays.toString(pop);
        System.out.println(s);
    }
    public static void universalMethod(int x, String y){
        x = 0;
        while (x < 10) {
            y = "Hi, java";
            System.out.print(y + " ");
            x++;
        }
    }
    public static void universalMethod(String i, short j){
        i = "hi, i'm Artem";
        j = 12;
        System.out.println(i + " мне " + j);
    }
    public static void universalMethod(double[] array, int[] arr) {
        Arrays.fill(array,11.12);
        Arrays.copyOf(array,arr.length);
        String s = Arrays.toString(arr);
        System.out.println(s);

    }
}
