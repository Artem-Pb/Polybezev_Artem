# Устанавливаем пакет cron
sudo apt-get update
sudo apt-get install -y cron

# Запускаем службу cron
sudo systemctl start cron

# Останавливаем службу cron
sudo systemctl stop cron

# Проверяем статус службы cron
sudo systemctl status cron