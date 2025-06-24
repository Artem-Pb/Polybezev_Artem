package com.javarush.task.pro.task09.task0906;

/* 
Двоичный конвертер
*/

public class Solution {
    public static void main(String[] args) {
        int decimalNumber = Integer.MAX_VALUE;
        System.out.println("Десятичное число " + decimalNumber + " равно двоичному числу " + toBinary(decimalNumber));
        String binaryNumber = "1111111111111111111111111111111";
        System.out.println("Двоичное число " + binaryNumber + " равно десятичному числу " + toDecimal(binaryNumber));
    }

    public static String toBinary(int decimalNumber) {
        String binaToDes = "";
        if (decimalNumber <= 0) {
            return binaToDes;
        }
        while (decimalNumber != 0) {
            binaToDes = (decimalNumber % 2) + binaToDes;
            decimalNumber = decimalNumber / 2;
        }
        return binaToDes;
    }

    public static int toDecimal(String binaryNumber) {
        int decimal = 0;
        if (binaryNumber == null) {
            return decimal;

        }
        for (int i = 0; i < binaryNumber.length(); i++) {
            int index = binaryNumber.length() - 1 - i;
            int numVal = Character.getNumericValue(binaryNumber.charAt(index));
            decimal += numVal * Math.pow(2, i);

        }
        return decimal;
    }
}
