#include "../include/readData.h"
#include "../include/init.h"


char** readData(char *dir, int *fileCount){
    struct dirent **entry;
    char **names;
    int i = 1;
    (*fileCount)=0;
    (*fileCount) = scandir(dir, &entry, 0, alphasort);
    names = malloc((*fileCount)*sizeof(char*));
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
	int pid;
	static char* arg[] = {"/work/text_editor/lib/of", "./text", NULL};
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
						if(getcwd(current->path, MAXDIR)==NULL){
							perror("getcwd error");
							return;
						}
						printFiles(current, 1);
						if(current->workWnd == left->workWnd) left = current;
						else right = current;
					}
					else{
						if((pid=fork())==0){
							/*strcpy(arg[1], current->names[current->currPos]);*/
							execvp(arg[0], arg);
						}
						wait(0);
						wrefresh(current->workWnd);
					}
				}

				break;
			}
		}
}

