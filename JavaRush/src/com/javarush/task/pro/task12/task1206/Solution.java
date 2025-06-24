package com.javarush.task.pro.task12.task1206;

/* 
Анализ строк
*/

public class Solution {
    public static void main(String[] args) {
        String string = "Думаю, это будет новой фичей." +
                "Только не говорите никому, что она возникла случайно 1112300 раза.";

        System.out.println("Количество цифр в строке : " + countDigits(string));
        System.out.println("Количество букв в строке : " + countLetters(string));
        System.out.println("Количество пробелов в строке : " + countSpaces(string));
    }

    public static int countDigits(String string) {
        char[] chars = string.toCharArray();
        int countInt = 0;
        for (int i = 0; i < chars.length; i++) {
            if (Character.isDigit(chars[i])){
                countInt++;
            }
        }
        return countInt;
    }

    public static int countLetters(String string) {
        char[] chars = string.toCharArray();
        int countLetters = 0;
        for (int i = 0; i < chars.length; i++) {
            if (Character.isLetter(chars[i])) {
                countLetters++;
            }
        } return countLetters;
    }

    public static int countSpaces(String string) {
        char[] chars = string.toCharArray();
        int countSpace = 0;
        for (int i = 0; i < chars.length; i++) {
            if (Character.isWhitespace(chars[i])) {
                countSpace++;
            }
        }
        return countSpace;
    }
}
