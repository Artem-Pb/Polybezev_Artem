package com.javarush.task.pro.task14.task1413;

public class Main
{
    public static String nameClass = " - Имя класса";
    public static String nameMethod = " - Имя метода";
    public static String nameFile = " -  Имя файла";
    public static String numStr = " - Номер строки";
    public static String nameModule = " - Имя модуля";
    public static String versionModule = " - Версия модуля";
    public static String inf = " - Вся информация о StackTrace";

    public static void main(String[] args)
    {
        test();
    }

    public static void test()
    {
        Thread current = Thread.currentThread();
        StackTraceElement[] methods = current.getStackTrace();

        for(StackTraceElement info: methods)
        {
            System.out.println(info + inf);
            System.out.print(info.getClassName() + nameClass);
            System.out.print(" " + info.getMethodName() + nameMethod);


            System.out.print(" " + info.getFileName() + nameFile);
            System.out.print(" " + info.getLineNumber() + numStr);

            System.out.print(" " + info.getModuleName() + nameModule);
            System.out.print(" " + info.getModuleVersion() + versionModule );
            System.out.println();
        }
    }
}
