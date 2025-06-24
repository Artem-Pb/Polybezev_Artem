package com.javarush.task.pro.task05.task0507;

import java.util.Scanner;

/* 
Максимальное из N чисел
*/

public class Solution {
    public static int[] array;

    public static void main(String[] args) throws Exception {
        Scanner in  = new Scanner(System.in);

        int N = in.nextInt(), tmp = Integer.MIN_VALUE;
        array = new int[N];

        for (int i = 0; i < array.length; i++) {
            array[i] = in.nextInt();
            if (array[i] > tmp) {
                tmp = array[i];
            }
        }
        System.out.print(tmp);
    }
}
