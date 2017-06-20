#include "../include/init.h"

int row, col;

void InitWindow(WINDOW** left_parent_wnd, WINDOW** left_wnd, 
				WINDOW** right_parent_wnd, WINDOW** right_wnd){

	*left_parent_wnd = newwin(row, col/2-1, 0, 0);
	box(*left_parent_wnd, '|', '-');
	*left_wnd = derwin(*left_parent_wnd, row-2, col/2-3, 1, 1);

	*right_parent_wnd = newwin(row, col/2, 0, col/2);
	box(*right_parent_wnd, '|', '-');
	*right_wnd = derwin(*right_parent_wnd, row-2, col/2-2, 1, 1);
}

void initDraw(){
	
	direct *right;
	direct *left;
	direct *current;
	
	right = malloc(sizeof(direct));
	left = malloc(sizeof(direct));
	current = malloc(sizeof(direct));
	initscr();

	left->names = readData(getenv("PWD"), &left->countNames);
	right->names = readData(getenv("HOME"), &right->countNames);
	strcpy(left->path,getenv("PWD"));
	strcpy(right->path,getenv("HOME"));

	getmaxyx(stdscr, row, col);
	
	InitWindow(&(left->parentWnd), &(left->workWnd), &(right->parentWnd), &(right->workWnd));

	curs_set(0);
	refresh();
	keypad(stdscr, TRUE);
	cbreak();
	start_color();
	noecho();

	

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
