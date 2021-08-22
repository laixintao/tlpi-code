#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_READ 10

int main(int argc, char **argv) {
  int c;
  int append = 0;
  while ((c = getopt(argc, argv, "a")) != -1) {
    switch (c) {
    case 'a':
      append = 1;
      break;
    default:
      printf("unknown args!");
      break;
    }
  }

  int openFlags = O_WRONLY | O_CREAT;
  if (append) {
    openFlags = openFlags | O_APPEND;
  }
  // open file to write
  int writefd = open(argv[optind], openFlags, S_IRUSR | S_IWUSR);
  if (writefd == -1) {
    printf("error when open file");
    exit(1);
  }

  ssize_t readSize = 0;
  char buffer[MAX_READ];
  ssize_t writeSize = 0;
  while (1) {
    readSize = read(STDIN_FILENO, buffer, MAX_READ);
    if (readSize == -1) {
      printf("error when read from stdio!");
      exit(2);
    }

    if (readSize == 0) {
      break;
    }

    write(1, buffer, readSize);

    writeSize = write(writefd, buffer, readSize);
    if (writeSize != readSize) {
      printf("error when write to file!");
      exit(3);
    }
  }

  return 0;
}
