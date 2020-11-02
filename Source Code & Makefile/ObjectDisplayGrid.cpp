#include <curses.h>
#include "ObjectDisplayGrid.hpp"
#ifdef _WIN32
	#include <windows.h>
#endif

// I am not certain about the threadsafety of ncurse methods.
// They appear to work just fine in my testing, but that is likely as it always sets the cursor position before writing

ObjectDisplayGrid::ObjectDisplayGrid(int _width, int _height, int _messages) : width(_width), height(_height), messages(_messages) {	
	// create the 2D array of grid characters
	// note if you want to write messages instead, ncurses
	objectGrid = new GridChar**[width];
	for (int i = 0; i < width; i++) {
		objectGrid[i] = new GridChar*[height];
		for (int j = 0; j < height; j++) {
			objectGrid[i][j] = NULL;
		}
	}
	// initialize ncurses

	// set command window size if running on windows, useful when running in Visual Studio
	// as far as I am aware, no way to do this on linux
	#ifdef _WIN32
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD size = { (short)width, (short)(height + messages) };
		SMALL_RECT DisplayArea = { 0, 0, (short)(size.X - 1), (short)(size.Y - 1) };
		SetConsoleScreenBufferSize(handle, size);
		SetConsoleWindowInfo(handle, TRUE, &DisplayArea);
	#endif
	
	// initializes ncurses
	initscr();
	// makes characters typed immediately available, instead of waiting for enter to be pressed
	cbreak(); 
	// stops typed characters from being shown, makes it easier to get keypresses
	noecho();
	// clears the screen to start
	clear();
}

ObjectDisplayGrid::~ObjectDisplayGrid() {
	// free memory from the dynamically sized object grid
	for (int i = 0; i < width; i++) {
		// delete all character objects in the grid
		for (int j = 0; j < height; j++) {
			delete objectGrid[i][j];
		}
		// delete the column
		delete[] objectGrid[i];
	}
	// delete the array of columns
	delete[] objectGrid;
	objectGrid = NULL;

	// free ncurses data
	endwin();
}

void ObjectDisplayGrid::addObjectToDisplay(GridChar* ch, int x, int y) {
	// note grid objects start from 0,0 and go until width,height
	// x between 0 and width
	//m.lock();
	if ((0 <= x) && (x < width)) {
		// y between 0 and height
		if ((0 <= y) && (y < height)) {
			// delete existing character if present
			if (objectGrid[x][y] != NULL) {
				GridChar *chr = objectGrid[x][y];
				char character = chr->display;
				if(character == 'x'){
					delete ch;
					character = '+';
					GridChar* ch = new GridChar(character);
				}
				delete objectGrid[x][y];
			}

			// add new character to the internal character list
			objectGrid[x][y] = ch;
			// draws the character on the screen, note it is relative to 0,0 of the terminal
			mvaddch(y, x, ch->getChar());
		}
	}
	//m.unlock();
}

void ObjectDisplayGrid::update() {
	// refreshes ncurses
	refresh();
}

void ObjectDisplayGrid::writeLine(int line, std::string message) {
	// messages start from 0, height and go until width,(height + messages)
	mvaddstr(line, 0, message.c_str());
	// clear after what we wrote to EOL
	clrtoeol();
}

