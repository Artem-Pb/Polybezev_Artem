package com.javarush.task.pro.task08.task0809;

/* 
Counter

*/
public class Solution {

    public static void main(String[] args) throws InterruptedException {
        printNumbers();
    }

    public static void printNumbers() throws InterruptedException {
        for (int i = 1; i < 11; i++) {
            if (i < 10) {
                System.out.println(i);
                Thread.sleep(1, 300_000);
            } else {
                System.out.println(i);
            }
        }
    }
}
