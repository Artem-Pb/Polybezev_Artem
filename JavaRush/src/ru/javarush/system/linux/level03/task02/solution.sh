# Проверка статуса службы 'cron'
sudo systemctl status cron

# Включение автозапуска для службы 'cron'
sudo systemctl enable cron

# Проверка, включён ли автозапуск для службы 'cron'
systemctl is-enabled cron