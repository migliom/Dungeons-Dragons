#include "GridChar.hpp"

GridChar::GridChar(char _display){
	floorStack.push(_display);
}

char GridChar::getChar() {
	return floorStack.top();
}

void GridChar::setChar(char x){
	//display = x;
}
