# Создание группы "developers"
sudo groupadd developers

# Добавление пользователей `user1` и `user2` в группу "developers"
sudo usermod -aG developers user1
sudo usermod -aG developers user2

# Проверка, что пользователи добавлены в группу "developers"
echo "Группы для user1:"
groups user1

echo "Группы для user2:"
groups user2