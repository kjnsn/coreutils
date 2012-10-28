#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "usage: %s src dest\n", argv[0]);
    exit(1);
  }

  if (access(argv[1], R_OK) == -1) {
    fprintf(stderr, "error: could not access %s\n", argv[1]);
    exit(1);
  }


  int src = open(argv[1], O_RDONLY);

  int dest;
  char buf[1024];
  int sz = 0;

  mode_t file_perms;
  int open_flags = O_CREAT | O_WRONLY | O_TRUNC;
  file_perms = S_IRUSR | S_IWUSR | S_IRGRP |
               S_IROTH | S_IWOTH;

  dest = open(argv[2], open_flags, file_perms);
  if (dest == -1) {
    fprintf(stderr, "error writing to %s\n", argv[2]);
    exit(1);
  }

  while((sz = read(src, buf, 1024)) > 0) {
    if (write(dest, buf, sz) != sz) {
      fprintf(stderr, "error writing to %s\n", argv[2]);
      exit(1);
    }
  }

  if (sz == -1) {
    fprintf(stderr, "error reading from %s\n", argv[1]);
    exit(1);
  }


  close(src);
  close(dest);

  return 0;
}
