#include "GridChar.hpp"

GridChar::GridChar(char _display, Creature *_dis, Item *item){
	floorStack.push(_display);
	displayableStack.push(_dis);
	itemStack.push(item);
	dis = _dis;
}

char GridChar::getChar() {
	return floorStack.top();
}

Creature* GridChar::getDis(){
	return displayableStack.top();
}

Item* GridChar::getItem(){
	return itemStack.top();
}
void GridChar::setChar(char x){
	//display = x;
}

void GridChar::popStacks(){
	if(!(floorStack.empty()))
		floorStack.pop();
	if(!(displayableStack.empty()))
		displayableStack.pop();
	if(!(itemStack.empty()))
		itemStack.pop();
}
