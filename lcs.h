#ifndef lcs_h
#define lcs_h

#define MAXLINE 256

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_matrix[MAXLINE][MAXLINE];
char symbol_matrix[MAXLINE][MAXLINE];

char* derive_sequence(char* str_a[MAXLINE], char* str_b[MAXLINE], int i, int j, char sym);
char* lcs(char* str_a[MAXLINE], char* str_b[MAXLINE], char sym, int len_a, int len_b);

#endif
