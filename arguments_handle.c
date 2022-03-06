#include <unistd.h>
#include <getopt.h>

int is_option(char *argument) {
  return (argument[0] == '-');
}

int find_target(int argc, char **argv) {
  for (int target_index = 1; target_index < argc; ++target_index)
    if (! is_option(argv[target_index]))
      return target_index;

  return -1; // return error code if target doesn't exist
}

int find_option(int argc, char **argv, const char *short_options, const struct option *long_options) {
  return getopt_long(argc, argv, short_options, long_options, NULL);
}




