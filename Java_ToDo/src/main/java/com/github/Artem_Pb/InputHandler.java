package com.github.Artem_Pb;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

/**
 * Обработчик ввода с консоли с валидацией.
 */
public class InputHandler {
    private final BufferedReader reader;
    private static final InputHandler INSTANCE = new InputHandler();

    public InputHandler(InputStream inputStream) {
        this.reader = new BufferedReader(new InputStreamReader(inputStream));
    }

    private InputHandler() {
        this(System.in);
    }

    public static InputHandler getInstance() {
        return INSTANCE;
    }

    public String readLine() {
        while (true) {
            try {
                String input = reader.readLine().trim();
                if (!input.isEmpty()) {
                    return input;
                }
                println("Ошибка: ввод не может быть пустым. Попробуйте снова:");
            } catch (IOException e) {
                println("Ошибка ввода: " + e.getMessage());
            }
        }
    }

    public int readIntRange(int min, int max) {
        while (true) {
            try {
                int input = Integer.parseInt(readLine());
                if (input >= min && input <= max) {
                    return input;
                }
                println("Ошибка: число должно быть от " + min + " до " + max);
            } catch (NumberFormatException e) {
                println("Ошибка: введите целое число!");
            }
        }
    }

    public int readInt() {
        while (true) {
            try {
                int input = Integer.parseInt(readLine());
                if (input > 0) {
                    return input;
                } else {
                    println("Ошибка: число должно быть положительным!");
                }
            } catch (NumberFormatException e) {
                println("Ошибка: введите положительное целое число!");
            }
        }
    }



    public void print(String message) {
        System.out.print(message);
    }

    public void println(String message) {
        System.out.println(message);
    }

    public void printf(String format, Object... args) {
        print(String.format(format, args));
    }
}