package com.github.Artem_Pb;

import java.util.Arrays;

/**
 * Перечисление всех доступных команд приложения
 */
public enum Command {
    // Основные команды
    ADD_SIMPLE(1, "Добавить простую задачу"),
    ADD_MEGA(2, "Добавить составную задачу"),
    SHOW_TODO(3, "Показать все задачи"),
    DEL_TASK(4, "Удалить задачу"),
    UPDATE_TASK(5, "Редактировать задачу"),
    DEL_TODO(6, "Очистить список"),
    SHOW_COMPLETE(7, "Показать выполненные"),
    STATS(8, "Статистика"),
    SEARCH(9, "Поиск задач"),
    START_TASK(10, "Начать выполнение задачи"),
    COMPLETE_TASK(11, "Завершить задачу"),
    RESET_TASK(12, "Сбросить статус"),
    EXIT(13, "Выход"),

    // Служебные сообщения
    HI(100, "\nДобро пожаловать в ToDo Manager!"),
    BY(101, "До свидания!"),
    WHAT_TASK(102, "Введите номер задачи:"),
    WHAT_SUBTASK(103, "Введите номер подзадачи:");

    private final int number;
    private final String text;

    Command(int number, String text) {
        this.number = number;
        this.text = text;
    }

    public int getNumber() {
        return number;
    }

    public String getCommand() {
        return text;
    }

    /**
     * Возвращает команду по номеру
     */
    public static Command getByNumber(int number) {
        return Arrays.stream(values())
                .filter(cmd -> cmd.number == number)
                .findFirst()
                .orElseThrow(() -> new IllegalArgumentException("Неизвестный номер команды"));
    }

    /**
     * Печатает основное меню (только команды с номерами 1-11)
     */
    public static void printMenu() {
        System.out.println(HI.getCommand());
        Arrays.stream(values())
                .filter(cmd -> cmd.number <= 13)
                .forEach(cmd -> System.out.println(cmd.number + ". " + cmd.text));
    }
}