void ObjectDisplayGrid::moveUp(int *xP, int *yP){
	int x = *xP;
	int y = *yP;
	if (objectGrid[x][y-1] != NULL) {
		GridChar *chr1 = objectGrid[x][y-1];
		char character1 = chr1->display;
		if(character1 == 'x' || character1 == 'S'||  character1 == 'T' || character1 == 'H'){
				return;
		}
		else{
			*yP -= 1;
			GridChar *checkX2;
			char check;
			GridChar* insert;
			char insertChar;
			if(character1 == '#'){
				checkX2 = objectGrid[x][y+1]; //check what is behind your character
				if(checkX2 == NULL){
					//std::cout << "TEST" << std::endl;
					addObjectToDisplay(new GridChar('#'), x, y);
					addObjectToDisplay(new GridChar('@'), x, y-1); 
					return;
				}
				check = checkX2->display;
				if(check == '+'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check == '#'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x, y-1);
				return;
			}
			else if(character1 == '+'){
				checkX2 = objectGrid[x][y+1]; //check what is behind your character
				if(checkX2 == NULL){
					addObjectToDisplay(new GridChar('#'), x, y);
					addObjectToDisplay(new GridChar('@'), x, y-1); 
					return;
				}
				else{
					check = checkX2->display;
					if(check != '#'){
						addObjectToDisplay(new GridChar('.'), x, y);
					}
					else if(check == '#'){
						addObjectToDisplay(new GridChar('#'), x, y);
					}
				}
					addObjectToDisplay(new GridChar('@'), x, y-1);
					return;
			}
			else if(character1 == '.'){
				checkX2 = objectGrid[x][y+1]; //check what is behind your character
				check = checkX2->display;
				if(check == '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('.'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x, y-1);
				return;
			}
		}
	}
}
void ObjectDisplayGrid::moveLeft(int *xP, int *yP){
	int x = *xP;
	int y = *yP;
	if (objectGrid[x-1][y] != NULL) {
		GridChar *chr1 = objectGrid[x-1][y];
		char character1 = chr1->display;
		if(character1 == 'x' || character1 == 'S'||  character1 == 'T' || character1 == 'H'){
				return;
		}
		else{
			*xP -= 1;
			GridChar *checkX2;
			char check;
			GridChar* insert;
			char insertChar;
			if(character1 == '#'){
				checkX2 = objectGrid[x+1][y]; //check what is behind your character
				if(checkX2 == NULL){
					//std::cout << "TEST" << std::endl;
					addObjectToDisplay(new GridChar('#'), x, y);
					addObjectToDisplay(new GridChar('@'), x-1, y); 
					return;
				}
				check = checkX2->display;
				if(check == '+'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check == '#'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x-1, y);
				return;
			}
			else if(character1 == '+'){
				checkX2 = objectGrid[x+1][y]; //check what is behind your character
				if(checkX2 == NULL){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				else{
					check = checkX2->display;
					if(check != '#'){
						addObjectToDisplay(new GridChar('.'), x, y);
					}
					else if(check == '#'){
						addObjectToDisplay(new GridChar('#'), x, y);
					}
				}
					addObjectToDisplay(new GridChar('@'), x-1, y);
					return;
			}
			else if(character1 == '.'){
				checkX2 = objectGrid[x+1][y]; //check what is behind your character
				check = checkX2->display;
				if(check == '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('.'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x-1, y);
				return;
			}
		}
	}
}
void ObjectDisplayGrid::moveDown(int *xP, int *yP){
	int x = *xP;
	int y = *yP;
	if (objectGrid[x][y+1] != NULL) {
		GridChar *chr1 = objectGrid[x][y+1];
		char character1 = chr1->display;
		if(character1 == 'x' || character1 == 'S'||  character1 == 'T' || character1 == 'H'){
				return;
		}
		else{
			*yP += 1;
			GridChar *checkX2;
			char check;
			GridChar* insert;
			char insertChar;
			if(character1 == '#'){
				checkX2 = objectGrid[x][y-1]; //check what is behind your character
				if(checkX2 == NULL){
					addObjectToDisplay(new GridChar('#'), x, y);
					addObjectToDisplay(new GridChar('@'), x, y+1); 
					return;
				}
				check = checkX2->display;
				if(check == '+'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check == '#'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x, y+1);
				return;
			}
			else if(character1 == '+'){
				checkX2 = objectGrid[x][y-1]; //check what is behind your character
				if(checkX2 == NULL){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				else{
					check = checkX2->display;
					if(check != '#'){
						addObjectToDisplay(new GridChar('.'), x, y);
					}
					else if(check == '#'){
						addObjectToDisplay(new GridChar('#'), x, y);
					}
				}
					addObjectToDisplay(new GridChar('@'), x, y+1);
					return;
			}
			else if(character1 == '.'){
				checkX2 = objectGrid[x][y-1]; //check what is behind your character
				check = checkX2->display;
				if(check == '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('.'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x, y+1);
				return;
			}
		}
	}
}
void ObjectDisplayGrid::moveRight(int *xP, int *yP){
	int x = *xP;
	int y = *yP;
	if (objectGrid[x+1][y] != NULL) {
		GridChar *chr1 = objectGrid[x+1][y];
		char character1 = chr1->display;
		if(character1 == 'x' || character1 == 'S'||  character1 == 'T' || character1 == 'H'){
				return;
		}
		else{
			*xP += 1;
			GridChar *checkX2;
			char check;
			GridChar* insert;
			char insertChar;
			if(character1 == '#'){
				checkX2 = objectGrid[x-1][y]; //check what is behind your character
				if(checkX2 == NULL){
					addObjectToDisplay(new GridChar('#'), x, y);
					addObjectToDisplay(new GridChar('@'), x+1, y); 
					return;
				}
				check = checkX2->display;
				if(check == '+'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check == '#'){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x+1, y);
				return;
			}
			else if(character1 == '+'){
				checkX2 = objectGrid[x-1][y]; //check what is behind your character
				if(checkX2 == NULL){
					addObjectToDisplay(new GridChar('#'), x, y);
				}
				else{
					check = checkX2->display;
					if(check != '#'){
						addObjectToDisplay(new GridChar('.'), x, y);
					}
					else if(check == '#'){
						addObjectToDisplay(new GridChar('#'), x, y);
					}
				}
					addObjectToDisplay(new GridChar('@'), x+1, y);
					return;
			}
			else if(character1 == '.'){
				checkX2 = objectGrid[x-1][y]; //check what is behind your character
				check = checkX2->display;
				if(check == '#'){
					addObjectToDisplay(new GridChar('+'), x, y);
				}
				else if(check != '#'){
					addObjectToDisplay(new GridChar('.'), x, y);
				}
				addObjectToDisplay(new GridChar('@'), x+1, y);
				return;
			}
		}
	}
}
