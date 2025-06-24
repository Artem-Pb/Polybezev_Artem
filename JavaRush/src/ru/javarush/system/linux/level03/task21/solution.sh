# Добавление задачи в crontab для записи текущей даты и времени в файл ~/task1.log каждые 2 минуты
(crontab -l 2>/dev/null; echo "*/2 * * * * date > ~/task1.log") | crontab -
(crontab -l 2>/dev/null; echo "*/2 * * * * date > ~/task1.log") | crontab -