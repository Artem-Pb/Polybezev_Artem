package com.javarush.task.pro.task13.task1309;

import java.util.HashMap;

/* 
Успеваемость студентов
*/

public class Solution {
    public static HashMap<String, Double> grades = new HashMap<>();

    public static void main(String[] args) {
        addStudents();
        System.out.println(grades);
    }

    public static void addStudents() {
            grades.put("mike", 1.2);
            grades.put("nike", 4.4);
            grades.put("kit", 5.0);
            grades.put("kosm", 5.0);
            grades.put("fuga", 4.9);
    }
}
