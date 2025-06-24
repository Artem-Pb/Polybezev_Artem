package com.javarush.task.task20.task2021;

import java.io.*;

/* 
Сериализация под запретом
*/

public class Solution implements Serializable {
    public static class SubSolution extends Solution {
        private void writeObject(ObjectOutputStream writer) throws NotSerializableException {
            throw new NotSerializableException("No!");
        }
        private void readObject(ObjectInputStream reader) throws NotSerializableException{
            throw new NotSerializableException("No!");
        }
    }

    public static void main(String[] args) {

    }
}
