package com.javarush.task.task16.task1632;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/* 
Клубок
*/

public class Solution {
    public static List<Thread> threads = new ArrayList<>(5);

    public static void main(String[] args) {
    }

    static {
        threads.add(new TestThread1());
        threads.add(new TestThread2());
        threads.add(new TestThread3());
        threads.add(new TestThread4());
        threads.add(new TestThread5());
    }

    public static class TestThread1 extends Thread {
        @Override
        public void run() {
            while (true) {
            }
        }
    }

    public static class TestThread2 extends Thread {
        @Override
        public void run() {
            if (isInterrupted()) {
                System.out.println("InterruptedException");
            }
        }
    }

    public static class TestThread3 extends Thread {
        @Override
        public void run() {
            try {
                while (true) {
                    System.out.println("Ура");
                    Thread.sleep(500);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static class TestThread4 extends Thread implements Message {
        @Override
        public void showWarning() {
            this.interrupt();
        }

        @Override
        public void run() {
            while (!isInterrupted()) {
            }
        }
    }

        public static class TestThread5 extends Thread {
            @Override
            public void run() {
                List<Integer> sumNum = new ArrayList<>();
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
                    String key;
                    while (!(key = reader.readLine()).equals("N")) {
                        Integer keyNum = Integer.parseInt(key);
                        sumNum.add(keyNum);
                    }
                    int tmp = 0;
                    for (Integer num : sumNum) {
                        tmp += num;
                    }
                    System.out.println(tmp);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }