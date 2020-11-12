#include "GridChar.hpp"

GridChar::GridChar(char _display, Displayable *_dis){
	floorStack.push(_display);
	displayableStack.push(_dis);
	dis = _dis;
}

char GridChar::getChar() {
	return floorStack.top();
}

Displayable* GridChar::getDis(){
	return displayableStack.top();
}

void GridChar::setChar(char x){
	//display = x;
}
