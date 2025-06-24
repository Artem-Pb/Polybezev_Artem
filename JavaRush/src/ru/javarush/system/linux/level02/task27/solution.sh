# Создаём файл project.txt в домашней директории пользователя user1
sudo -u user1 touch /home/user1/project.txt

# Меняем владельца файла на пользователя user1, а группу на developers
sudo chown user1:developers /home/user1/project.txt

# Устанавливаем права доступа: только владелец и члены группы могут читать и записывать файл
sudo chmod 660 /home/user1/project.txt

# Проверяем итоговые права доступа на файл
ls -l /home/user1/project.txt