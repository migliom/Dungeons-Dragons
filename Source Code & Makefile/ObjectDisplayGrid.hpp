#pragma once
#include <string>
#include "GridChar.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <stdlib.h>
#include <time.h>

class ObjectDisplayGrid {
private:
	/** Keeps track of the characters on the screen */
	GridChar*** objectGrid;
	/** Keeps track of the consoles width and height */
	int height, width;

	/** Number of lines for message writing */
	int messages;

public:
	int messageHeight;
	int score;
	int hpMoveCounter = 0;
	int hallucinatioCount = 0;
	bool hall = false;
	/**
	 * Creates a new display grid using the given parameters and initializes ncurses.
	 * Screen height will be grid height + messages
	 * @param width     Screen width
	 * @param height    Grid height
	 * @param messages  Number of lines to reserve in the message area
	 */
	ObjectDisplayGrid(int width, int height, int messages, int gH, int tH);
	static std::mutex m;
	/** Object deconstructor, to delete the grid character matrix and free ncurses data */
	virtual ~ObjectDisplayGrid();

	/**
	 * Refreshes the grid display
	 */
	virtual void update();
	/**
	 * Adds an object to the display grid
	 * @param ch  Object to display
	 * @param x   X position
	 * @param y   Y position
	 */
	virtual void addObjectToDisplay(GridChar* ch, int x, int y);

	/**
	 * Writes a line of text to the screen at the given line relative to the bottom
	 * @param line    line number
	 * @param message message to write
	 * @param update  If true, immediately updates the screen
	 */
	virtual void writeLine(int line, std::string message);
	virtual void updateBottomDisplay(Player *player);
	virtual int moveUp(int*, int*, Player*, std::vector<Room*> rooms);
	virtual int moveLeft(int*, int*, Player*, std::vector<Room*> rooms);
	virtual int moveDown(int*, int*, Player*, std::vector<Room*> rooms);
	virtual int moveRight(int*, int*, Player*, std::vector<Room*> rooms);
	virtual char engageInCombat(Player*, Creature*, int, int, int, int);
	virtual void pickUpItem(Player*, int, int);
	virtual void dropItem(Player*, int, int, int);
	virtual void showCommands();
	virtual void detailedCommands(char);
	virtual void readScroll(Player*, int, std::vector<Room*>, int, int);
	virtual void wieldSword(Player*, int);
	virtual void wearArmor(Player*, int);
	virtual void takeArmorOff(Player*);
	virtual void removeSword(Player* player);
	virtual void Hallucinate(std::vector<Room*>, int, int);
	virtual void flushFloor(int, int, std::vector<Room*> rooms);
	virtual void teleport(Creature*, std::string);
};

