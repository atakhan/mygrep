#include <stdio.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

int compareFile(FILE * fPtr1, FILE * fPtr2, int * line, int * col);
int run_test(char *command1, char *command2, int i, int *success, int *failure);

int main() {
    int i = 1;
    int s = 0;
    int f = 0;
    printf("\n\n======================== INTEGRATION TESTS ========================\n");

    printf(" -------------------\n OPTION (e) TESTS \n -------------------\n");
    i = run_test(
              "grep epat -e one text.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep epat -e one text.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -e one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ie ONE test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ie ONE test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -eone test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -eone test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -eone test2.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -eone test2.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e twenty -fpattern.txt -eseven test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -e twenty -fpattern.txt -eseven test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -fpattern.txt test2.txt -o > outputs/output_orig.txt 2>&1",
        "./s21_grep -fpattern.txt test2.txt -o > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e one -e twenty test2.txt -e test > outputs/output_orig.txt 2>&1",
        "./s21_grep -e one -e twenty test2.txt -e test > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e one -e twenty -e and -e yo test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -e one -e twenty -e and -e yo test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e one -fpatternss.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -e one -fpatternss.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);

    printf(" -------------------\n OPTION (f) TESTS \n -------------------\n");

    i = run_test(
              "grep -f pattern.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -f pattern.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -fpattern.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -fpattern.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -fpattern.txt test2.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -fpattern.txt test2.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -fpatternss.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -fpatternss.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -fpatternss.txt test2.txt -e one > outputs/output_orig.txt 2>&1",
        "./s21_grep -fpatternss.txt test2.txt -e one > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -f patternerr.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -f patternerr.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);

    printf(" -------------------\n OTHER OPTIONS TESTS \n -------------------\n");

    i = run_test(
              "grep -i ONE test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -i ONE test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -v one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -v one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -c one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -c one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -c one test2.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -c one test2.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -cv one test2.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -cv one test2.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -l one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -l one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -l one test2.txt test2.txt test3.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -l one test2.txt test2.txt test3.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -n one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -n one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -h one test2.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -h one test2.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -s one test2.txt testno.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -s one test2.txt testno.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -o one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -o one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);

    printf(" -------------------\n COMPATIBLE PAIR COMBO TESTS \n -------------------\n");

    i = run_test(
              "grep -vc one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -vc one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -vl one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -vl one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -vn one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -vn one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -vh one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -vh one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -vs one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -vs one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -vi one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -vi one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ch one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ch one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -cs one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -cs one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ci one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ci one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ls one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ls one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -li one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -li one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -nh one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -nh one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ns one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ns one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -no one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -no one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ni one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ni one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -hs one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -hs one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ho one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ho one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -hi one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -hi one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -so one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -so one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -si one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -si one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -oi one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -oi one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);

    printf(" -------------------\n DOUBTFUL PAIR COMBO TESTS \n -------------------\n");
    i = run_test(
              "grep -cl one test2.txt test3.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -cl one test2.txt test3.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -cl one test2.txt test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -cl one test2.txt test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -cn one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -cn one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -co one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -co one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -vo one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -vo one test2.txt > outputs/output_s21.txt", i, &s, &f);
    i = run_test(
              "grep -ln one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ln one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -lh one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -lh one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -lo one test2.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -lo one test2.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e one -e yo -e hmm test.txt -c > outputs/output_orig.txt 2>&1",
        "./s21_grep -e one -e yo -e hmm test.txt -c > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e one -e yo test2.txt -v -n > outputs/output_orig.txt 2>&1",
        "./s21_grep -e one -e yo test2.txt -v -n > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep for s21_grep.c s21_grep.h Makefile -v -c -h > outputs/output_orig.txt 2>&1",
        "./s21_grep for s21_grep.c s21_grep.h Makefile -v -c -h > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep one test2.txt -v -c -o > outputs/output_orig.txt 2>&1",
        "./s21_grep one test2.txt -v -c -o > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e ^twenty test.txt -v -c -n > outputs/output_orig.txt 2>&1",
        "./s21_grep -e ^twenty test.txt -v -c -n > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e . test.txt -o > outputs/output_orig.txt 2>&1",
        "./s21_grep -e . test.txt -o > outputs/output_s21.txt 2>&1", i, &s, &f);


    printf(" -------------------\n V TESTS \n -------------------\n");
    i = run_test(
              "grep yo test.txt test2.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep yo test.txt test2.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -i one test.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep -i one test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -v s test.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep -v s test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -c s test.txt  > outputs/output_orig.txt 2>&1",
        ".//s21_grep -c s test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -l s test.txt test.txt test.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep -l s test.txt test.txt test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -n s test.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep -n s test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -o 123 test.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep -o 123 test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -h reflect test.txt test.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep -h reflect test.txt test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep grep -s 123123  > outputs/output_orig.txt 2>&1",
        "./s21_grep grep -s 123123  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -f test.txt test.txt  > outputs/output_orig.txt 2>&1",
        "./s21_grep -f test.txt test.txt  > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -in trulyalya test.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -in trulyalya test.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -cv s test.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -cv s test.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -iv s test.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -iv s test.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -lv s test.txt test.txt test.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -lv s test.txt test.txt test.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ho reflect test.txt test.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -ho reflect test.txt test.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -nf test.txt test.txt > outputs/output_orig.txt 2>&1",
        "./s21_grep -nf test.txt test.txt > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -ffilepath > outputs/output_orig.txt 2>&1",
        "./s21_grep -ffilepath > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep > outputs/output_orig.txt 2>&1",
        "./s21_grep > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -e > outputs/output_orig.txt 2>&1",
        "./s21_grep -e > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -f > outputs/output_orig.txt 2>&1",
        "./s21_grep -f > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -i > outputs/output_orig.txt 2>&1",
        "./s21_grep -i > outputs/output_s21.txt 2>&1", i, &s, &f);
    i = run_test(
              "grep -v > outputs/output_orig.txt 2>&1",
        "./s21_grep -v > outputs/output_s21.txt 2>&1", i, &s, &f);
    // i = run_test(
    //           "grep -e .* test.txt -o > outputs/output_orig.txt 2>&1",
    //     "./s21_grep -e .* test.txt -o > outputs/output_s21.txt 2>&1", i, &s, &f);
    printf(" ------------- \n");
    printf("| SUCCESS: %d |\n", s);
    printf(" ------------- \n");
    printf("| FAILURE: %d |\n", f);
    printf(" ------------- \n");
    (void)i;
    return 0;
}

int run_test(char *command1, char *command2, int i, int *success, int *failure) {
    printf("test #%-3d ", i);

    system(command1);
    system(command2);

    FILE * fPtr1;
    FILE * fPtr2;

    int diff;
    int line, col;
    fPtr1 = fopen("outputs/output_orig.txt", "r");
    fPtr2 = fopen("outputs/output_s21.txt", "r");

    if (fPtr1 == NULL || fPtr2 == NULL) {
        printf("ERROR: Unable to open file.");
        printf("Please check whether file exists and you have read privilege.");
        exit(EXIT_FAILURE);
    }

    diff = compareFile(fPtr1, fPtr2, &line, &col);

    if (diff == 0) {
        printf("%sSUCCESS: %s%s %s\n", KGRN, command1, command2, KNRM);
        *success += 1;
    } else {
        printf("%sFAIL: %s%s %s\n", KRED, command1, command2, KNRM);
        *failure += 1;
    }
    fclose(fPtr1);
    fclose(fPtr2);
    return (i += 1);
}

int compareFile(FILE * fPtr1, FILE * fPtr2, int * line, int * col) {
    int ch1, ch2;
    *line = 1;
    *col  = 0;
    do {
        ch1 = fgetc(fPtr1);
        ch2 = fgetc(fPtr2);
        if (ch1 == '\n') {
            *line += 1;
            *col = 0;
        }
        if (ch1 != ch2)
            return -1;
        *col  += 1;
    } while (ch1 != EOF && ch2 != EOF);

    if (ch1 == EOF && ch2 == EOF)
        return 0;
    else
        return -1;
}
