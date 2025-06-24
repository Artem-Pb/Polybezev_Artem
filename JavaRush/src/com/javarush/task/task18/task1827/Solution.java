package com.javarush.task.task18.task1827;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/* 
Прайсы
*/

public class Solution {
    public static void main(String[] args) throws Exception {
        if (args.length < 4) {
            System.out.println("Error!");
            return;
        }

        List<String> params = new ArrayList<>();
        for (String s : args) {
            params.add(s);
        }

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String fileName = reader.readLine();

        String flag = params.get(0);
        if (flag.equals("-c")) {
            StringBuilder nameProduct = new StringBuilder(params.get(1));
            while (nameProduct.length() < 30) {
                nameProduct.append(" ");
            }
            StringBuilder price = new StringBuilder(params.get(2));
            while (price.length() < 8) {
                price.append(" ");
            }
            StringBuilder quantity = new StringBuilder(params.get(3));
            while (quantity.length() < 4) {
                quantity.append(" ");
            }
            StringBuilder resultString = new StringBuilder();
            int lastId = 0;
            try (BufferedReader input = new BufferedReader(new FileReader(fileName))) {
                String line;
                while ((line = input.readLine()) != null) {
                    String idStr = line.substring(0, 8).trim();
                    try {
                        int id = Integer.parseInt(idStr);
                        if (id > lastId) {
                            lastId = id;
                        }
                    } catch (NumberFormatException e) {
                        // NON
                    }
                }
            }

            lastId++;

            StringBuilder newId = new StringBuilder(String.valueOf(lastId));
            while (newId.length() < 8) {
                newId.append(" ");
            }

            resultString.append(newId).append(nameProduct).append(price).append(quantity);

            try (FileWriter writer = new FileWriter(fileName, true)) {
                writer.write("\n");
                writer.write(resultString.toString());
            }
        }
    }
}

