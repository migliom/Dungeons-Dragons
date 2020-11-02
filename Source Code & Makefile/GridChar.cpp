#include "GridChar.hpp"

GridChar::GridChar(char _display) : display(_display) {}

char GridChar::getChar() {
	return display;
}

void GridChar::setChar(char x){
	display = x;
}
