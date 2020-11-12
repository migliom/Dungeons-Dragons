#pragma once
#include <stack>
#include "Displayable.hpp"
#include "Item.hpp"
/**
 * This class in its current form is simply a wrapper around a character.
 * However, it can easily be expanded to include other behaviors for a grid character.
 */
class GridChar {
private:
	//char display;

public:
	//char display;
	std::stack <char> floorStack;
	std::stack <Displayable*> displayableStack;
	Displayable *dis;
	/**
	 * Creates a new grid character
	 * @param display Character to use for display
	 */
	GridChar(char, Displayable*);
	virtual void setChar(char x);
	/**
	 * Gets the character used to display this grid character
	 * @return  Character to display
	 */
	virtual char getChar();
	virtual Displayable* getDis();
};

