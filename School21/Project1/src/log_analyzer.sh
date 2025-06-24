#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Используется меньше или больше  1 агрумента. нужно всего 1"
	exit 1
fi 

fileName="$1"

if [ ! -f "$fileName" ]; then 
	echo "Ошибка: Файл '$fileName' не найден!"
	exit 1
fi 

if [ ! -s "$fileName" ]; then 
	echo "Файл '$fileName' пустой!"
	exit 1
fi

countStr=$(wc -l < "$fileName")
uniqCount=$(cut -d'-' -f1 "$fileName" | sort | uniq | wc -l)
changeCount=$(awk -F'-' '{print $(NF-1)}' "$fileName" | sort | uniq | wc -l)
result="$countStr $uniqCount $changeCount"
echo "$result" 
exit 0
