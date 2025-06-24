package com.javarush.task.task13.task1326;

import java.io.*;
import java.util.ArrayList;
import java.util.stream.Stream;

/* 
Сортировка четных чисел из файла
*/

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String FileNameTo = reader.readLine();
        ArrayList<Integer> list = new ArrayList<>();
        try (FileInputStream input = new FileInputStream(FileNameTo);
             BufferedReader reader1 = new BufferedReader(new InputStreamReader(input))) {

            while (reader1.ready()) {
                String line = reader1.readLine();
                Integer num = Integer.parseInt(line);
                list.add(num);
            }
            Stream<Integer> listInteger = list.stream().filter(x -> x % 2 == 0).sorted();
            listInteger.forEach(System.out ::println);
        }
        finally {
            reader.close();
        }
    }
}
