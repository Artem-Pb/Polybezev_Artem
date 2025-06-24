package com.javarush.task.pro.task06.task0607;

/* 
Добро пожаловать! Но не всем.
*/

public class Solution {

    public static void main(String[] args) {
        signIn("user");
    }

    public static void signIn(String username) {
        String s = "user";
        if (username.equals(s))
            return;
        else
            System.out.println("Добро пожаловать " + username);
        System.out.println("Очень скучали по Вам, " + username);
    }
}
