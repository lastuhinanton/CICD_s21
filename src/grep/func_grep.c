#include "func_grep.h"

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isFile(char *file, int *countFiles) {
  int status;
  FILE *f;
  if ((f = fopen(file, "r")) != NULL) {
    status = 1;
    (*countFiles)++;
    fclose(f);
  } else {
    status = 0;
  }
  return status;
}

void clean(char **patterns) {
  while (*patterns) {
    free(*patterns);
    patterns++;
  }
}

void printError(int code, char **patterns, char **files) {
  switch (code) {
    case 1:
      fprintf(stderr, "Something wrong with pattern.");
      break;
    case 2:
      fprintf(stderr, "Could not compile regex\n");
      break;
    case 3:
      fprintf(stderr, "Something wrong with file.");
      break;
    case 4:
      fprintf(stderr, "Something wring with memory");
      break;
    case 5:
      fprintf(stderr, "Something wrong with flags");
      break;
  }
  clean(patterns);
  clean(files);
  exit(1);
}

int parsFlag(char *flags, opt *options, char **patterns, int *in, char **files,
             int *reqPattern) {
  int status = 0;
  for (int i = 1; i < (int)strlen(flags); i++) {
    switch (flags[i]) {
      case 'e':
        if (i == ((int)strlen(flags) - 1)) {
          options->e = 1;
          options->f = 0;
        } else {
          int j = 0;
          patterns[*in] = calloc(300, sizeof(char));
          if (!patterns[*in]) {
            printError(1, patterns, files);
          }
          while (j + i + 1 < (int)strlen(flags)) {
            patterns[*in][j] = flags[j + i + 1];
            j++;
          }
          (*in)++;
          i = (int)strlen(flags) - 1;
          options->e = 0;
          options->f = 0;
          *reqPattern = 1;
        }
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        if (i != ((int)strlen(flags) - 1)) {
          status = 1;
        }
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        printError(1, patterns, files);
    }
  }
  return status;
}

void parser(int argc, char **argv, char **files, opt *options, char **patterns,
            int *countFiles) {
  int i = 0;
  int i_file = 0;
  int index = 1;
  int reqPattern = 0;
  int reqFiles = 0;
  char pat[SIZE] = {'\0'};

  while (index < argc) {
    if (isFile(argv[index], countFiles)) {
      reqFiles = 1;

      files[i_file] = malloc(SIZE * sizeof(char));
      if (!files[i_file]) printError(3, patterns, files);
      strcpy(files[i_file], argv[index]);
      i_file++;

    } else if (argv[index][0] == '-') {
      if (parsFlag(argv[index], options, patterns, &i, files, &reqPattern)) {
        printError(5, patterns, files);
      }
      if (options->f) {
        FILE *f;
        if ((f = fopen(argv[++index], "r")) == NULL) {
          if (!options->s)
            printError(1, patterns, files);
          else {
            printError(2, patterns, files);
          }
        }
        while (fgets(pat, SIZE, f) != NULL) {
          if (pat[strlen(pat) - 1] == '\n') pat[strlen(pat) - 1] = '\0';
          patterns[i] = malloc(SIZE * sizeof(char));
          if (!patterns[i]) printError(3, patterns, files);
          strcpy(patterns[i], pat);
          i++;
        }
        fclose(f);
        reqPattern = 1;
      } else if (options->e) {
        patterns[i] = malloc(SIZE * sizeof(char));
        if (!patterns[i]) printError(3, patterns, files);
        if (index == argc - 1) printError(5, patterns, files);
        strcpy(patterns[i], argv[++index]);
        options->e = 0;
        i++;
        reqPattern = 1;
      }
    } else {
      patterns[i] = malloc(SIZE * sizeof(char));
      if (!patterns[i]) printError(4, patterns, files);
      strcpy(patterns[i], argv[index]);
      i++;
      reqPattern = 1;
    }
    index++;
  }

  if (reqFiles == 0 || reqPattern == 0) {
    if (!options->s && reqPattern == 0) {
      printError(1, patterns, files);
    } else if (!options->s && reqFiles == 0) {
      printError(1, patterns, files);
    }
  }
}

