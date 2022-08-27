#include "s21_grep.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
    }
    if (argc - 1 < MAX_ARGS) {
        parse_t parser = PARSE_INIT;
        opts_t opts = OPTIONS_INIT;
        char values[MAX_ARGS+1];
        parse(values, argc, argv, &parser, &opts);
        check_errors(argc, values, argv, opts);
        process(argc, argv, values, opts);
    } else {
        printf("Maximum %d arguments", MAX_ARGS);
    }
    return 0;
}

void process(int argc, char *argv[], char *values, opts_t opts) {
    file_t file = FILE_INIT;
    int filesCount = count_type(values, '5');
    if (filesCount > 1 && !opts.h) file.show = 1;
    for (int i = 1; i < argc; i++) {
        if (values[i-1] == '5') {
            file.name = argv[i];
            FILE *fp = fopen(file.name, "r");
            if (fp == NULL) {
                if (!opts.l && !opts.s) printf("grep: %s: No such file or directory\n", file.name);
                continue;
            }
            line_t line = LINE_INIT;
            char *text_line = NULL;
            size_t len = 0;
            while (getline(&text_line, &len, fp) > 0) {
                line.offset = 0;
                line.cur_line = text_line;
                result_t result = RESULT_INIT;
                search_patterns(values, argc, argv, opts, &file, &line, &result);
                print_result(opts, &file, &line, &result);
                line.number++;
            }

            print_count(opts, &file);
            file.found_lines = 0;
            file.not_found_lines = 0;
            file.lines_count = 0;

            if (i < filesCount - 1)
                printf("\n");
            fclose(fp);
            free(text_line);
        }
    }
}

int count_type(const char *values, char c) {
    int filesCount = 0;
    for (size_t i = 0; i <= strlen(values); i++)
        if (values[i] == c) filesCount++;
    return filesCount;
}

// // CHECKERS
// void check_errors(int argc, const char *values, char *argv[], opts_t opts) {
//     for (int j = 1; j < argc; j++) {
//         if (values[j-1] == '2') {
//             char *_ptr = NULL;
//             if ((_ptr = strchr(argv[j], 'f')) != NULL )
//                 check_file_isset((_ptr+1), opts);
//         }
//     }
//     if (count_type(values, '4') > 0) {
//         for (int j = 1; j < argc; j++)
//             if (values[j-1] == '4')
//                 check_file_isset(argv[j], opts);
//     }
//     // output file isset error with -l flag before result output
//     if (opts.l && !opts.s)
//         l_check_files(argc, argv, values);
// }

// void l_check_files(int argc, char *argv[], const char *values) {
//     for (int i = 1; i < argc; i++) {
//         if (values[i-1] == '5') {
//             FILE *fp = fopen(argv[i], "r");
//             if (fp == NULL)
//                 printf("grep: %s: No such file or directory\n", argv[i]);
//             else
//                 fclose(fp);
//         }
//     }
// }

// void check_file_isset(char *filename, opts_t opts) {
//     FILE *fp = fopen(filename, "r");
//     if (fp == NULL && !opts.s) {
//         printf("grep: %s: No such file or directory\n", filename);
//         exit(0);
//     }
//     char *pattern = NULL;
//     size_t len = 0;
//     // looping patterns from pattern file
//     while (getline(&pattern, &len, fp) > 0) check_regex_errors(pattern);
//     fclose(fp);
//     free(pattern);
// }

// void check_regex_errors(char *pattern) {
//     regex_t regex;
//     pattern[strcspn(pattern, "\n")] = 0;  // trim \n
//     int regcomp_result = regcomp(&regex, pattern, 0);
//     if (regcomp_result != 0) {
//         char buffer[100];
//         regerror(regcomp_result, &regex, buffer, 100);
//         printf("grep: %s\n", buffer);
//         exit(1);
//     }
//     regfree(&regex);
// }


