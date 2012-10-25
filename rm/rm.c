#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <files to remove>\n", argv[0]);
    exit(1);
  }

  char *file = argv[1];
  for (int i = 1; i < argc; i++, file = argv[i]) {
    if (remove(file) == -1) {
      fprintf(stderr, "error: could not remove %s\n", file);
    }
  }

  return 0;
}
