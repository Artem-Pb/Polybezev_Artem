# Создание файла task1.txt
touch task1.txt

# Установка прав доступа:
# - Полные права для владельца (rwx)
# - Только чтение для группы (r--), остальные без прав доступа (---)
chmod u+rwx task1.txt
chmod g+r task1.txt
chmod o-rwx task1.txt
# Проверка прав доступа файла
ls -l task1.txt