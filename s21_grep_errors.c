#include "s21_grep.h"

// VALUES
// 1 - options
// 2 - sliced options (ex: "-fso" -> "so" being an argument; if "f" then it's pattern file; if "e" pattern)
// 3 - pattern
// 4 - pattern file
// 5 - file

// CHECKERS
void check_errors(int argc, const char *values, char *argv[], opts_t opts) {
    if (strlen(values) == 1 && values[0] != '2') {
        if (opts.e || opts.f)
            printf("grep: option requires an argument -- %c\n", (opts.e ? 'e': 'f'));
        print_usage();
    }
    for (int j = 1; j < argc; j++) {
        if (values[j-1] == '2') {
            char *_ptr = NULL;
            if ((_ptr = strchr(argv[j], 'f')) != NULL )
                check_file_isset((_ptr+1), opts);
        }
    }
    if (count_type(values, '4') > 0) {
        for (int j = 1; j < argc; j++)
            if (values[j-1] == '4')
                check_file_isset(argv[j], opts);
    }
    // output file isset error with -l flag before result output
    if (opts.l && !opts.s)
        l_check_files(argc, argv, values);
}

void l_check_files(int argc, char *argv[], const char *values) {
    for (int i = 1; i < argc; i++) {
        if (values[i-1] == '5') {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL)
                printf("grep: %s: No such file or directory\n", argv[i]);
            else
                fclose(fp);
        }
    }
}

void check_file_isset(char *filename, opts_t opts) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL && !opts.s) {
        printf("grep: %s: No such file or directory\n", filename);
        exit(0);
    }
    char *pattern = NULL;
    size_t len = 0;
    // looping patterns from pattern file
    while (getline(&pattern, &len, fp) > 0) check_regex_errors(pattern);
    fclose(fp);
    free(pattern);
}

void check_regex_errors(char *pattern) {
    regex_t regex;
    pattern[strcspn(pattern, "\n")] = 0;  // trim \n
    int regcomp_result = regcomp(&regex, pattern, 0);
    if (regcomp_result != 0) {
        char buffer[100];
        regerror(regcomp_result, &regex, buffer, 100);
        printf("grep: %s\n", buffer);
        exit(1);
    }
    regfree(&regex);
}
