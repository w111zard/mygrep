#ifndef __OPTIONS_LIST_H__
#define __OPTIONS_LIST_H__

const char *short_options = "hv";

const struct option long_options[] = {
  {"help", no_argument, NULL, 'h'},
  {"invert-match", no_argument, NULL, 'v'},
  {NULL, 0, NULL, 0}
};

opterr = 0; // disable error messages

#endif /* #define __OPTIONS_LIST_H__ */
