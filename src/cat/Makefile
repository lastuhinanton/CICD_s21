CC=gcc
CFLAGS=-c -Wall -Werror -Wextra

s21_cat: main_cat func_cat library_cat
	$(CC) s21_cat.o func_cat.o library_cat.o -o s21_cat

main_cat:
	$(CC) $(CFLAGS) s21_cat.c

func_cat:
	$(CC) $(CFLAGS) func_cat.c

library_cat:
	$(CC) $(CFLAGS) library_cat.c

check:
	bash ../style.sh && rm -rf test.tmp

rebuild: clean s21_cat

clean:
	rm -rf *.o s21_cat