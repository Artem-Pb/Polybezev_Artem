#include "s21_string.h"

#include <stdlib.h>
int s21_strlen(const char *data) {
    if (data == NULL) {
        return 0;
    }

    const char *str = data;
    while (*str != '\0') {
        str++;
    }
    return str - data;
}

int s21_strcmp(const char *data, const char *data1) {
    if (data == NULL && data1 == NULL) return 0;
    if (data == NULL) return -1;
    if (data1 == NULL) return 1;

    int i = 0;
    while (data[i] != '\0' && data1[i] != '\0') {
        if ((unsigned char)data[i] != (unsigned char)data1[i]) {
            return (unsigned char)data[i] - (unsigned char)data1[i];
        }
        i++;
    }

    return (unsigned char)data[i] - (unsigned char)data1[i];
}

char *s21_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return dest;
}

char *s21_strcat(char *dest, const char *src) {
    int i = 0;
    while (dest[i] != '\0') {
        i++;
    }
    int j = 0;
    while (src[j] != '\0') {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
    char ch = (char)c;

    while (*str != '\0') {
        if (*str == ch) {
            return (char *)str;
        }
        str++;
    }
    if (ch == '\0') {
        return (char *)str;
    }

    return NULL;
}

char *s21_strstr(const char *str1, const char *str2) {
    if (!*str2) {
        return (char *)str1;
    }

    for (; *str1 != '\0'; str1++) {
        const char *ch = str1;
        const char *ch1 = str2;

        while (*ch && *ch1 && (*ch == *ch1)) {
            ch++;
            ch1++;
        }

        if (*ch1 == '\0') return (char *)str1;
    }

    return NULL;
}

char *s21_strtok(char *str, const char *delim) {
    static char *next = NULL;
    if (str != NULL) {
        next = str;
    }
    if (next == NULL) {
        return NULL;
    }

    while (*next && s21_strchr(delim, *next)) {
        next++;
    }

    if (*next == '\0') {
        next = NULL;
        return NULL;
    }

    char *start = next;

    while (*next && !s21_strchr(delim, *next)) {
        next++;
    }

    if (*next) {
        *next = '\0';
        next++;
    } else {
        next = NULL;
    }

    return start;
}