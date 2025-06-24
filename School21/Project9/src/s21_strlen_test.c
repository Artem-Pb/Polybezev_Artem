#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void s21_strlen_test(const char *data, int len_exe);
void s21_strcmp_test(const char *data, const char *data1, int test);
void s21_strcpy_test(const char *src);
void s21_strcat_test(const char *dest, const char *src, const char *final);
void s21_strchr_test(const char *src, int c, const char *search);
void s21_strstr_test(const char *str1, const char *str2, const char *final);
void s21_strtok_test(char *input, const char *delim, const char *expected_tokens[], int expected_count);

int main() {
#ifdef STRLEN
    const char *test_1 = "HELLLO";
    const char *test_2 = "544533";
    const char *test_3 = "";
    const char *test_4 = NULL;
    const char *test_5 = "\n";
    s21_strlen_test(test_1, 6);
    printf("\n");
    s21_strlen_test(test_2, 6);
    printf("\n");
    s21_strlen_test(test_3, 0);
    printf("\n");
    s21_strlen_test(test_4, 0);
    printf("\n");
    s21_strlen_test(test_5, 1);
#elif STRCMP
    const char *test_cmp1 = "HELLLO";
    const char *test_cmp2 = "Game_of_Life";
    const char *test_cmp3 = "ananas";
    const char *test_cmp4 = NULL;
    const char *test_cmp5 = "appricote";
    const char *test_cmp6 = "apple";
    s21_strcmp_test(test_cmp1, test_cmp2, 1);
    printf("\n");
    s21_strcmp_test(test_cmp3, test_cmp4, 0);
    printf("\n");
    s21_strcmp_test(test_cmp5, test_cmp6, 1);
#elif STRCPY
    const char *test_cpy1 = "ARTEM_Pb";
    const char *test_cpy2 = "ananas";
    const char *test_cpy3 = "KREVETKA";
    s21_strcpy_test(test_cpy1);
    printf("\n");
    s21_strcpy_test(test_cpy2);
    printf("\n");
    s21_strcpy_test(test_cpy3);
#elif STRCAT
    char test_dest1[100] = "HELLO, ";
    const char *test_src1 = "MY_FRIENDS";
    const char *final1 = "HELLO, MY_FRIENDS";
    char test_dest2[100] = "KUPI_";
    const char *test_src2 = "SLONA";
    const char *final2 = "KUPI_SLONA";
    char test_dest3[100] = "appricote ";
    const char *test_src3 = "apple";
    const char *final3 = "appricote apple";
    s21_strcat_test(test_dest1, test_src1, final1);
    printf("\n");
    s21_strcat_test(test_dest2, test_src2, final2);
    printf("\n");
    s21_strcat_test(test_dest3, test_src3, final3);
    printf("\n");
#elif STRCHR
    const char *test_chr1 = "ARTEM_Pb";
    const char *test_chr2 = "ARTEM_Pb";
    const char *test_chr3 = "ARTEM_Pb";
    s21_strchr_test(test_chr1, 'A', (char *)test_chr1);
    printf("\n");
    s21_strchr_test(test_chr2, 'z', NULL);
    printf("\n");
    s21_strchr_test(test_chr3, '\0', (char *)test_chr3 + s21_strlen(test_chr3));
#elif STRSTR
    const char *test_str1 = "MAKEFILE ROBIT";
    const char *test_str2 = "INOGDA NE ROBIT";
    const char *test_str3 = "READY_TO_GO";
    s21_strstr_test(test_str1, "ROBIT", "ROBIT");
    printf("\n");
    s21_strstr_test(test_str2, "A NE", "A NE ROBIT");
    printf("\n");
    s21_strstr_test(test_str3, "ZAROBIT", NULL);
#elif STRTOK
    char test_tok1[] = "MAKEFILE ROBIT";
    char test_tok2[] = "INOGDA, NE; ROBIT";
    char test_tok3[] = "READY_TO_GO";
    const char *delim = " ,;_";
    const char *expected_tokens1[] = {"MAKEFILE", "ROBIT"};
    const char *expected_tokens2[] = {"INOGDA", "NE", "ROBIT"};
    const char *expected_tokens3[] = {"READY", "TO", "GO"};
    s21_strtok_test(test_tok1, delim, expected_tokens1, 2);
    printf("\n");
    s21_strtok_test(test_tok2, delim, expected_tokens2, 3);
    printf("\n");
    s21_strtok_test(test_tok3, delim, expected_tokens3, 3);
    printf("\n");
#endif
    return 0;
}
void s21_strlen_test(const char *data, int len_exe) {
    if (data == NULL) {
        printf("NULL\n0\nFAIL");
        return;
    }

    int len = s21_strlen(data);

    printf("%s\n%d\n", data, len);

    if (len == len_exe) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strcmp_test(const char *data, const char *data1, int test) {
    if (data == NULL || data1 == NULL) {
        printf("NULL\n0\nFAIL");
        return;
    }
    int result = s21_strcmp(data, data1);
    int pass = 0;

    if (test == 0) {
        pass = (result == 0);
    } else if (test < 0) {
        pass = (result < 0);
    } else {
        pass = (result > 0);
    }

    printf("%s\n%s\n%d\n%s", data, data1, result, pass ? "SUCCESS" : "FAIL");
}

void s21_strcpy_test(const char *src) {
    if (src == NULL) {
        printf("NULL\n0\nFAIL");
        return;
    }

    int len_src = s21_strlen(src);
    char dest[len_src + 1];

    char *result = s21_strcpy(dest, src);

    if (result != dest) {
        printf("%s\n0\nFAIL", src);
        return;
    }

    int len_dest = s21_strlen(dest);

    int pass = (len_dest == len_src) && (s21_strcmp(dest, src) == 0);

    if (s21_strcmp(dest, src) != 0) {
        pass = 0;
    }

    printf("%s\n%s\n%s", src, dest, pass ? "SUCCESS" : "FAIL");
}

void s21_strcat_test(const char *dest, const char *src, const char *final) {
    char buff[100] = {0};

    s21_strcpy(buff, dest);
    char *result = s21_strcat(buff, src);
    if (result != buff) {
        printf("%s %s\n0\nFAIL", dest, src);
        return;
    }

    if (s21_strcmp(buff, final) != 0) {
        printf("%s %s\n0\nFAIL", dest, src);
        return;
    }

    size_t len_final = s21_strlen(final);
    size_t len_buff = s21_strlen(buff);
    if (len_final != len_buff) {
        printf("%s %s\n0\nFAIL", dest, src);
        return;
    }

    if (buff[len_buff] != '\0') {
        printf("%s %s\n0\nFAIL", dest, src);
        return;
    }

    printf("%s\n%s\n%s\n%s", dest, src, result, "SUCCESS");
}

void s21_strchr_test(const char *src, int c, const char *search) {
    char *result = s21_strchr(src, c);

    if (search == NULL) {
        if (result == NULL) {
            printf("%s\nNULL\nSUCCESS", src);
            return;
        } else {
            printf("%s\n%c\nFAIL", src, c);
            return;
        }
    } else {
        if (result == search) {
            printf("%s\n%c\nSUCCESS", src, c);
            return;
        } else {
            printf("%s\n%c\nFAIL", src, c);
            return;
        }
    }
}

void s21_strstr_test(const char *str1, const char *str2, const char *final) {
    char *result = s21_strstr(str1, str2);

    if (final == NULL) {
        if (result == NULL) {
            printf("%s\nNULL\nSUCCESS", str2);
            return;
        } else {
            printf("%s\n%s\nFAIL", str1, result);
            return;
        }
    } else {
        if (result != NULL && s21_strcmp(result, final) == 0) {
            printf("%s\n%s\nSUCCESS", str1, result);
            return;
        } else {
            printf("%s\n%s\nFAIL", str1, result);
            return;
        }
    }
}

void s21_strtok_test(char *input, const char *delim, const char *expected_tokens[], int expected_count) {
    int i = 0;
    char *token = s21_strtok(input, delim);

    while (token != NULL && i < expected_count) {
        if (s21_strcmp(token, expected_tokens[i]) == 0) {
            printf("%s\nNULL\nSUCCESS", input);
            return;
        } else {
            printf("%s\n%s\nFAIL", input, token);
            return;
        }
        token = s21_strtok(NULL, delim);
        i++;
    }

    if (token != NULL) {
        printf("%s\n%s\nFAIL", input, token);
        return;
    } else if (i < expected_count) {
        printf("%s\n%s\nFAIL", input, token);
        return;
    } else {
        printf("%s\n%s\nSUCCESS", input, token);
        return;
    }
    printf(" ");
}