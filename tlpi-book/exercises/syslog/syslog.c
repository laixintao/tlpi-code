#include "tlpi_hdr.h"
#include <ctype.h>
#include <syslog.h>

#define printable(ch) (isprint((unsigned char)ch) ? ch : '#')

const char *program = "my_logger";

static void /* Print "usage" message and exit */
usageError(char *progName, char *msg, int opt) {
  if (msg != NULL && opt != 0)
    fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
  fprintf(stderr, "Usage: [-l priority] %s\n", progName);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  int opt, priority;
  while ((opt = getopt(argc, argv, ":l:")) != -1) {

    printf("opt =%3d (%c); optind = %d\n", opt, printable(opt), optind);

    switch (opt) {
    case 'l':
      if (strcmp(optarg, "EMERG") == 0) {
        priority = LOG_EMERG;
      } else if (strcmp(optarg, "ALERT") == 0) {
        priority = LOG_ALERT;
      } else if (strcmp(optarg, "CRIT") == 0) {
        priority = LOG_CRIT;
      } else if (strcmp(optarg, "ERR") == 0) {
        priority = LOG_ERR;
      } else if (strcmp(optarg, "WARNING") == 0) {
        priority = LOG_WARNING;
      } else if (strcmp(optarg, "NOTICE") == 0) {
        priority = LOG_NOTICE;
      } else if (strcmp(optarg, "INFO") == 0) {
        priority = LOG_INFO;
      } else if (strcmp(optarg, "DEBUG") == 0) {
        priority = LOG_DEBUG;
      } else {
        usageError(argv[0], "Invalid priority", optopt);
      }
      break;
    case ':':
      usageError(argv[0], "Missing argument", optopt);
    case '?':
      usageError(argv[0], "Unrecognized option", optopt);
    }
  }

  char *message = argv[optind];

  openlog(program, LOG_NDELAY, LOG_USER);

  syslog(priority, "priority=%d: %s\n", priority, message);

  closelog();

  return 0;
}
