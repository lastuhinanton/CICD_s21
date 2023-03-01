#include <stdio.h>

#include "func_cat.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    opt options = {0};
    parser(argc, argv, &options);

    reader(argv, options);
    while (argv[optind + 1] != NULL) {
      optind++;
      reader(argv, options);
    }
  } else {
    fprintf(stderr, "Usage: ./s21_cat [OPTIONS] FILE");
  }

  return 0;
}