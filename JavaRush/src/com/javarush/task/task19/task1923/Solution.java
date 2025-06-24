package com.javarush.task.task19.task1923;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/* 
Слова с цифрами
*/

public class Solution {
    public static void main(String[] args) throws IOException {
        if (args.length < 2) {
            System.out.println("Мало параметров!");
            return;
        }

        String nameFile1 = args[0];
        String nameFile2 = args[1];

        try (BufferedReader reader = new BufferedReader(new FileReader(nameFile1));
             FileWriter writer = new FileWriter(nameFile2)) {
            String[] lines;
            String line;
            while ((line = reader.readLine()) != null) {
                lines = line.split("\\s+");

                for (String s : lines) {
                    if (isDigit(s)) {
                        writer.write(s + " ");
                    }
                }
            }
        }
    }

    private static boolean isDigit(String s) {
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) >= '0' && s.charAt(i) <= '9') {
                return true;
            }
        }
        return false;
    }
}
