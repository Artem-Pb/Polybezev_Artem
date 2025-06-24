package com.javarush.task.pro.task13.task1314;

/* 
StringLinkedList, часть 2
*/

public class Solution {

    public static void main(String[] args) {
        StringLinkedList stringLinkedList = new StringLinkedList();
        stringLinkedList.add("1");
        stringLinkedList.add("2");
        stringLinkedList.add("3");
        stringLinkedList.add("4");
        stringLinkedList.add("5");

        System.out.println(stringLinkedList.get(0)); // должно вывести "1"
        System.out.println(stringLinkedList.get(2)); // должно вывести "3"
        System.out.println(stringLinkedList.get(4)); // должно вывести "5"
        System.out.println(stringLinkedList.get(5)); // должно вывести null
    }
}
