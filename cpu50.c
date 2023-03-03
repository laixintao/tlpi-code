#include <time.h>
#include <unistd.h>

int main(void) {
  int clock_per_ms = CLOCKS_PER_SEC / 1000;

  while (1) {
    int count = 0;
    while (count < clock_per_ms * 1000) {
      count += 1;
    };
    usleep(1);
  }
  return 0;
}
