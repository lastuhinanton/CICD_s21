#ifndef FUNC_CAT_H
#define FUNC_CAT_H

#include <getopt.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

static struct option const long_options[] = {
    {"number-nonblank", 0, 0, 'b'}, {"show-ends", 0, 0, 'e'},
    {"number", 0, 0, 'n'},          {"squeeze-blank", 0, 0, 's'},
    {"show-tabs", 0, 0, 't'},       {"show-nonprinting", 0, 0, 'v'},
    {"show-tabs", 0, 0, 'T'},       {"show-ends", 0, 0, 'E'}};

void parser(int argc, char *argv[], opt *options);
void reader(char *argv[], opt options);

#endif