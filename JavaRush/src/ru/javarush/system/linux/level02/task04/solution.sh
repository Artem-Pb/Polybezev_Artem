# Устанавливаем маску доступа 0022
umask 0022

# Создаем директорию task4_dir
mkdir task4_dir

# Создаем файл task4.txt внутри директории task4_dir
echo "File to test" > task4_dir/task4.txt

# Устанавливаем права доступа для task4.txt
# Владельцу - чтение и выполнение (rx), группе - выполнение (x), остальным - чтение (r)
chmod 544 task4_dir/task4.txt

# Смена владельца файла task4.txt на root и группы на sudo
sudo chown root:sudo task4_dir/task4.txt

# Проверяем права доступа, владельца и группу файла task4.txt
ls -l task4_dir/task4.txt