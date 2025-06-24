package com.javarush.task.pro.task17.task1715;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/* 
Вилларибо и Виллабаджо.
*/

public class Solution {
    static List<MusicalInstrument> orchestra = new ArrayList<>();

    public static void main(String[] args) {
        createKeyboardOrchestra();
        createStringedOrchestra();
        playOrchestra();
    }

    public static void createKeyboardOrchestra() {
        for (int i = 0; i <= 2; i++) {
            if (i == 0) {
                orchestra.add(new Organ());
            }
            orchestra.add(new Piano());
        }
    }

    public static void createStringedOrchestra() {
        for (int i = 4; i <= 5 ; i++) {
            if (i == 4) {
                orchestra.add(new Guitar());
            }
            orchestra.add(new Violin());
        }
    }

    public static void playOrchestra() {
        for (MusicalInstrument mus : orchestra) {
            mus.play();
        }
    }
}
