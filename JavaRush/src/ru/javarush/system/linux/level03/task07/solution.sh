# Вывод логов сервиса `cron` за последние 24 часа и поиск строк с ключевым словом `ERROR`
sudo journalctl -u cron --since "24 hour ago"  | grep "ERROR"