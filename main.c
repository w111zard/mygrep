#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "arguments_handle.h"
#include "options_list.h"

enum {
  BUFFER_SIZE = 80
};

void print_help() {
  printf("Usage: mygrep [OPTION]... PATTERNS [FILE]...\n");
  printf("Try 'mygrep --help' for more information.\n");
}

void setup_color() {
  printf("\033[0;31m");
}

void reset_color() {
  printf("\033[0m");
}

enum {
  DEFAULT,
  CHECK,
  PRINT
};

void highlight_patterns(char *str, char *pattern) {
  int status = DEFAULT;

  int i = 0;
  int j = 0;

  while (str[i] && str[i + j]) {
    switch (status) {
    case DEFAULT:
      if (str[i] != pattern[0]) {
        putchar(str[i]);
        ++i;
      }
      else {
        j = 1;
        status = CHECK;
      }
      break;

    case CHECK:
      if (str[i + j] == pattern[j]) {
        ++j;
      }
      else if(pattern[j] == 0) {
        setup_color();
        printf("%s", pattern);
        reset_color();

        status = DEFAULT;
        i += j;
        j = 0;
      }
      else {
        int beg = i;
        while (i <= beg + j) {
          putchar(str[i]);
          ++i;
        }
        j = 0;
        status = DEFAULT;
      }
      break;
    }
  }
}

void my_grep(char *target) {
  char buffer[BUFFER_SIZE];

  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL)
    if (strstr(buffer, target) != NULL)
      highlight_patterns(buffer, target);
}

void my_grep_invert(char *target) {
  char buffer[BUFFER_SIZE];

  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL)
    if (strstr(buffer, target) == NULL)
      printf("%s", buffer);
}

int main(int argc, char **argv) {
  opterr = 0; // disable error print

  int target_index = find_target(argc, argv);
  int option = find_option(argc, argv, short_options, long_options);

  if ((target_index == -1) && (option != 'h')) {
    print_help();
    return 1;
  }

  switch (option) {
  case -1:
    my_grep(argv[target_index]);
    break;

  case 'v':
    my_grep_invert(argv[target_index]);
    break;

  case 'h':
    break;

  case '?':
    printf("Error: unknown option!\n");
    return 2;

  default:
    break;
  }

  return 0;
}
