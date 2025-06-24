package com.javarush.task.task14.task1420;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

/* 
НОД
*/

public class Solution {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        int numStr = in.nextInt();
        int numStr1 = in.nextInt();
        in.close();

        int numLess = Math.min(numStr1, numStr);
        int numMore = Math.max(numStr1, numStr);

        int NOD = 1;
        int remainder = 1;

        while (remainder != 0) {
            remainder = numMore % numLess;
            numMore = numLess;
            if (remainder == 0) {
                NOD = numLess;
            }
            numLess = remainder;
        }
        System.out.println(NOD);
    }
}
