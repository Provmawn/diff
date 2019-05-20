#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFSIZE 256
#define PARA_BUFSIZE 256
#define FILE_BUFSIZE 10

#define HASHSIZE 200

#include "lcs.h"


struct para {
    char* line_buf[LINE_BUFSIZE];
    int pos;
    int print_flag;
};

struct file_buf {
    struct para* para[PARA_BUFSIZE];
    int pos;
    int print_flag;
};

int getline_(char* line, int max);
char* fgets(char* s, int n, FILE* iop);
int fputs_(char* s, FILE* iop);
FILE* open_file(char* name, char* mode);
void read_lines(char** file_buf, int file_buf_size, char* line_buf, int line_buf_size, FILE* file);
char* para_read(FILE* file);
void file_buf_add(struct file_buf* fbuf, struct para* para);
void para_compare(struct file_buf* lhs, struct file_buf* rhs);
void file_buf_add_both(char* para_buf, struct file_buf* fbuf);
void para_add_line(char* line, struct para* para);
struct para* para_create(char* para); 
void para_print(struct para* para);
void para_printright(struct para* para);
void para_printleft(struct para* para);
void para_printboth(struct para* para);
int para_match(struct para* lhs, struct para* rhs);
char* strdup_nullcheck(char* s);

unsigned int hash(char* s);

struct file_buf lhs_file_buf;
struct file_buf rhs_file_buf;
struct file_buf diff_buf;

int main(int argc, const char* argv[]) {
    ++argv;
    int c;
    while (argc > 1) {
        if (**argv == '-') {
            //c = hash(*argv);
            printf("%s\n", *argv);
        } else {
            printf("Invalid arg.\n");
        }
        ++argv;
        --argc;
    }
    char lhs_line_buf[LINE_BUFSIZE], rhs_line_buf[LINE_BUFSIZE];  // storage for individual lines
    memset(lhs_line_buf, '\0', LINE_BUFSIZE - 1);
    memset(rhs_line_buf, '\0', LINE_BUFSIZE - 1);
    FILE* lhs_fp;                                                 // left file pointer
    FILE* rhs_fp;                                                 // right file pointer
    lhs_fp = open_file("left.txt", "r");
    rhs_fp = open_file("right.txt", "r");

    char* para = NULL;
    while ((para = para_read(lhs_fp)) != NULL) {
        file_buf_add(&lhs_file_buf, para_create(para));
    }
    printf("--------------------------------\n");
    while ((para = para_read(rhs_fp)) != NULL) {
        file_buf_add(&rhs_file_buf, para_create(para));
    }
    para_compare(&lhs_file_buf, &rhs_file_buf);
    /*
    char* para = NULL;
    while ((para = para_read(lhs_fp)) != NULL) {
        file_buf_add(para, &lhs_file_buf);
    }
    while ((para = para_read(rhs_fp)) != NULL) {
        file_buf_add(para, &rhs_file_buf);
    }
    */
    //para_compare(&lhs_file_buf, &rhs_file_buf);
    //read_lines(lhs_file_buf, FILE_BUFSIZE, lhs_line_buf, LINE_BUFSIZE, lhs_fp);
    //read_lines(rhs_file_buf, FILE_BUFSIZE, rhs_line_buf, LINE_BUFSIZE, rhs_fp);
    //print_filebuf(&lhs_file_buf);
    //print_filebuf(&diff_buf);
    printf("--------------------------------\n");
    //print_filebuf(&rhs_file_buf);
    fclose(lhs_fp);
    fclose(rhs_fp);
    return EXIT_SUCCESS;
}

unsigned int hash(char* s) {
    unsigned int hashval;
    hashval = 0;
    while (*s != '\0') {
        hashval = *s + 31 * hashval;
        ++s;
    }
    return hashval % HASHSIZE;
}

struct para* para_create(char* para) {
    struct para* p = (struct para*) malloc(sizeof(struct para));
    p->pos = 0;
    char* line_start = para;
    char* line_pos = para;
    while (*line_pos != '\0') {
        if (*line_pos == '\n' && *(line_pos + 1) != '\n') {
            *line_pos = '\0';
            para_add_line(line_start, p);
            ++line_pos;
            line_start = line_pos;
        }
        ++line_pos;
    }
    return p;
}

void para_print(struct para* para) {
    int i = 0;
    while (i < para->pos) {
        printf("%s\n", para->line_buf[i++]);
    }
}

void para_add_line(char* line, struct para* para) {
    para->line_buf[para->pos++] = line;
}

void para_compare(struct file_buf* lhs, struct file_buf* rhs) {
    int lhs_para_i, rhs_para_i;
    lhs_para_i = rhs_para_i = 0;
    while (lhs_para_i < lhs->pos) {
        para_printboth(lhs->para[lhs_para_i]);
        ++lhs_para_i;
    }

    while (lhs_para_i < lhs->pos) {
        \
    }
}

int para_match(struct para* lhs, struct para* rhs) {
        int compare;
        int lhs_line_i, rhs_line_i;
        lhs_line_i = rhs_line_i = 0;
        while (lhs_line_i < lhs->pos && rhs_line_i < rhs->pos) {
            compare = strcmp(lhs->line_buf[lhs_line_i], rhs->line_buf[rhs_line_i]);
            if (compare != 0) {
                break;
            }
            ++lhs_line_i;
            ++rhs_line_i;
        }
        return compare;
}

void para_printboth(struct para* para) {
    if (para == NULL) {
        return;
    }
    int i = 0;
    while (i < para->pos) {
        printf("%-60s %s\n", para->line_buf[i], para->line_buf[i]);
        ++i;
    }
}

void para_printright(struct para* para) {
    int i = 0;
    while (i < para->pos) {
        printf("%60s\n", para->line_buf[i]);
        ++i;
    }
}

void para_printleft(struct para* para) {
    int i = 0;
    while (i < para->pos) {
        printf("%s\n", para->line_buf[i]);
        ++i;
    }
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

void file_buf_add_both(char* para_buf, struct file_buf* fbuf) {
    
}

void file_buf_add(struct file_buf* fbuf, struct para* para) {
    if (fbuf->pos < FILE_BUFSIZE) {
        fbuf->para[fbuf->pos++] = para;
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

void print_filebuf(struct file_buf* file_buf) {
    int para_i = 0;
    int line_i;
    while (para_i < file_buf->pos) {
        line_i = 0;
        while (line_i < file_buf->para[para_i]->pos) {
            if (strlen(file_buf->para[para_i]->line_buf[line_i]) == 0) {
                printf("\n");
            } else {
                printf("%s\n", file_buf->para[para_i]->line_buf[line_i]);
            }
            ++line_i;
        }
        ++para_i;
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
