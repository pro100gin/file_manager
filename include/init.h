#ifndef INIT_H
#define INIT_H

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
#include "readData.h"

#define MAXDIR 255


void initDraw();
void InitWindow(WINDOW**, WINDOW**, WINDOW**, WINDOW**);

#endif
