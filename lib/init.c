#include "../include/init.h"

void initDraw(){
	initscr();
	direct *right = malloc(sizeof(direct));
	direct *left = malloc(sizeof(direct));
	direct *current = malloc(sizeof(direct));
	left->names = readData(getenv("PWD"), &left->countNames);
	right->names = readData(getenv("HOME"), &right->countNames);
	strcpy(left->path,getenv("PWD"));
	strcpy(right->path,getenv("HOME"));

	int row, col;

	curs_set(0);
	refresh();
	keypad(stdscr, TRUE);
	cbreak();
	start_color();
	noecho();
	getmaxyx(stdscr, row, col);

	left->parentWnd = newwin(row, col/2-1, 0, 0);
	box(left->parentWnd, '|', '-');
	left->workWnd = derwin(left->parentWnd, row-2, col/2-3, 1, 1);

	right->parentWnd = newwin(row, col/2, 0, col/2);
	box(right->parentWnd, '|', '-');
	right->workWnd = derwin(right->parentWnd, row-2, col/2-2, 1, 1);

	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);

	printFiles(left, 1);
	printFiles(right, 2);

	wrefresh(left->parentWnd);
	wrefresh(right->parentWnd);

	current = left;


	run(left, right, current);

	echo();
	endwin();
}
