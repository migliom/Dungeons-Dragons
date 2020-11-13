#include "KeyboardListener.hpp"
#include <unistd.h>

KeyboardListener::KeyboardListener(ObjectDisplayGrid* _grid) : grid(_grid) {}
void KeyboardListener::run(int *xP, int *yP, Player *p) {
	//grid->writeLine(0, "Press 'x' to exit");
	int alive = 1;
	running = true;
	char input;
	char index;
	do {
		// wait for next input
		// lowercase so 'x' and 'X' are treated as the same
		input = std::tolower(getchar());

		switch (input) {
		// press X to stop
		case 'x':
			running = false;
			grid->writeLine(2, "Exiting...");
			//if die -> write line
			break;
		case 'h':
			grid->moveLeft(xP, yP, p);
			break;
		case 'k':
			grid->moveDown(xP, yP, p);
			break;
		case 'l':
			grid->moveRight(xP, yP, p);
			break;
		case 'j':
			alive = grid->moveUp(xP, yP, p);
			break;
		case 'p':
			grid->pickUpItem(p,*xP,*yP);
			break;
		case 'd':
			index = std::tolower(getchar());
			grid->dropItem(p, index, *xP, *yP);
			break;
		case 'i':
			grid->updateBottomDisplay(p);
			break;
		default:
			// C is not happy about appending a character to a string apparently
			std::string message = "Unknown key '";
			message += input;
			grid->writeLine(30, message + "'");
			break;
		}
		grid->update();
		if(!alive){
			grid->writeLine(2, "You died......");
			usleep(5000000);
		}
	} while (running && input != EOF && alive);
}