import java.util.concurrent.atomic.AtomicInteger;

/**
 * Потокобезопасный генератор ID для задач.
 */
public final class TaskIdGenerator {
    private static final AtomicInteger counter = new AtomicInteger(0);

    private TaskIdGenerator() {}

    public static int generateId() {
        int newId = counter.incrementAndGet();
        if (newId <= 0) {
            throw new IllegalStateException("ID должен быть положительным");
        }
        return newId;
    }
}