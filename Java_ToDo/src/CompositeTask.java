import java.util.List;

/**
 * Интерфейс для составных задач с подзадачами и заголовком.
 */
public interface CompositeTask extends Task {
    String getTitle();
    void setTitle(String title);

    List<Task> getSubTasks();
    void addSubTask(Task task);
    void removeSubTask(int id);

    default boolean hasSubTasks() {
        return !getSubTasks().isEmpty();
    }
}