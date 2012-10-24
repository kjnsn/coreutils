#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define DEBUG 1

#define BUF_LENGTH 4096
#define NARGS 64

void split(char *result[], char *input, const char *delim) {
  int i = 0;
  result[i] = strtok(input, delim);

  while (1) {
    i++;
    result[i] = strtok(NULL, delim);
    
    if (result[i] == NULL)
      break;
  }
}


int process_line(char *line) {
  if (strcmp(line, "exit") == 0)
    return 1;

  if (strlen(line) < 1)
    return 0;

  regex_t r;
  if (regcomp(&r, "^[A-Za-z0-9]*=.*", 0)) {
    fprintf(stderr, "Error compiling regex\n");
    return 0;
  }

  if (!regexec(&r, line, 0, NULL, 0)) {
    printf("setting env: %s\n", line);
    putenv(line);
    return 0; 
  }

  // run the program
  if (fork() == 0) {
    // child

    char *args[NARGS];
    split(args, line, " ");

    // Try running the program with the raw filename
    execvp(args[0], args);

    // Find the file (using $PATH)
    char *paths[NARGS];
    split(paths, getenv("PATH"), ":");

    for (int i = 0; paths[i] != NULL; i++) {

      char *p = (char *)malloc(strlen(paths[i]) + strlen(args[0]));
      strcpy(p, paths[i]);
      strcat(p, "/");
      strcat(p, args[0]);

      if (access(p, X_OK ) != -1) {
        // file exists
        if (execvp(p, args)) {
          fprintf(stderr, "Error running program: %s\n", p);
          exit(0);
        }
      }
    }

    // file doesn't exist
    fprintf(stderr, "could not access file: %s\n", args[0]);
    exit(0);

  } else {
    // parent
    wait(NULL);
    return 0;
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
