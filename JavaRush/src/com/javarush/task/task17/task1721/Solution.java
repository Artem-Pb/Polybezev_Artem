package com.javarush.task.task17.task1721;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/* 
Транзакционность
*/

public class Solution {
    public static List<String> allLines = new ArrayList<String>();
    public static List<String> forRemoveLines = new ArrayList<String>();

    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            String fileName1 = reader.readLine();
            String fileName2 = reader.readLine();
            reader.close();
            try (BufferedReader readerFile1 = new BufferedReader(new FileReader(fileName1));
                 BufferedReader readerFile2 = new BufferedReader(new FileReader(fileName2))) {
                String line1;
                String line2;

                while ((line1 = readerFile1.readLine()) != null) {
                    allLines.add(line1);
                }

                while ((line2 = readerFile2.readLine()) != null) {
                    forRemoveLines.add(line2);
                }
                Solution solution = new Solution();
                solution.joinData();
            }
        } catch (Exception ignored) {
        }
    }

            public void joinData () throws CorruptedDataException {
                if (allLines.containsAll(forRemoveLines)) {
                    allLines.removeAll(forRemoveLines);
                } else {
                    allLines.clear();
                    throw new CorruptedDataException();
                }
            }
        }
