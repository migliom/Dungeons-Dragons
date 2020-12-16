#include "KeyboardListener.hpp"
#include <unistd.h>

KeyboardListener::KeyboardListener(ObjectDisplayGrid* _grid) : grid(_grid) {}
void KeyboardListener::run(int *xP, int *yP, Player *p, int topHeight, int gameHeight, std::vector<Room*> rooms) {
	//grid->writeLine(0, "Press 'x' to exit");
	int alive = 1;
	running = true;
	char input;
	char index;
	do {
		// wait for next input
		// lowercase so 'x' and 'X' are treated as the same
		//input = std::tolower(getchar());
		if(alive == 'L'){
			for (int i = 0; (i < 40); i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
			break;
		}
		input = getchar();
		switch (input) {
		// press X to stop
		case 'x':
			running = false;
			grid->writeLine(2, "Exiting...");
			//if die -> write line
			break;
		case 'h':
			alive=grid->moveLeft(xP, yP, p, rooms);
			break;
		case 'k':
			alive=grid->moveDown(xP, yP, p, rooms);
			break;
		case 'l':
			alive= grid->moveRight(xP, yP, p, rooms);
			break;
		case 'j':
			alive = grid->moveUp(xP, yP, p, rooms);
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
		case '?':
			grid->showCommands();
			break;
		case 'H':
			index = std::tolower(getchar());
			grid->detailedCommands(index);
			break;
		case 'r':
			index = std::tolower(getchar());
			grid->readScroll(p, index, rooms, *xP, *yP);
			break;
		case 't':
			index = std::tolower(getchar());
			grid->wieldSword(p, index);
			break;
		case 'c':
			grid->takeArmorOff(p);
			break;
		case 'e':
			grid->removeSword(p);
			break;
		case 'w':
			index = std::tolower(getchar());
			grid->wearArmor(p, index);
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