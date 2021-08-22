#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FILEHOLE_NAME "filehole"

int main(int argc, char **argv) {

  int fd = open(FILEHOLE_NAME, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);

  if (fd == -1) {
    printf("error when open and create a new file!");
    exit(1);
  }

  char *content = "hello world!";
  int len = write(fd, content, strlen(content));
  if (len == -1) {
      printf("error when write to file!");
  }

  int offset = lseek(fd, 100, SEEK_CUR);
  if (offset == -1){
      printf("error offset!");
      exit(2);
  }


  char * content2 = "write again!";
  len = write(fd, content2, strlen(content2));
  if (len == -1) {
      printf("error when write to file!");
  }

  return 0;
}
