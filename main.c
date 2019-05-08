#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFSIZE 256
#define FILE_BUFSIZE 10

void print_filebuf();
int getline_(char* line, int max);
char* fgets(char* s, int n, FILE* iop);
int fputs_(char* s, FILE* iop);
FILE* open_file(char* name, char* mode);
void read_lines(char** file_buf, int file_buf_size, char* line_buf, int line_buf_size, FILE* file);

char* lhs_file_buf[FILE_BUFSIZE];                           // storage for left input file
char* rhs_file_buf[FILE_BUFSIZE];                           // storage for right input file

int main(int argc, const char* argv[]) {
    char lhs_line_buf[LINE_BUFSIZE], rhs_line_buf[LINE_BUFSIZE];  // storage for individual lines
    memset(lhs_line_buf, '\0', LINE_BUFSIZE - 1);
    memset(rhs_line_buf, '\0', LINE_BUFSIZE - 1);
    FILE* lhs_fp;                                       // storage for 
    FILE* rhs_fp;
    lhs_fp = open_file("left.txt", "r");
    rhs_fp = open_file("right.txt", "r");
    read_lines(lhs_file_buf, FILE_BUFSIZE, lhs_line_buf, LINE_BUFSIZE, lhs_fp);
    read_lines(rhs_file_buf, FILE_BUFSIZE, rhs_line_buf, LINE_BUFSIZE, rhs_fp);
    print_filebuf(lhs_file_buf, FILE_BUFSIZE);
    printf("--------------------------------\n");
    print_filebuf(rhs_file_buf, FILE_BUFSIZE);
    fclose(lhs_fp);
    fclose(rhs_fp);
    return EXIT_SUCCESS;
}

void read_lines(char** file_buf, int file_buf_size, char* line_buf, int line_buf_size, FILE* file) {
    char** pend = file_buf + file_buf_size; 
    char** pstart = file_buf;
    while (pstart < pend && fgets(line_buf, line_buf_size, file) != NULL) {
        *pstart++ = strdup(line_buf);
    }
}

void print_filebuf(char** file_buf, int file_buf_size) {
    char** pend = file_buf + file_buf_size;
    char** pstart = file_buf;
    int i = 1;
    while (pstart < pend && *pstart != NULL) {
        if (strlen(*pstart) == 0) {
            printf("%d: \n", i);
        } else {
            printf("%d: %s", i, *pstart);
        }
        ++i;
        ++pstart;
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
    while (--n > 1 && (c = getc(iop)) != EOF) {
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
