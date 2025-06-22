import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Менеджер для работы с сохранением и загрузкой списка задач
 */
public class FileManager {
    private static final String FILE_PATH = "todo_list.dat";
    private static final Logger logger = Logger.getLogger(FileManager.class.getName());
    private static final FileManager INSTANCE = new FileManager();

    private FileManager() {} // Приватный конструктор

    public static FileManager getInstance() {
        return INSTANCE;
    }

    /**
     * Загружает список задач из файла
     * @return загруженный ToDoList или новый экземпляр, если файла нет
     */
    public ToDoList load() {
        File file = new File(FILE_PATH);
        if (!file.exists() || file.length() == 0) {
            logger.log(Level.INFO, "Файл не найден или пуст. Создан новый список.");
            return new ToDoList(InputHandler.getInstance());
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILE_PATH))) {
            return (ToDoList) ois.readObject();
        } catch (IOException e) {
            logger.log(Level.SEVERE, "Ошибка чтения файла: " + e.getMessage(), e);
        } catch (ClassNotFoundException e) {
            logger.log(Level.SEVERE, "Некорректный формат файла: " + e.getMessage(), e);
        }

        return new ToDoList(InputHandler.getInstance());
    }

    /**
     * Сохраняет список задач в файл
     * @param todoList список для сохранения
     */
    public void save(ToDoList todoList) {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_PATH))) {
            oos.writeObject(todoList);
            logger.log(Level.INFO, "Список задач успешно сохранён");
        } catch (IOException e) {
            logger.log(Level.SEVERE, "Ошибка сохранения: " + e.getMessage(), e);
        }
    }

    /**
     * Проверяет существование файла с данными
     */
    public boolean dataFileExists() {
        return new File(FILE_PATH).exists();
    }
}