#include "func_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "library_cat.h"

void parser(int argc, char **argv, opt *options) {
  int opt;
  int option_index;

  while ((opt = getopt_long(argc, argv, "+benstvET", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        options->n = 0;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        if (!options->b) options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      default:
        exit(1);
    }
  }
}

void reader(char *argv[], opt options) {
  FILE *f;
  if ((f = fopen(argv[optind], "r")) == NULL) {
    fprintf(stderr, "Something wrong with file");
    exit(1);
  }

  implementation(f, options);
}
