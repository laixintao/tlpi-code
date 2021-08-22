#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_READ 20

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("cp <src> <dst>, 2 arguments please. you have %d", argc);
    exit(1);
  }

  char *src = argv[1];
  char *dst = argv[2];

  printf("copy from %s to %s...\n", src, dst);

  int srcFd = open(src, O_RDONLY);
  int dstFd = open(dst, O_WRONLY | O_CREAT, S_IRWXU);

  char buffer[MAX_READ];
  size_t rsize, wsize = 0;

  while (1) {
    rsize = read(srcFd, buffer, MAX_READ);

    // not very sure if there is anything special here.
    // read and write are already dealing with holes very nice from my perspective
    // maybe this is a better answer:
    // https://github.com/posborne/linux-programming-interface-exercises/blob/master/04-file-io-universal-io-model/cpholes.c#L78

    if (rsize == -1) {
      printf("error when read from file! error: %s\n", strerror(errno));
      exit(1);
    }

    if (rsize == 0) {
      break;
    }

    wsize = write(dstFd, buffer, rsize);
    if (wsize == -1) {
      printf("error when write file!");
      exit(2);
    }
  }

  return 0;
}
