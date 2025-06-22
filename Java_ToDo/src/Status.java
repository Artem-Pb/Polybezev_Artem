public enum Status {
    NOT_STARTED("Не начата"),
    IN_PROGRESS("В процессе"),
    COMPLETED("Завершена");

    private final String displayName;

    Status(String displayName) {
        this.displayName = displayName;
    }

    public String getDisplayName() {
        return displayName;
    }

    public boolean isCompleted() {
        return this == COMPLETED;
    }
}
