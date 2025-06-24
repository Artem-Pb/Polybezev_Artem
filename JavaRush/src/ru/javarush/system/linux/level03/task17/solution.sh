#!/bin/zsh

# Сохраняем имя файла из аргумента
file_name="$1"

# Проверка существования файла
if [ -f $file_name ]; then
  echo "Файл $file_name существует."
else
  echo "Файл $file_name не найден."
fi