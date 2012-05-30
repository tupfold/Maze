#include <cstdlib>
#include <iostream>
#define initMaze(size) for (int i = 0; i < size; i++) for (int j = 0; j < size; j++) maze[i][j] = new tile;
#include <ncurses/ncurses.h>
#include <algorithm>
using namespace std;

struct tile {
	bool up;
	bool down;
	bool left;
	bool right;
	bool visited;
};

void write(char s, int x, int y);
void write(string s, int y, int x);
void printMaze();
void carveMaze(int x, int y);
void printTile(int x, int y);

const static int size = 4;
tile* maze[size][size];

int main() {
	initMaze(size);
	initscr();
	noecho();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			maze[j][i]->up = true;
			maze[j][i]->down = true;
			maze[j][i]->left = true;
			maze[j][i]->right = true;
			maze[j][i]->visited = false;
		}
	}
	printMaze();
	carveMaze(0,0);
	//cout << maze[0][0]->down << endl;
	printMaze();
	getch();
	endwin();
	return 0;
}
bool inBounds(int x, int y, char dir) {
	switch(dir) {
		case 'U':
			return y>0;
		case 'D':
			return y+1 < size;
		case 'L':
			return x > 0;
		case 'R':
			return x+1 < size;
	}
	return false;
}
void carveMaze(int x, int y) {
	char dir[] = {'U','D','L','R'};
	std::random_shuffle(dir,dir+size);
	tile *curTile = maze[x][y];
	curTile->visited = true;
	printTile(x,y);
	//write(x+48,1,17);
	//write(y+48,1,15);
	//getch();
	for (int i = 0; i < size; i++) {
		if (inBounds(x,y,dir[i])) {
			write(dir[i],0,15);
			//getch();
			switch(dir[i]) {
				case 'U': 
					if(maze[x][y-1]->visited == false) {
						curTile->up = false;
						maze[x][y-1]->down = false;
						carveMaze(x,y-1);
					}
					break;
				case 'D':
					if(maze[x][y+1]->visited == false) {
						curTile->down = false;
						maze[x][y+1]->up = false;
						carveMaze(x,y+1);
					}
					break;
				case 'L':
					if(maze[x-1][y]->visited == false) {
						curTile->left = false;
						maze[x-1][y]->right = false;
						carveMaze(x-1,y);
					}
					break;
				case 'R':
					if(maze[x+1][y]->visited == false) {
						curTile->right = false;
						maze[x+1][y]->left = false;
						carveMaze(x+1,y);
					}
					break;
			}
		}
	}
}
void printTile(int x, int y) {
	tile *cur = maze[x][y];
	int offsetX = 1 + (2*x); 
	write(offsetX+48, 4,15)
	if(!cur->up) 		write(' ', y-1, offsetX);
	if(!cur->down) 	write(' ', y+1, offsetX);
	if(!cur->right)  	write(' ', y, offsetX+1);
	if(!cur->left)		write(' ', y, offsetX-1);
	move(y,offsetX);
	getch();
}
void printMaze() {
	int curX = 1, curY = 1;
	for (int i = 0; i < size; i++) {
		curY = 1;
		for (int j = 0; j < size; j++) {
			tile *cur = maze[i][j];
			if(cur->up) 		write('_', curY-1, curX); else write(' ', curY-1, curX);
			if(cur->down) 	write('_',curY, curX); else write(' ',curY, curX);
			if(cur->right)  	write('|',curY,curX+1); else write(' ',curY,curX+1);
			if(cur->left) 		write('|', curY,curX-1);else write(' ', curY,curX-1);
			curY++;
			//getch();
		}
		curX+=2;
	}
	refresh();
}
void write(char s, int y, int x) {
	move(y, x);
	addch(s);
}
void write(string s, int y, int x) {
	move(y,x);
	for (int i = 0; i < s.length();i++) {
		addch(s[i]);
	}
}		