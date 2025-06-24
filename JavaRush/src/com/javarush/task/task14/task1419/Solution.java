package com.javarush.task.task14.task1419;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InterruptedIOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/* 
Нашествие исключений
*/

public class Solution {
    public static List<Exception> exceptions = new ArrayList<Exception>();

    public static void main(String[] args) {
        initExceptions();


        for (Exception exception : exceptions) {
            System.out.println(exception);
        }
    }

    private static void initExceptions() {   //the first exception
        try {
            float i = 1 / 0;

        } catch (Exception e) {
            exceptions.add(e);
        }

        try {
            int[] a = new int[-1];
        } catch (Exception e) {
            exceptions.add(e);
        }

        try {
            int[] a = {1, 1};
            for (int i = 1; i < a.length; i--) {
                a[i] = 3;
            }
        } catch (Exception e) {
            exceptions.add(e);
        }

        try {
            InputStream inputStream = new FileInputStream("dfg.yh");
        } catch (Exception e) {
            exceptions.add(e);
        }
        exceptions.add(new ArrayStoreException());
        exceptions.add(new InterruptedIOException());
        exceptions.add(new IllegalAccessException());
        exceptions.add(new InstantiationException());
        exceptions.add(new NoSuchFieldException());
        exceptions.add(new SecurityException());

    }
}
