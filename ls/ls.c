#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  void *dir = argv[1];

  // check args
  if (argc == 1) {
    dir = (void *)"./";
  }

  // check to see if the file exists
  if (access( dir, R_OK ) == -1) {
    fprintf(stderr, "error, could not open %s\n", dir);
    exit(1);
  }

  DIR *dirp = opendir(dir);

  for (struct dirent *file = readdir(dirp); file; file = readdir(dirp)) {
    if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
      printf("%s ", file->d_name);
  }

  printf("\n");


  return 0;
}
