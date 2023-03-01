#include "library_cat.h"

#include <stdio.h>
#include <stdlib.h>

void implementation(FILE *f, opt options) {
  int flg_print_cur = 0;
  int cur = 0;
  int begin_line = 0;
  int counter_string = 0;
  int empty_line_counter = 0;

  while ((cur = getc(f)) != EOF) {
    if (begin_line == 0) {
      if (options.s && cur == '\n') {
        if (empty_line_counter == 0) {
          empty_line_counter = 1;
        } else {
          flg_print_cur = 1;
        }
      }
    } else {
      empty_line_counter = 0;
    }

    if (begin_line == 0 && flg_print_cur == 0) {
      begin_line = 1;
      if (options.n && cur == '\n') {
        printf("%6d\t", ++counter_string);
      } else if (cur != '\n' && (options.b || options.n)) {
        printf("%6d\t", ++counter_string);
      }
    }

    if (options.e && cur == '\n' && flg_print_cur == 0) {
      fputc('$', stdout);
    }

    if (options.t && cur == '\t') {
      printf("^I");
      flg_print_cur = 1;
    }

    if (cur == '\n') {
      begin_line = 0;
    }

    if (options.v) {
      if (cur >= 0 && cur <= 31 && cur != '\n' && cur != '\t') {
        fputc('^', stdout);
        fputc(cur + 64, stdout);
        flg_print_cur = 1;
      } else if (cur == 127) {
        fputc('^', stdout);
        fputc('?', stdout);
        flg_print_cur = 1;
      }
    }

    if (flg_print_cur == 0) {
      fputc(cur, stdout);
    } else {
      flg_print_cur = 0;
    }
  }
}