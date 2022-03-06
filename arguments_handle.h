#ifndef __ARGUMENTS_HANDLE_H__
#define __ARGUMENTS_HANDLE_H__

int is_option(char *arguments);
int find_target(int argc, char **argv);
int find_option(int argc, char **argv, const char *short_options, const struct option *long_option);

#endif /* #define __ARGUMENTS_HANDLE_H */
