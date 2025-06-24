package com.javarush.task.pro.task13.task1303;

import java.util.Arrays;
import java.util.HashSet;

/* 
Выводим в консоли элементы множества
*/

public class Solution {

    public static void print(HashSet<String> words) {
        for (String iterator : words) {
            System.out.println(iterator);
        }
    }


    public static void main(String[] args) {
        HashSet<String> words = new HashSet<>(Arrays.asList("на примерах учат програмированию".split(" ")));
        print(words);
    }
}
