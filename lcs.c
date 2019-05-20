#include "lcs.h"

char* derive_sequence(char* str_a, char* str_b, int i, int j, char sym) {
    char* str = (char*) malloc(sizeof(char)*MAXLINE);

    while (i != 0 && j != 0) {
        if (symbol_matrix[i][j] == 's') {
            if (sym == '=') {
                sprintf(str + strlen(str), "%c: %c\n", sym, str_a[i]);
            }
            --i;
            --j;
        } else if (symbol_matrix[i][j] == 'j') {
            --j;
        } else {
            if (sym == '<' || sym == '>') {
                sprintf(str + strlen(str), "%c: %c\n", sym, str_a[i]);
            }
            --i;
        }
    }
    return str;
}

char* lcs(char* str_a, char* str_b, char sym) {
    int i, j;
    int len_a, len_b;
    len_a = strlen(str_a);
    len_b = strlen(str_b);
    i = 1;
    j = 1;
    while (i < len_a) {
        j = 1;
        while (j < len_b) {
            if (str_a[i] == str_b[j]) {
                count_matrix[i][j] = count_matrix[i-1][j-1] + 1;
                symbol_matrix[i][j] = 's';
            } else if (count_matrix[i][j-1] > count_matrix[i-1][j]) {
                count_matrix[i][j] = count_matrix[i][j-1];
                symbol_matrix[i][j] = 'j';
            } else {
                count_matrix[i][j] = count_matrix[i-1][j];
                symbol_matrix[i][j] = 'i';
            }
            ++j;
        }
        ++i;
    }
    return derive_sequence(str_a, str_b, len_a-1, len_b-1, sym);
}
    //printf("%s\n", lcs(" ABCDEFG", " ABCDFF", '<'));
    //printf("%s\n", lcs(" ABCDFF", " ABCDEFG", '='));
    //printf("%s\n", lcs(" ABCDFF", " ABCDEFG", '>'));
