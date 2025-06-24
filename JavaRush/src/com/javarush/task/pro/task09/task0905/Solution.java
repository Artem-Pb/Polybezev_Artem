package com.javarush.task.pro.task09.task0905;

/* 
Восьмеричный конвертер
*/

public class Solution {
    public static void main(String[] args) {
        int decimalNumber = 2111;
        System.out.println("Десятичное число " + decimalNumber + " равно восьмеричному числу " + toOctal(decimalNumber));
        int octalNumber = 25123;
        System.out.println("Восьмеричное число " + octalNumber + " равно десятичному числу " + toDecimal(octalNumber));
    }

    public static int toOctal(int decimalNumber) {
        int i = 0;
        int octalNum = 0;
        if (decimalNumber <= 0) {
            return octalNum;
        }
        while (decimalNumber != 0) {
            octalNum = (int) (octalNum + (decimalNumber % 8) * Math.pow(10, i++));
            decimalNumber = decimalNumber / 8;
        }
        return octalNum;
    }

    public static int toDecimal(int octalNumber) {
        int i = 0;
        int decimalNum = 0;
        if (octalNumber <= 0) {
            return decimalNum;
        }
        while (octalNumber != 0) {
            decimalNum = (int)(decimalNum + (octalNumber % 10) * Math.pow(8, i++));
            octalNumber = octalNumber / 10;
        }
        return decimalNum;
    }
}


