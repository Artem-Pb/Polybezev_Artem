package com.javarush.task.pro.task13.task1316;

public class Solution {

    public static void main(String[] args) {
        JavarushQuest[] quests = JavarushQuest.values();
        for (int i = 0; i < quests.length; i++) {
           int j = quests[i].ordinal();
            System.out.println(j);
        }
    }
}
