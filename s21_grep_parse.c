#include "s21_grep.h"

// VALUES
// 1 - options
// 2 - sliced options (ex: "-fso" -> "so" being an argument; if "f" then it's pattern file; if "e" pattern)
// 3 - pattern
// 4 - pattern file
// 5 - file

void parse(char *values, int argc, char *argv[], parse_t *parse, opts_t *opts) {
    values[0] = '\0';
    for (int i = 1; i < argc; i++) {
        if (parse->act == 0) *parse = parseOpts(argv[i], *parse, opts);
        if (parse->act == 0) *parse = isPattern(argv[i], *parse, argv[i+1], i);
        if (parse->act == 0) *parse = isFile(argv[i], *parse);
        parse->act = 0;
        const char val = parse->val;
        strncat(values, &val, 1);
    }
    values[argc] = '\0';
}

parse_t parseOpts(char *arg, parse_t parse, opts_t *opts) {
    if ((arg[0] == '-')) {
        char *p;
        int i = 0;
        parse.val = '1';
        parse.next = 3;
        for (p = (char*)arg; *p; p++)
            if (getOpt(p, &parse, i, opts) < 0) break;
        parse.act = 1;
    }
    return parse;
}

parse_t isPattern(const char *arg, parse_t parse, const char *n_arg, int i) {
    if ((arg[0] != '-')) {
        if (parse.next == 0 && parse.val == '\0') {
            parse.val = '3'; parse.next = 0; parse.act = 1;
        }
        if (parse.next == 3) {
            parse.val = '3'; parse.next = 0; parse.act = 1;
        }
        if (parse.next == 4) {
            parse.val = '4'; parse.next = 0; parse.act = 1;
        }
        if (n_arg != NULL && n_arg[0] == '-' && i == 1) {
            parse.val = '\0'; parse.next = 5; parse.act = 0;
        }
    }
    return parse;
}

parse_t isFile(const char *arg, parse_t parse) {
    if ((arg[0] != '-')) {
        if (parse.next != 3 && parse.next != 4) {
            parse.val = '5'; parse.next = 0; parse.act = 1;
        }
    }
    return parse;
}

int getOpt(char *c, parse_t *parse, int i, opts_t *opts) {
    switch (*c) {
        case 'e':
            opts->e = 1;
            char *e_ptr = NULL;
            if (((e_ptr = strchr(c, 'e')) != NULL) && (strlen(e_ptr+1) > 1)) {
                parse->val = '2';
                parse->next = 0;
                i = -1;
            }
            break;
        case 'f':
            opts->f = 1;
            char *f_ptr = NULL;
            if (((f_ptr = strchr(c, 'f')) != NULL) && (strlen(f_ptr+1) > 1)) {
                parse->val = '2';
                parse->next = 0;
                i = -1;
            } else {
                parse->next = 4;
            }
            break;
        case 'i': opts->i = 1; break;
        case 'v': opts->v = 1; break;
        case 'c': opts->c = 1; break;
        case 'l': opts->l = 1; break;
        case 'n': opts->n = 1; break;
        case 'h': opts->h = 1; break;
        case 's': opts->s = 1; break;
        case 'o': opts->o = 1; break;
        default: break;
    }
    return i;
}

