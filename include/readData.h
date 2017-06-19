#ifndef READDATA_H
#define READDATA_H

#define _SVID_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <curses.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

#define MAXDIR 255

typedef struct DS direct;
struct DS{
	char path[255];
	char **names;
	int countNames;
	int currPos;
	WINDOW *workWnd;
	WINDOW *parentWnd;
} ;

char** readData(char *, int *);

void printFiles(direct *, int );

void run(direct *, direct *, direct *);

#endif
