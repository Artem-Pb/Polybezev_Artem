package com.javarush.task.pro.task13.task1306;

import java.util.ArrayList;
import java.util.Collections;

/* 
Изучаем методы класса Collections, часть 1
*/

public class Solution {

    public static void copy(ArrayList<String> destination, ArrayList<String> source) {
        if (destination.size() < source.size()) {
            throw new IndexOutOfBoundsException("Source does not fit in dest");
        }
        Collections.copy(destination, source);
        System.out.println(source);
    }

    public static void addAll(ArrayList<String> list, String... strings) {
        Collections.addAll(list, strings);
        System.out.println(list);
    }

    public static void replaceAll(ArrayList<String> list, String oldValue, String newValue) {
        Collections.replaceAll(list, oldValue, newValue);
        System.out.println(list);
    }

    public static void main(String[] args) {
        ArrayList<String> x = new ArrayList<>();
        ArrayList<String> y = new ArrayList<>(x);
        String c = "g", v = "1", g = "3";
        addAll(x,c,g,v);
        copy(x,y);
        replaceAll(x,c,v);
    }
}
