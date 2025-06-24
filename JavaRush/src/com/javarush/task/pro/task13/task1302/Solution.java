package com.javarush.task.pro.task13.task1302;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;

import static java.util.Arrays.asList;
import static java.util.Arrays.spliterator;

/* 
Проверка присутствия
*/

public class Solution {
    public static HashSet<String> words = new HashSet<>(asList("Если 1 бы меня попросили выбрать язык на замену Java я бы не выбирал".split(" ")));

    public static void checkWords(String word) {
        Iterator<String> iterator = words.iterator();
        if (iterator.hasNext()){

        }

    }

    public static void main(String[] args) {
        checkWords("JavaScript");

    }
}
