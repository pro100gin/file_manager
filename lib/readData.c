#include "../include/readData.h"



char** readData(char *dir, int *fileCount){
    struct dirent **entry;
    char **names;
    int i = 1;
    (*fileCount)=0;
    (*fileCount) = scandir(dir, &entry, 0, alphasort);
    names = (char**)malloc((*fileCount)*sizeof(char*));
    for(i = 1; i <(*fileCount); ++i){
       names[i-1] = malloc(255);
       strcpy(names[i-1], entry[i]->d_name);
    }
    (*fileCount)--;
    return names;
}


void printFiles(direct *curr, int colorBG){
	int i = 0;
	wclear(curr->workWnd);
	for(i=0; i<curr->countNames; ++i){
		if(i == curr->currPos){
			wattron(curr->workWnd, COLOR_PAIR(colorBG));
			wprintw(curr->workWnd, "%40.40s\n", curr->names[i]);
			wattroff(curr->workWnd, COLOR_PAIR(colorBG));
		}
		else
			wprintw(curr->workWnd, "%40.40s\n", curr->names[i]);
	}
	wrefresh(curr->workWnd);
}

void run(direct *left, direct *right, direct *current){
	int ch =0;
	while((ch = getch()) != 'q'){
		switch(ch){
			case KEY_LEFT:
				if(current->workWnd == right->workWnd){
					printFiles(current, 2);
					right->currPos = current->currPos;
					current = left;
					printFiles(current, 1);
				}
				break;
			case KEY_RIGHT:
				if(current->workWnd == left->workWnd){
					printFiles(current, 2);
					left->currPos = current->currPos;
					current = right;
					printFiles(current, 1);
				}
				break;
			case KEY_UP:
			 	if(current->currPos > 0) current->currPos--;
				printFiles(current, 1);
				break;
			case KEY_DOWN:
				if(current->currPos < current->countNames - 1) current->currPos++;
				printFiles(current, 1);
				break;
			case 10:
				if(!chdir(current->path)){
					if(!chdir(current->names[current->currPos])){
						free(current->names);
						current->names=NULL;
						current->names = readData(".", &current->countNames);
						current->currPos = 0;
						getcwd(current->path, MAXDIR);
						printFiles(current, 1);
						if(current->workWnd == left->workWnd) left = current;
						else right = current;
					}
				}
				break;
			}
		}
}

