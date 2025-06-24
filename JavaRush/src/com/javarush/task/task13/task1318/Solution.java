package com.javarush.task.task13.task1318;

import java.io.*;
import java.util.Scanner;

/* 
Чтение файла
*/

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String sourceFileName = reader.readLine();
        FileInputStream inputStream = new FileInputStream(sourceFileName);

        try (Scanner in = new Scanner(inputStream)) {
            StringBuilder stringBuilder = new StringBuilder();

            while (in.hasNextLine()) {
                stringBuilder.append(in.nextLine()).append("\n");
            }
            System.out.print(stringBuilder.toString());
        } finally {
            reader.close();
            inputStream.close();
        }
    }
}