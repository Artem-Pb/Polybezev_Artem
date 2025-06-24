package com.javarush.task.pro.task09.task0907;

/* 
Шестнадцатеричный конвертер
*/

public class Solution {
    private static final String HEX = "0123456789abcdef";

    public static void main(String[] args) {
        int decimalNumber = 1256;
        System.out.println("Десятичное число " + decimalNumber + " равно шестнадцатеричному числу " + toHex(decimalNumber));
        String hexNumber = "4e8";
        System.out.println("Шестнадцатеричное число " + hexNumber + " равно десятичному числу " + toDecimal(hexNumber));
    }

    public static String toHex(int decimalNumber) { // из 10 в 16
        String perfHex = "";
        while (decimalNumber > 0) {
            char index = HEX.charAt(decimalNumber % 16);
            perfHex = index + perfHex;
            decimalNumber /= 16;
        }
        return perfHex;
    }

    public static int toDecimal(String hexNumber) { // из 16 в 10
        int decimal = 0;
        if (hexNumber == null) {
            return 0;
        }
        for (int i = 0; i < hexNumber.length(); i++) {
            int index = HEX.indexOf(hexNumber.charAt(i));
            decimal = decimal * 16 + index;
        }
        return decimal;
    }
}

