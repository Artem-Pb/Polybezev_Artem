package com.javarush.task.task15.task1514;

import java.util.HashMap;
import java.util.Map;

/* 
Статики-1
*/

public class Solution {
    public static Map<Double, String> labels = new HashMap<Double, String>();

    static {
        labels.put(5.5,"Double 3");
        labels.put(1.3, "Double 5");
        labels.put(4.3, "Double 1");
        labels.put(1.9, "Double 4");
        labels.put(665.5, "Double 2");
    }

    public static void main(String[] args) {
        System.out.println(labels);
    }
}
