package com.javarush.task.pro.task15.task1507;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Scanner;

/* 
Пропускаем не всех
*/

public class Solution {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        List<String> stringList = Files.readAllLines(Paths.get(in.nextLine()));
        for (int i = 0; i < stringList.size(); i+=2) {
            System.out.println(stringList.get(i));
        }
    }
}

