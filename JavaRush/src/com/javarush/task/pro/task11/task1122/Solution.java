package com.javarush.task.pro.task11.task1122;

/* 
Затенение поля класса
*/

public class Solution {
    private int salary;

    public int add(int increase) {
        int salary = this.salary;
        this.salary += increase;
        return this.salary;
    }
    public static void main(String[] args) {
        Solution solution = new Solution();
        solution.add(100500);
        System.out.println(solution.salary);
    }
}