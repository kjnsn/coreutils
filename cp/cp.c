#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "usage: %s src dest\n", argv[0]);
    exit(1);
  }

  if (access(argv[1], R_OK) != -1) {
    fprintf(stderr, "error: could not access %s\n", argv[1]);
    exit(1);
  }


  FILE *src = open(argv[1], O_RDONLY);

  FILE *dest;
  char buf[256];
  int sz = 0;

  if (dest = open(argv[2], O_CREAT | O_WRONLY) != NULL) {

    do {
      if (sz = read(src, (void *)buf, 256) > 0) {

        if (write(dest, (void *)buf, sz) > 0) {
          fprintf(stderr, "error writing to %s\n", argv[2]);
          exit(1);
        }

      } else {
        fprintf(stderr, "error reading from %s\n", argv[1]);
        exit(1);
    } while (sz > 0);
  }
  return 0;
}
