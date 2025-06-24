package com.javarush.task.task18.task1828;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/*
Прайсы 2
*/

public class Solution {
    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.out.println("error!");
            return;
        }
        String flag = args[0];
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String pathOfFile = reader.readLine();
        String id = String.format("%-8s", args[1]);

        String nameOfProduct = "";
        String price = "";
        String quantity = "";

        if (flag.equals("-u") && args.length == 5) {
            nameOfProduct = String.format("%-30s", args[2]);
            price = String.format("%-8s", args[3]);
            quantity = String.format("%-8s", args[4]);
        }

        boolean modified = false;
        List<String> fileLines = new ArrayList<>();

        try (BufferedReader reader1 = new BufferedReader(new FileReader(pathOfFile))) {
            String line;
            while ((line = reader1.readLine()) != null) {
                String fileId = line.substring(0, 8).trim();

                if (flag.equals("-u") && fileId.equals(args[1])) {
                    fileLines.add(id + nameOfProduct + price + quantity);
                    modified = true;
                } else if (flag.equals("-d") && fileId.equals(args[1])) {
                    modified = true;
                } else {
                    fileLines.add(line);
                }
            }
        }

        if (modified) {
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(pathOfFile))) {
                for (String s : fileLines) {
                    writer.write(s);
                    writer.newLine();
                }
            }
        }
    }
}

