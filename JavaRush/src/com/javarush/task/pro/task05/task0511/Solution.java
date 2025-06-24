package com.javarush.task.pro.task05.task0511;

import java.util.Scanner;

/* 
Создаем двумерный массив
*/

public class Solution {
    public static int[][] multiArray;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int x = in.nextInt();
        multiArray = new int[x][];
        for (int i = 0; i < multiArray.length;i++) {
            int y = in.nextInt();
            multiArray[i] = new int[y];
            for(int j = 0; j < multiArray[i].length; j++) {
                multiArray[i][j] = 1;
                System.out.print(multiArray[i][j] + " ");
            }
            System.out.println();
        }
    }
}
