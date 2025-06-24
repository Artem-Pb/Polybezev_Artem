#!/bin/bash

if [ "$#" -ne 3 ]; then 
	echo "Используйте 3 аргумента"
	exit 1
fi 

fileName="$1"
oldStr="$2"
newStr="$3"

if [ ! -f "$fileName" ]; then 
	echo "Ошибка: файл '$fileName' не найден!"
       exit 1
fi

if [ ! -s "$fileName" ]; then 
	echo "Ошибка: файл '$fileName' пустой!"
	exit 1
fi 
 

sed -i "s/$oldStr/$newStr/g" $fileName

fileLog=/src/files.log

if [  -f "$fileLog" ]; then
	echo "Ошибка! Файл '$fileLog' не найден!"
	exit 1
fi

fullPath="src/${fileName}"
fileSize=$(stat --format="%s" "$fileName")
modDate=$(stat --format="%y" "$fileName" | cut -d':' -f1,2)
fileHash=$(sha256sum "$fileName" | awk '{print $1}')

result="$fullPath - $fileSize - $modDate - $fileHash - sha256"
echo "$result" >> files.log
exit 0
