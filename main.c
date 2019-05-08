#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFSIZE 256
#define PARA_BUFSIZE 256
#define FILE_BUFSIZE 10

struct file_buf {
    char* buf[FILE_BUFSIZE];
    int pos;
};

void print_filebuf();
int getline_(char* line, int max);
char* fgets(char* s, int n, FILE* iop);
int fputs_(char* s, FILE* iop);
FILE* open_file(char* name, char* mode);
void read_lines(char** file_buf, int file_buf_size, char* line_buf, int line_buf_size, FILE* file);
char* para_read(FILE* file);
void para_add(char* para_buf, struct file_buf* fbuf);
char* strdup_nullcheck(char* s);


struct file_buf lhs_file_buf;
struct file_buf rhs_file_buf;

int main(int argc, const char* argv[]) {
    struct file_buf lhs_buf;
    struct file_buf rhs_buf;
    char lhs_line_buf[LINE_BUFSIZE], rhs_line_buf[LINE_BUFSIZE];  // storage for individual lines
    memset(lhs_line_buf, '\0', LINE_BUFSIZE - 1);
    memset(rhs_line_buf, '\0', LINE_BUFSIZE - 1);
    FILE* lhs_fp;                                                 // left file pointer
    FILE* rhs_fp;                                                 // right file pointer
    lhs_fp = open_file("left.txt", "r");
    rhs_fp = open_file("right.txt", "r");
    char* para = NULL;
    while ((para = para_read(lhs_fp)) != NULL) {
        para_add(para, &lhs_file_buf);
    }
    while ((para = para_read(rhs_fp)) != NULL) {
        para_add(para, &rhs_file_buf);
    }


    //read_lines(lhs_file_buf, FILE_BUFSIZE, lhs_line_buf, LINE_BUFSIZE, lhs_fp);
    //read_lines(rhs_file_buf, FILE_BUFSIZE, rhs_line_buf, LINE_BUFSIZE, rhs_fp);
    print_filebuf(&lhs_file_buf);
    printf("--------------------------------\n");
    print_filebuf(&rhs_file_buf);
    fclose(lhs_fp);
    fclose(rhs_fp);
    return EXIT_SUCCESS;
}

char* para_read(FILE* file) {
    char para_buf[PARA_BUFSIZE];
    char line_buf[LINE_BUFSIZE];
    memset(para_buf, '\0', PARA_BUFSIZE - 1);
    memset(line_buf, '\0', LINE_BUFSIZE - 1);
    while (fgets(line_buf, LINE_BUFSIZE, file) != NULL) {
        strcat(para_buf, line_buf);
        if (strlen(line_buf) == 1 && *line_buf == '\n') {
            return strdup_nullcheck(para_buf);
        }
    }
    return strdup_nullcheck(para_buf);
}

void para_add(char* para_buf, struct file_buf* fbuf) {
    if (fbuf->pos < FILE_BUFSIZE) {
        fbuf->buf[fbuf->pos++] = para_buf;
    } else {
        fprintf(stderr, "file buffer is full\n");
    }
}

char* strdup_nullcheck(char* s) {
    if (s == NULL || *s == '\0') {
        return NULL;
    } else {
        return strdup(s);
    }
}

void read_lines(char** file_buf, int file_buf_size, char* line_buf, int line_buf_size, FILE* file) {
    char** pend = file_buf + file_buf_size; 
    char** pstart = file_buf;
    while (pstart < pend && fgets(line_buf, line_buf_size, file) != NULL) {
        *pstart++ = strdup(line_buf);
    }
}

void print_filebuf(struct file_buf* file_buf, int file_buf_size) {
    char** pend = file_buf->buf + FILE_BUFSIZE;
    char** pstart = file_buf->buf;
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
