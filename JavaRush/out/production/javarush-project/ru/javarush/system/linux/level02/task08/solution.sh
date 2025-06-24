# Устанавливаем новый пароль для пользователя developer
passwd developer

# Принуждаем пользователя сменить пароль при следующем входе
passwd -e developer

# Проверяем параметры пользователя
chage -l developer