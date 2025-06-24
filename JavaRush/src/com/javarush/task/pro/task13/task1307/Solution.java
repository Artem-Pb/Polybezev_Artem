package com.javarush.task.pro.task13.task1307;

import java.util.ArrayList;
import java.util.Random;
import java.util.Collections;

/* 
Изучаем методы класса Collections, часть 2
*/

public class Solution {

    public static void reverse(ArrayList<Integer> list) {
        Collections.reverse(list);
        System.out.println(list);
    }

    public static void sort(ArrayList<Integer> list) {
        Collections.sort(list);
        System.out.println(list);
    }

    public static void rotate(ArrayList<Integer> list, int distance) {
        Collections.rotate(list, distance);
        System.out.println(list);
    }

    public static void shuffle(ArrayList<Integer> list) {
        Collections.shuffle(list);
        System.out.println(list);
    }

    public static void main(String[] args) {
        ArrayList<Integer> arr = new ArrayList<Integer>();
        int dist = 4;
        Collections.addAll(arr, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
        reverse(arr);
        rotate(arr,dist);
        sort(arr);
        shuffle(arr);
    }
}
