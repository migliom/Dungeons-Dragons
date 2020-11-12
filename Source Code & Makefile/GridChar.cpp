#include "GridChar.hpp"

GridChar::GridChar(char _display, Displayable *dis){
	floorStack.push(_display);
	displayableStack.push(dis);
}

char GridChar::getChar() {
	return floorStack.top();
}

void GridChar::setChar(char x){
	//display = x;
}
