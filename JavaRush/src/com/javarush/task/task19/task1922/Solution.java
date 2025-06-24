package com.javarush.task.task19.task1922;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/* 
Ищем нужные строки
*/

public class Solution {
    public static List<String> words = new ArrayList<String>();

    static {
        words.add("файл");
        words.add("вид");
        words.add("В");
    }

    public static void main(String[] args) throws IOException {
        String nameFile;
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            nameFile = reader.readLine();
        }
        try (BufferedReader reader = new BufferedReader(new FileReader(nameFile))) {
            String line;
            int count = 0;
            while ((line = reader.readLine()) != null) {
                for (String str : words) {
                    int is = contains(line, str);
                    if (is > 0) {
                        count += is;
                    }
                }
                if ((count == 2)) {
                    System.out.println(line);
                }
                count = 0;
            }
        }
    }

    public static int contains(String line, String words) {
        int count = 0;
        String[] lines = line.split(" ");
        for (int i = 0; i < lines.length; i++) {
            if (lines[i].equalsIgnoreCase(words)) {
                count++;
            }
        }
        return count;
    }
}
