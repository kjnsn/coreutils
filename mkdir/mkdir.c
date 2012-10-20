#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: %s <file or directory to create> <mode in binary>:optional\n", argv[0]);
    exit(0);
  }

  if (mkdir(argv[1], argc > 2 ? atoi(argv[2])  : 0b111101101)) {
    fprintf("mkdir: could not create directory %s\n", argv[1]);
  }

  return 0;
}
