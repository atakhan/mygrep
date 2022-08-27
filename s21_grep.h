#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <sys/types.h>

#define MAX_ARGS 20
#define PARSE_INIT {0, 0, 0}
#define OPTIONS_INIT {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define LINE_INIT {NULL, 0, 1}
#define FILE_INIT {0, NULL, 0, 0, 0}
#define RESULT_INIT {0, {}, {}}

// parsing struct
typedef struct parse {
    char val;
    int next;
    int act;
} parse_t;

typedef struct options {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} opts_t;

typedef struct line {
    char *cur_line;
    size_t offset;
    int number;
} line_t;

typedef struct file {
    int show;
    char *name;
    int lines_count;
    int found_lines;
    int not_found_lines;
} file_t;

typedef struct search_result {
    int match;
    int start[64];
    int finish[64];
} result_t;

// -- PROCESSING
void process(int argc, char *argv[], char *v, opts_t o);
int count_type(const char *values, char c);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

// s21_grep_errors.c -- ETC
void l_check_files(int argc, char *argv[], const char *values);
void check_errors(int argc, const char *values, char *argv[], opts_t opts);
void check_file_isset(char *filename, opts_t opts);
void check_regex_errors(char *pattern);

// s21_grep_parse.c -- PARSE FUNCTIONS
void parse(char *values, int argc, char *argv[], parse_t *exp, opts_t *opts);
parse_t parseOpts(char *arg, parse_t exp, opts_t *opts);
parse_t isPattern(const char *arg, parse_t exp, const char *n_arg, int i);
parse_t isFile(const char *arg, parse_t exp);
int getOpt(char *c, parse_t *exp, int i, opts_t *opts);
int isLast(char *arg, char c);

// -- SEARCH PATTERNS
void search_patterns(const char *v, int argc, char *argv[], opts_t o, file_t *f, line_t *l, result_t *r);
void pattern_s(char *arg, opts_t o, file_t *f, line_t *l, result_t *r);
void pattern_f(char *arg, opts_t o, file_t *f, line_t *l, result_t *r);
void search(char *pattern, opts_t o, file_t *f, line_t *l, result_t *r);
void reg_search(char *pattern, opts_t o, file_t *f, line_t *l, result_t *r);
void reg_compile(regex_t *regex, char *pattern, int cflags);
int regex_match(char *pattern, opts_t opts, file_t file, line_t *line, result_t *result);


// s21_grep_output.c -- OUTPUT
void print_result(opts_t o, file_t *f, line_t *l, result_t *r);
void print_filename(opts_t o, file_t *f);
void print_line(opts_t o, file_t *f, line_t *l);
void print_line_number(opts_t o, line_t *l);
void print_count(opts_t o, file_t *f);
void print_usage();

#endif  // SRC_GREP_S21_GREP_H_
