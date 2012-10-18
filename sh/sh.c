#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

#define BUF_LENGTH 4096

void process_line(const char *line) {

}

int interactive(void) {
  char line[BUF_LENGTH];

  do {
    if (fgets(line, BUF_LENGTH, stdin)) {
      line[strlen(line)-1] = 0;  // strip the \n
      process_line(line);
    }

  } while (strcmp (line, "exit") != 0);

  return 0;
}

int main(int argc, char *argv[]) {

#if DEBUG
  printf("argc: %d\n", argc);
#endif
  // if no shell file provided, go into default mode
  if (argc < 2)
    return interactive();

  // otherwise, run a file
}
