#include "s21_grep.h"

//  OUTPUT
void print_result(opts_t opts, file_t *file, line_t *line, result_t *res) {
    if (res->match > 0 && !opts.v && !opts.c && !opts.l) {
        if (opts.o) {
            print_line_number(opts, line);
            for (int i = 0; i < res->match; i++) {
                if ((line->cur_line + res->start[i])[0] != '\n')
                    printf("%.*s\n", (res->finish[i] - res->start[i]), (line->cur_line + res->start[i]));
            }
        } else {
            if (line->cur_line != NULL) print_line(opts, file, line);
        }
    }
    if (res->match == 0 && opts.v && !opts.c && !opts.l) print_line(opts, file, line);
}

void print_filename(opts_t opts, file_t *file) {
    if (file->show && !opts.h) printf("%s:", file->name);
}

void print_line_number(opts_t opts, line_t *line) {
    if (opts.n) printf("%d:", line->number);
}

void print_line(opts_t opts, file_t *file, line_t *line) {
    if (line->cur_line != NULL) {
        print_filename(opts, file);
        print_line_number(opts, line);
        printf("%s", line->cur_line);
    }
}

void print_count(opts_t opts, file_t *file) {
    if (opts.c && !opts.v) {
        print_filename(opts, file);
        if (opts.l && file->found_lines > 0)
            printf("1\n");
        else
            printf("%d\n", file->found_lines);
    }
    if (opts.c && opts.v) {
        print_filename(opts, file);
        if (opts.l)
            printf("1\n");
        else
            printf("%d\n", file->not_found_lines);
    }
    if (opts.l && file->found_lines > 0) printf("%s\n", file->name);
    if (opts.l && opts.v && file->found_lines == 0) printf("%s\n", file->name);
}

void print_usage() {
    printf("usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n");
    printf("\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
    printf("\t[--context[=num]] [--directories=action] [--label] [--line-buffered]\n");
    printf("\t[--null] [pattern] [file ...]\n");
}
