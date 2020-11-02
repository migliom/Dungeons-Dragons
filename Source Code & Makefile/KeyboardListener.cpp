#include "KeyboardListener.hpp"

KeyboardListener::KeyboardListener(ObjectDisplayGrid* _grid) : grid(_grid) {}

void KeyboardListener::run(int *xP, int *yP) {
	//grid->writeLine(0, "Press 'x' to exit");
	running = true;
	char input;
	do {
		// wait for next input
		// lowercase so 'x' and 'X' are treated as the same
		input = std::tolower(getchar());

		switch (input) {
		// press X to stop
		case 'x':
			running = false;
			grid->writeLine(2, "Exiting...");
			break;
		case 'a':
			grid->moveLeft(xP, yP);
			break;
		case 's':
			grid->moveDown(xP, yP);
			break;
		case 'd':
			grid->moveRight(xP, yP);
			break;
		case 'w':
			grid->moveUp(xP, yP);
			break;
		default:
			// C is not happy about appending a character to a string apparently
			std::string message = "Unknown key '";
			message += input;
			grid->writeLine(30, message + "'");
			break;
		}
		grid->update();
	} while (running && input != EOF);
}