#include <stdio.h>

#include "../common/func_grep.h"

int main(int argc, char *argv[]) {
  int countFiles = 0;
  char *files[SIZE] = {'\0'};
  opt options = {INIT};
  char *patterns[SIZE] = {'\0'};

  if (argc > 1) {
    parser(argc, argv, files, &options, patterns, &countFiles);

    reader(files, options, patterns, countFiles);
  } else {
    fprintf(stderr, "Something wrong with arguments");
  }

  clean(files);
  clean(patterns);
  return 0;
}