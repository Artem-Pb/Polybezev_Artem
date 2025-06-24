package com.javarush.task.pro.task08.task0808;
import java.lang.Thread.*;
/* 
Обратный отсчет
*/

public class Solution {

    public static void main(String[] args) throws InterruptedException {
        countDown();
    }
    public static void countDown() throws InterruptedException {
        for (int i = 3; i > 0; i--) {
            System.out.println(i);
            Thread.sleep(1000);
        }
        System.out.print("Старт!");
    }
}
