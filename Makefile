.PHONY: all clean
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g

all: s21_grep tests

s21_grep: s21_grep.o s21_grep_parse.o s21_grep_errors.o s21_grep_search.o s21_grep_output.o

tests: tests.o

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c -o s21_grep.o s21_grep.c

s21_grep_parse.o: s21_grep_parse.c s21_grep.h
	$(CC) $(CFLAGS) -c -o s21_grep_parse.o s21_grep_parse.c

s21_grep_errors.o: s21_grep_errors.c s21_grep.h
	$(CC) $(CFLAGS) -c -o s21_grep_errors.o s21_grep_errors.c

s21_grep_search.o: s21_grep_search.c s21_grep.h
	$(CC) $(CFLAGS) -c -o s21_grep_search.o s21_grep_search.c

s21_grep_output.o: s21_grep_output.c s21_grep.h
	$(CC) $(CFLAGS) -c -o s21_grep_output.o s21_grep_output.c

tests.o: tests.c
	mkdir outputs/
	$(CC) $(CFLAGS) -c -o tests.o tests.c

rebuild: clean all

test: clean all
	./tests

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h

clean:
	rm -rf *.o *.a *.info test.out
	rm -rf outputs/
	rm -rf s21_grep tests
