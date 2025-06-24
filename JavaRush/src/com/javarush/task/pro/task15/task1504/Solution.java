package com.javarush.task.pro.task15.task1504;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

/* 
Перепутанные байты
*/

public class Solution {
    public static void main(String[] args) {
        try (Scanner in = new Scanner(System.in);
             var file1 = Files.newInputStream(Paths.get(in.nextLine()));
             var file2 = Files.newOutputStream(Paths.get(in.nextLine()))) {
            byte[] bufferFile1 = file1.readAllBytes();
            byte[] bufferFile2 = new byte[bufferFile1.length];
            for (int i = 0; i < bufferFile2.length; i += 2) {
                if (i < bufferFile1.length - 1) {
                    bufferFile2[i] = bufferFile1[i + 1];
                    bufferFile2[i + 1] = bufferFile1[i];
                } else {
                    bufferFile2[i] = bufferFile1[i];
                }
            }
            file2.write(bufferFile2);
        } catch (IOException e) {
            System.out.println("Something went wrong " + e);
        }
    }
}

