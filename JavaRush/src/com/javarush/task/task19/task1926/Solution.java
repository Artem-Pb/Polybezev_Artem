package com.javarush.task.task19.task1926;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

/* 
Перевертыши
*/

public class Solution {
    public static void main(String[] args) {
        String nameFile = "";
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
             nameFile = reader.readLine();
        } catch (IOException e) {
            //ignored
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(nameFile))) {
            String line;
            while ((line = reader.readLine()) != null) {
                StringBuilder stringBuilder = new StringBuilder(line);
                stringBuilder.reverse();
                System.out.println(stringBuilder);
                stringBuilder.setLength(0);
            }
        } catch (IOException e) {
            //ignored
        }
    }
}
