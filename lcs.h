#ifndef lcs_h
#define lcs_h

#define MAXLINE 128

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_matrix[MAXLINE][MAXLINE];
char symbol_matrix[MAXLINE][MAXLINE];

char* derive_sequence(char* str_a, char* str_b, int i, int j, char sym);
char* lcs(char* str_a, char* str_b, char sym);

#endif
