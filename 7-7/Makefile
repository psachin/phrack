#
#  Phrack: Issue 7-7
# 

CC = gcc
CFLAGS = -c -g
CURSES = -lcurses

BIN = horse

all: ${BIN}

horse:	horse.c
	@echo "Compiling.."
	${CC} $< ${CURSES} -o $@
clean:
	@echo "Cleaning up.."
	rm -rvf *~ \#* *.o *.out
	rm -rvf ${BIN}