void neitral_case(char *string) {
  while (*string) {
    *string = tolower(*string);
    string++;
  }
}

void reader(char **files, opt options, char **patterns, int countFiles) {
  int i_file = 0;
  int matchedFile;
  int index = 0;
  int matched = 0;
  int countMatchedLines;
  int countMatchedFiles = 0;
  int counterLines;
  int reti;
  regex_t regex;
  char string_std[SIZE] = {'\0'};

  FILE *f;
  while (i_file < countFiles) {
    if ((f = fopen(*files, "r")) == NULL) printError(3, patterns, files);
    countMatchedLines = 0;
    matchedFile = 0;
    counterLines = 0;
    while (fgets(string_std, SIZE, f) != NULL) {
      index = 0;
      matched = 0;
      while (patterns[index]) {
        if (options.i) {
          char string_nei[SIZE];
          char expresion[SIZE];

          strcpy(expresion, patterns[index]);
          strcpy(string_nei, string_std);
          neitral_case(expresion);
          neitral_case(string_nei);

          reti = regcomp(&regex, expresion, 0);
          if (reti) {
            regfree(&regex);
            printError(2, patterns, files);
          }
          reti = regexec(&regex, string_nei, 0, NULL, REG_NEWLINE);
          regfree(&regex);

          if (!reti) {
            matched = 1;
            matchedFile = 1;
          }
        } else {
          reti = regcomp(&regex, patterns[index], 0);
          if (reti) {
            regfree(&regex);
            printError(2, patterns, files);
          }
          reti = regexec(&regex, string_std, 0, NULL, REG_NEWLINE);
          regfree(&regex);

          if (!reti) {
            matched = 1;
            matchedFile = 1;
          } else if (options.v) {
            matchedFile = 1;
          }
        }
        index++;
      }

      counterLines++;

      if (matched && !options.v) {
        countMatchedLines++;
        if (!options.c && !options.l) {
          if (countFiles > 1 && !options.h) {
            printf("%s:", *files);
          }
          if (options.n) {
            printf("%d:", counterLines);
          }
          printf("%s", string_std);
          if (string_std[strlen(string_std) - 1] != '\n') {
            fputc('\n', stdout);
          }
        }
      } else if (!matched && options.v) {
        countMatchedLines++;
        if (!options.c && !options.l) {
          if (countFiles > 1 && !options.h) {
            printf("%s:", *files);
          }
          if (options.n) {
            printf("%d:", counterLines);
          }
          printf("%s", string_std);
          if (string_std[strlen(string_std) - 1] != '\n') {
            fputc('\n', stdout);
          }
        }
      }
    }
    if (matchedFile) countMatchedFiles++;

    if (options.c || options.l) {
      if (options.c && options.l) {
        if (countFiles > 1) {
          if (!options.h && !options.n && !options.o) {
            printf("%s:%d\n", *files, matchedFile);
            if (matchedFile) {
              printf("%s\n", *files);
            }
          } else if (options.h || options.n) {
            printf("%d\n", matchedFile);
            if (matchedFile) {
              printf("%s\n", *files);
            }
          } else {
            printf("%s:%d\n", *files, countMatchedFiles);
          }
        } else {
          if (!options.h && !options.n && !options.o) {
            if (options.v) {
              printf("%d\n", matchedFile);
              if (matchedFile) {
                printf("%s\n", *files);
              }
            } else {
              printf("%s:%d\n", *files, matchedFile);
              if (matchedFile) {
                printf("%s\n", *files);
              }
            }
          } else if (options.h) {
            printf("%d\n", countMatchedFiles);
            if (matchedFile) {
              printf("%s\n", *files);
            }
          } else {
            printf("%d\n%s\n", countMatchedFiles, *files);
          }
        }
      } else {
        if (countFiles > 1 && options.c && !options.h) {
          printf("%s:%d\n", *files, countMatchedLines);
        } else if (options.c) {
          printf("%d\n", countMatchedLines);
        }
        if (options.l && matchedFile) {
          printf("%s\n", *files);
        }
      }
    }
    files++;
    i_file++;
    fclose(f);
  }
}
