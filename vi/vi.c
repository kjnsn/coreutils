#include <ncurses.h>
#include <form.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//==== vars
char *curmsg = "\0";
enum modes { M_DEF, M_INS, M_CMD };
int mode = M_DEF;
FILE *fp = NULL;


//==== functions
void printmsg(char *msg);


//==== code
int main(int argc, char *argv[]) {

  // check to see if the specified file can be accessed
  if (argc > 1) {
    if (access(argv[1], R_OK | W_OK) == -1) {
      fprintf(stderr, "error: could not access %s\n", argv[1]);
      exit(1);
    } else {
      fp = fopen(argv[1], "rw");
    }
      
  }

  // init
  initscr();
  cbreak(); // disable line buffering
  keypad(stdscr, TRUE);
  noecho();


  if (argc == 1)
    printw("Welcome to vi!");


  do {
    
    if (mode == M_DEF) {

      char cmd = getch();

      int x, y;
      if (':' == cmd) {
        printmsg(":");
        echo();

        getmaxyx(stdscr, y, x);
        move(y - 1, 1);
        mode = M_CMD;
      } else if ('i' == cmd) {
        mode = M_INS;
      }
    }


    // if in cmd mode, get command
    if (mode == M_CMD) {
      
      char cmd[4096];
      getstr(cmd);

      if (strcmp(cmd, "q") == 0) {
        endwin();
        exit(0);
      } else {
        // if the command was not recognised, go back to default mode
        printmsg("");
        noecho();
        mode = M_DEF;
      }

    }
  } while (1);


  return 0;
}

void printmsg(char *msg) {

  // move the cursor to the bottom of the window
  int x, y;
  getmaxyx(stdscr, y, x);
  move(y - 1, 0);

  // clear the current message
  for (int i = 0; i < strlen(curmsg); i++) {
    printw(" ");
    move(y - 1, i);
  }

  // print out the message
  move(y - 1, 0);
  printw(msg);

  // move the cursor back
  move(0,0);

  curmsg = msg;
}
