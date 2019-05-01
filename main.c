#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

void print_filebuf();
int getline_(char* line, int max);
char* fgets(char* s, int n, FILE* iop);
int fputs_(char* s, FILE* iop);
FILE* open_file(char* name, char* mode);

char* file_buf1[BUFSIZE];
char* file_buf2[BUFSIZE];

int main(int argc, const char* argv[]) {
    char buf1[BUFSIZE], buf2[BUFSIZE];
    memset(buf1, '\0', BUFSIZE - 1);
    memset(buf2, '\0', BUFSIZE - 1);
    FILE* fp1;
    FILE* fp2;
    fp1 = open_file("a.txt", "r");
    fp2 = open_file("b.txt", "r");
    int comp;
    int i = 0;
    while (fgets(buf1, BUFSIZE - 1 , fp1) != NULL || fgets(buf2, BUFSIZE - 1, fp2) != NULL) {
        if ((comp = strcmp(buf1, buf2)) != 0) {
            file_buf1[i] = malloc(sizeof(buf1));
            strcpy(file_buf1[i], buf1);
            file_buf2[i] = malloc(sizeof(buf2));
            strcpy(file_buf2[i], buf2); 
            ++i;
        }
    }
    print_filebuf();
    fclose(fp1);
    fclose(fp2);
    return EXIT_SUCCESS;
}

void print_filebuf() {
    int i = 0;
    while (file_buf1[i] != '\0') {
        printf("<%s", file_buf1[i]);
        ++i;
    }
    i = 0;
    while (file_buf2[i] != '\0') {
        printf(">%s", file_buf2[i]);
        ++i;
    }
}

int getline_(char* line, int max) {
    if (fgets(line, max, stdin) == NULL) {
        return 0;
    }
    return strlen(line);
}

char* fgets(char* s, int n, FILE* iop) {
    register int c;
    register char* cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF) {
        if ((*cs++ = c) == '\n') {
            break;
        }
    }
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

int fputs_(char* s, FILE* iop) {
    int c;
    while ((c = *s++) != EOF) {
        putc(c, iop);
    }
    return ferror(iop) ? EOF : 0;
}

FILE* open_file(char* name, char* mode) {
    FILE* fp;
    if ((fp = fopen(name, mode)) == NULL) {
        fprintf(stderr, "%s\n", "open_file: could not open file");
        exit(1);
    }
    return fp;
}
