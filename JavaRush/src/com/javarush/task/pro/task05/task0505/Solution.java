package com.javarush.task.pro.task05.task0505;

import java.util.Scanner;

/* 
Reverse
*/

public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int[] arr = new int[N];
        for (int i = 0; i < arr.length; i++) {
            if (N > 0) {
                arr[i] = in.nextInt();
            }
        }
        int[] arr_dop = new int[arr.length];
        if (N % 2 == 1) {
            for (int i = 0; i < arr.length; i++) {
                arr_dop[i] = arr[i];
                System.out.println(arr_dop[i]);
            }
        } else {
            for (int i = arr.length; i > 0; i--) {
                System.out.println(arr[i - 1]);
            }
        }
    }
}
