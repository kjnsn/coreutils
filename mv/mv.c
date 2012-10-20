#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s current_path new_path\n", argv[0]);
    exit(0);
  }

  if (rename(argv[1], argv[2])) {
    fprintf(stderr, "Error: could not move %s to %s\n", argv[1], argv[2]);
    exit(1);
  }

  return 0;
}
