#ifndef FUNC_GREP_H
#define FUNC_GREP_H

#define SIZE 1000
#define INIT 0

#include <getopt.h>

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} opt;

static struct option const long_options[] = {{"regexp", 1, 0, 'e'},
                                             {"ignore-case", 0, 0, 'i'},
                                             {"revert-match", 0, 0, 'v'},
                                             {"count", 0, 0, 'c'},
                                             {"files-with-matches", 0, 0, 'l'},
                                             {"line-number", 0, 0, 'n'}};

void clean(char **patterns);
void parser(int argc, char **argv, char **files, opt *options, char **patterns,
            int *countFiles);
void reader(char **files, opt options, char **patterns, int countFiles);

#endif