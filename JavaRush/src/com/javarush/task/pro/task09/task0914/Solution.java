package com.javarush.task.pro.task09.task0914;

/* 
Обновление пути
*/

public class Solution {
    public static void main(String[] args) {
        String path = "/usr/java/jdk1.8/bin/";

        String jdk13 = "jdk-13";
        System.out.println(changePath(path, jdk13));
    }

    public static String changePath(String path, String jdk) {
        int i = path.indexOf("jdk");
        int i1 = path.indexOf("/", i);
        String oldJ = path.substring(i, i1);
        return path.replace(oldJ, jdk);
    }
}