// void parse(char *values, int argc, char *argv[], parse_t *parse, opts_t *opts) {
//     values[0] = '\0';
//     for (int i = 1; i < argc; i++) {
//         if (parse->act == 0) *parse = parseOpts(argv[i], *parse, opts);
//         if (parse->act == 0) *parse = isPattern(argv[i], *parse, argv[i+1], i);
//         if (parse->act == 0) *parse = isFile(argv[i], *parse);
//         parse->act = 0;
//         const char val = parse->val;
//         strncat(values, &val, 1);
//     }
//     values[argc] = '\0';
// }

// parse_t parseOpts(char *arg, parse_t parse, opts_t *opts) {
//     if ((arg[0] == '-')) {
//         char *p;
//         int i = 0;
//         parse.val = '1';
//         parse.next = 3;
//         for (p = (char*)arg; *p; p++)
//             if (getOpt(p, &parse, i, opts) < 0) break;
//         parse.act = 1;
//     }
//     return parse;
// }

// parse_t isPattern(const char *arg, parse_t parse, const char *n_arg, int i) {
//     if ((arg[0] != '-')) {
//         if (parse.next == 0 && parse.val == '\0') {
//             parse.val = '3'; parse.next = 0; parse.act = 1;
//         }
//         if (parse.next == 3) {
//             parse.val = '3'; parse.next = 0; parse.act = 1;
//         }
//         if (parse.next == 4) {
//             parse.val = '4'; parse.next = 0; parse.act = 1;
//         }
//         if (n_arg != NULL && n_arg[0] == '-' && i == 1) {
//             parse.val = '\0'; parse.next = 5; parse.act = 0;
//         }
//     }
//     return parse;
// }

// parse_t isFile(const char *arg, parse_t parse) {
//     if ((arg[0] != '-')) {
//         if (parse.next != 3 && parse.next != 4) {
//             parse.val = '5'; parse.next = 0; parse.act = 1;
//         }
//     }
//     return parse;
// }

// int getOpt(char *c, parse_t *parse, int i, opts_t *opts) {
//     switch (*c) {
//         case 'e':
//             opts->e = 1;
//             char *e_ptr = NULL;
//             if (((e_ptr = strchr(c, 'e')) != NULL) && (strlen(e_ptr+1) > 1)) {
//                 parse->val = '2';
//                 parse->next = 0;
//                 i = -1;
//             }
//             break;
//         case 'f':
//             opts->f = 1;
//             char *f_ptr = NULL;
//             if (((f_ptr = strchr(c, 'f')) != NULL) && (strlen(f_ptr+1) > 1)) {
//                 parse->val = '2';
//                 parse->next = 0;
//                 i = -1;
//             } else {
//                 parse->next = 4;
//             }
//             break;
//         case 'i': opts->i = 1; break;
//         case 'v': opts->v = 1; break;
//         case 'c': opts->c = 1; break;
//         case 'l': opts->l = 1; break;
//         case 'n': opts->n = 1; break;
//         case 'h': opts->h = 1; break;
//         case 's': opts->s = 1; break;
//         case 'o': opts->o = 1; break;
//         default: break;
//     }
//     return i;
// }


// void search_patterns(const char *v, int argc, char *argv[], opts_t o, file_t *f, line_t *l, result_t *r) {
//     for (int i = 1; i < argc; i++) {
//         if (v[i-1] == '2' && argv[i][0] == '-') pattern_s(argv[i], o, f, l, r);
//         if (v[i-1] == '3') search(argv[i], o, f, l, r);
//         if (v[i-1] == '4') pattern_f(argv[i], o, f, l, r);
//     }
//     if (r->match) {
//         f->found_lines++;
//         f->lines_count++;
//     } else {
//         f->not_found_lines++;
//     }
// }

// void pattern_s(char *arg, opts_t opts, file_t *file, line_t *line, result_t *result) {
//     size_t ptr_len = 0, ptr2_len = 0;
//     char *ptr = NULL, *ptr2 = NULL;
//     if ((ptr = strchr(arg, 'e')) != NULL ) ptr_len = strlen(ptr);
//     if ((ptr2 = strchr(arg, 'f')) != NULL ) ptr2_len = strlen(ptr2);
//     if (ptr2_len > ptr_len) pattern_f((ptr2 + 1), opts, file, line, result);
//     if (ptr_len > ptr2_len) search((ptr + 1), opts, file, line, result);
// }

