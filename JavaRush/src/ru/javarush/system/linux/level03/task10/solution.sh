# Выводим список всех доступных временных зон
timedatectl list-timezones

# Определяем временную зону для города Нью-Йорк
# Используем фильтрацию вывода команды для нахождения нужной временной зоны
sudo timedatectl list-timezones | grep -w "America/New_York"