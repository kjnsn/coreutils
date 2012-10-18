#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

#define BUF_LENGTH 4096

int process_line(const char *line) {
  if (strcmp(line, "exit") == 0)
    return 1;

  if (strlen(line) < 1)
    return 0;

  // run the program
  if (fork() == 0) {
    // child
    if (execv(strtok(line, " "), NULL) == -1) {
      fprintf(stderr, "Error running program: %s\n", line);
      return 0;
    }

  } else {
    // parent
    int status;
    wait(&status);
  }

}

int interactive(void) {
  char line[BUF_LENGTH];

  do {

    char *ps = getenv("PS1");
    if (!ps)
      ps = "# ";

    printf("%s", ps); // print out the prompt

    if (fgets(line, BUF_LENGTH, stdin)) {
      line[strlen(line)-1] = 0;  // strip the \n

      // quit if needed
      if (process_line(line) > 0)
        return 0;

    } else {
      printf("\n");
      return 1;
    }

  } while (1);

  return 0;
}

int main(int argc, char *argv[]) {
  // if no shell file provided, go into default mode
  if (argc < 2)
    return interactive();

  // otherwise, run a file
  FILE *file = fopen(argv[1], "r");
  char line[BUF_LENGTH];

  if (file) {
    while (fgets(line, BUF_LENGTH, file)) {
      line[strlen(line)-1] = 0;  // strip the \n

      // quit if needed
      if (process_line(line) > 0)
        return 0;

    }

    fclose(file);
  }
}
