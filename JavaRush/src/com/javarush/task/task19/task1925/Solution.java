package com.javarush.task.task19.task1925;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

/* 
Длинные слова
*/

public class Solution {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Неверное кол-во параметров");
        }
        String fileName1 = args[0];
        String fileName2 = args[1];

        try (BufferedReader reader = new BufferedReader(new FileReader(fileName1))) {
            String line;
            String[] words;
            ArrayList<String> parts = new ArrayList<>();
            while ((line = reader.readLine()) != null) {
                words = line.split("\\s+");
                for (String s : words) {
                    if (!s.isEmpty()) {
                        parts.add(s);
                    }
                }
            }

            try (FileWriter fileWriter = new FileWriter(fileName2)) {
                for (int i = 0; i < parts.size(); i++) {
                    if (parts.get(i).length() > 6 && i != parts.size() - 1) {
                        fileWriter.write(parts.get(i) + ",");
                    } else if (parts.get(i).length() > 6 && i == parts.size() -1) {
                        fileWriter.write(parts.get(i));
                    }
                }
            }
        } catch (IOException e) {
            //ignored
        }
    }
}
