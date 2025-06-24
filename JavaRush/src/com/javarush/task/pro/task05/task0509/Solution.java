package com.javarush.task.pro.task05.task0509;

/* 
Таблица умножения
*/

public class Solution {

    public static int[][] MULTIPLICATION_TABLE;

    public static void main(String[] args) {
        MULTIPLICATION_TABLE = new int[131][131];
        int[] tmp = new int[131];
        int x = 1;
        for (int i = 0; i < MULTIPLICATION_TABLE.length; i++) {
            int y = 1;
            tmp = MULTIPLICATION_TABLE[i];
            for (int j = 0; j < tmp.length; j++) {
                int z = x * y;
                tmp[j] = z;
                System.out.print(tmp[j] + " ");
                y++;
            }
            x++;
            System.out.println();
        }
    }
}

