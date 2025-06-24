#!/bin/bash

# Добавление задания в crontab для выполнения скрипта ежедневно в 01:00
(crontab -l <2/dev/null; echo "0 1 * * * backup.sh") | crontab -