// void pattern_f(char *p_fn, opts_t opts, file_t *file, line_t *line, result_t *result) {
//     FILE *fp = fopen(p_fn, "r");
//     if (fp == NULL && !opts.s) {
//         printf("grep: %s: No such file or directory\n", p_fn);
//         exit(0);
//     }
//     char *p_line = NULL;
//     size_t len = 0;
//     while (getline(&p_line, &len, fp) > 0) search(p_line, opts, file, line, result);
//     fclose(fp);
//     free(p_line);
// }

// void search(char *pattern, opts_t opts, file_t *file, line_t *line, result_t *result) {
//     pattern[strcspn(pattern, "\n")] = 0;  // trim \n
//     reg_search(pattern, opts, file, line, result);
// }

// void reg_compile(regex_t *regex, char *pattern, int cflags) {
//     int regcomp_result = regcomp(regex, pattern, cflags);
//     if (regcomp_result != 0) {
//         char buffer[100];
//         regerror(regcomp_result, regex, buffer, 100);
//         printf("grep: %s\n", buffer);
//         exit(1);
//     }
// }

// void reg_search(char *pattern, opts_t opts, file_t *file, line_t *line, result_t *result) {
//     (void)file;
//     regex_t regex;
//     regmatch_t rm[20];
//     int n_match = 20;
//     int cflags = (opts.i == 1) ? REG_ICASE : 0;
//     char * p = line->cur_line;
//     reg_compile(&regex, pattern, cflags);
//     if (strlen(p) > line->offset) p += line->offset;
//     while (1) {
//         int no_match = regexec(&regex, p, n_match, rm, 0);
//         if (no_match) break;
//         for (int i = 0; i < n_match; i++) {
//             if (rm[i].rm_so == -1) break;
//             result->start[result->match] = rm[i].rm_so + (p - line->cur_line);
//             result->finish[result->match] = rm[i].rm_eo + (p - line->cur_line);
//         }
//         result->match += 1;
//         if (rm[0].rm_eo > (int)line->offset) line->offset = rm[0].rm_eo;
//         p += rm[0].rm_eo;
//     }
//     regfree(&regex);
// }


// //  OUTPUT
// void print_result(opts_t opts, file_t *file, line_t *line, result_t *res) {
//     if (res->match > 0 && !opts.v && !opts.c && !opts.l) {
//         if (opts.o) {
//             print_line_number(opts, line);
//             for (int i = 0; i < res->match; i++) {
//                 if ((line->cur_line + res->start[i])[0] != '\n')
//                     printf("%.*s\n", (res->finish[i] - res->start[i]), (line->cur_line + res->start[i]));
//             }
//         } else {
//             if (line->cur_line != NULL) print_line(opts, file, line);
//         }
//     }
//     if (res->match == 0 && opts.v && !opts.c && !opts.l) print_line(opts, file, line);
// }

// void print_filename(opts_t opts, file_t *file) {
//     if (file->show && !opts.h) printf("%s:", file->name);
// }

// void print_line_number(opts_t opts, line_t *line) {
//     if (opts.n) printf("%d:", line->number);
// }

// void print_line(opts_t opts, file_t *file, line_t *line) {
//     if (line->cur_line != NULL) {
//         print_filename(opts, file);
//         print_line_number(opts, line);
//         printf("%s", line->cur_line);
//     }
// }

// void print_count(opts_t opts, file_t *file) {
//     if (opts.c && !opts.v) {
//         print_filename(opts, file);
//         if (opts.l && file->found_lines > 0)
//             printf("1\n");
//         else
//             printf("%d\n", file->found_lines);
//     }
//     if (opts.c && opts.v) {
//         print_filename(opts, file);
//         if (opts.l)
//             printf("1\n");
//         else
//             printf("%d\n", file->not_found_lines);
//     }
//     if (opts.l && file->found_lines > 0) printf("%s\n", file->name);
//     if (opts.l && opts.v && file->found_lines == 0) printf("%s\n", file->name);
// }
