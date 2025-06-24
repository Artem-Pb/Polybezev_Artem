# Установка веб-сервера nginx
sudo apt update
sudo apt install -y nginx

# Запуск службы nginx
sudo systemctl start nginx

# Перезапуск службы nginx
sudo systemctl restart nginx

# Проверка статуса службы nginx
sudo systemctl status nginx

# Отключение автозапуска службы nginx
sudo systemctl disable nginx

# Проверка, что автозапуск службы nginx отключён
systemctl is-enabled nginx