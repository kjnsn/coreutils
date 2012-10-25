#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char *rgv[]) {

  // init
  initscr();
  cbreak(); // disable line buffering
  keypad(stdscr, TRUE);


  printw("Hello world");
  refresh();


  getch();
  endwin();

  return 0;
}
