package com.javarush.task.task13.task1319;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;


/* 
Писатель в файл с консоли
*/

public class Solution {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        String fileOutName = in.nextLine();

        try (BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in))) {
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileOutName))) {
            String line;
            String exit = "exit";
            while (!(line = bufferedReader.readLine()).equals("exit")) {
                writer.write(line + "\n");
            }
            writer.write(exit);
        }
    } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
