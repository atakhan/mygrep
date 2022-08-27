#include "s21_grep.h"

void search_patterns(const char *v, int argc, char *argv[], opts_t o, file_t *f, line_t *l, result_t *r) {
    for (int i = 1; i < argc; i++) {
        if (v[i-1] == '2' && argv[i][0] == '-') pattern_s(argv[i], o, f, l, r);
        if (v[i-1] == '3') search(argv[i], o, f, l, r);
        if (v[i-1] == '4') pattern_f(argv[i], o, f, l, r);
    }
    if (r->match) {
        f->found_lines++;
        f->lines_count++;
    } else {
        f->not_found_lines++;
    }
}

void pattern_s(char *arg, opts_t opts, file_t *file, line_t *line, result_t *result) {
    size_t ptr_len = 0, ptr2_len = 0;
    char *ptr = NULL, *ptr2 = NULL;
    if ((ptr = strchr(arg, 'e')) != NULL ) ptr_len = strlen(ptr);
    if ((ptr2 = strchr(arg, 'f')) != NULL ) ptr2_len = strlen(ptr2);
    if (ptr2_len > ptr_len) pattern_f((ptr2 + 1), opts, file, line, result);
    if (ptr_len > ptr2_len) search((ptr + 1), opts, file, line, result);
}

void pattern_f(char *p_fn, opts_t opts, file_t *file, line_t *line, result_t *result) {
    FILE *fp = fopen(p_fn, "r");
    if (fp == NULL && !opts.s) {
        printf("grep: %s: No such file or directory\n", p_fn);
        exit(0);
    }
    char *p_line = NULL;
    size_t len = 0;
    while (getline(&p_line, &len, fp) > 0) search(p_line, opts, file, line, result);
    fclose(fp);
    free(p_line);
}

void search(char *pattern, opts_t opts, file_t *file, line_t *line, result_t *result) {
    pattern[strcspn(pattern, "\n")] = 0;  // trim \n
    reg_search(pattern, opts, file, line, result);
}

void reg_compile(regex_t *regex, char *pattern, int cflags) {
    int regcomp_result = regcomp(regex, pattern, cflags);
    if (regcomp_result != 0) {
        char buffer[100];
        regerror(regcomp_result, regex, buffer, 100);
        printf("grep: %s\n", buffer);
        exit(1);
    }
}

void reg_search(char *pattern, opts_t opts, file_t *file, line_t *line, result_t *result) {
    (void)file;
    regex_t regex;
    regmatch_t rm[20];
    int n_match = 20;
    int cflags = (opts.i == 1) ? REG_ICASE : 0;
    char * p = line->cur_line;
    reg_compile(&regex, pattern, cflags);
    if (strlen(p) > line->offset) p += line->offset;
    while (1) {
        int no_match = regexec(&regex, p, n_match, rm, 0);
        if (no_match) break;
        for (int i = 0; i < n_match; i++) {
            if (rm[i].rm_so == -1) break;
            result->start[result->match] = rm[i].rm_so + (p - line->cur_line);
            result->finish[result->match] = rm[i].rm_eo + (p - line->cur_line);
        }
        result->match += 1;
        if (rm[0].rm_eo > (int)line->offset) line->offset = rm[0].rm_eo;
        p += rm[0].rm_eo;
    }
    regfree(&regex);
}
