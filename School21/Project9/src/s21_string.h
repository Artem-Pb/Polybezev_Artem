#ifndef STR_LEN_H
#define STR_LEN_H

#include <stdio.h>
int s21_strlen(const char *data);
int s21_strcmp(const char *data, const char *data1);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *destination, const char *source);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *str1, const char *str2);
char *s21_strtok(char *str, const char *delim);
#endif