package com.javarush.task.pro.task15.task1512;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

/* 
Задом наперед
*/

public class Solution {
    public static ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    public static PrintStream stream = new PrintStream(outputStream);

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        printSomething(scanner.nextLine());
        String result = outputStream.toString();
        char[] charsLine = new char[result.length()];

        for (int i = 0; i < charsLine.length; i++) {
            charsLine[i] = result.charAt(i);
        }
        char[] charsRes = new char[charsLine.length];
        for (int i = 0; i < charsLine.length; i++) {
            charsRes[i] = charsLine[charsLine.length - i - 1];

        }
        String str = Arrays.toString(charsRes);
        printSomething(str);
        System.out.println(outputStream);
    }

    public static void printSomething(String str) {
        stream.print(str);
    }
}