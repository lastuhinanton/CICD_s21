CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

s21_grep: main_grep func_grep
	$(CC) s21_grep.o func_grep.o -o s21_grep

main_grep:
	$(CC) $(CFLAGS) s21_grep.c

func_grep:
	$(CC) $(CFLAGS) ../common/func_grep.c

test:

rebuild: clean s21_grep

clean:
	rm -rf *.o s21_grep