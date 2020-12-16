#include <curses.h>
#include <ctime>
#include "ObjectDisplayGrid.hpp"
#include <unistd.h>
#ifdef _WIN32
	#include <windows.h>
#endif
class Room;
static int damageCalc(int damage){
    srand (time(NULL));
    return (rand() % damage + 1);
}
void ObjectDisplayGrid::teleport(Creature *mon, std::string name){
	if(name.compare("Snake") == 0){
		addObjectToDisplay(new GridChar('S', mon, NULL), 18, 14);
	}else if(name.compare("Hobgoblin") == 0){
		addObjectToDisplay(new GridChar('H', mon, NULL), 18, 14);
	}else if(name.compare("Troll") == 0){
		addObjectToDisplay(new GridChar('T', mon, NULL), 18, 14);
	}
	return;
}
char ObjectDisplayGrid::engageInCombat(Player *p, Creature *dp, int xP, int yP, int x, int y){
	int teleport = 0;
    int monsterHP = dp->hitpoints;
    int playerHP = p->hitpoints;
    int pmaxHit = p->maxHP;
    int monsterMaxHit = dp->maxHP;
    if(playerHP > 0 && monsterHP > 0){
        int pDamage = damageCalc(pmaxHit) + 4;
        int monsterDamage = damageCalc(monsterMaxHit);
		if(p->getSword() != NULL){
			Sword *s = p->getSword();
			pDamage += s->intValue;
		}
		if(p->getArmor() != NULL){
			Armor *a = p->getArmor();
			monsterDamage -= a->intValue;
			if(monsterDamage < 0) {monsterDamage = 0;}
		}
		p->hitpoints -= monsterDamage;
        dp->hitpoints -= pDamage;
		for(CreatureAction* cAA: p->returnHitActions()){
			std::string name = cAA->getName();
			std::string message = cAA->getMessage();
			if(name.compare("DropPack") == 0){
				dropItem(p, '1', x, y);
				writeLine(1, message);
				update();
				for (int i = 0; (i < 25); i++)
                	std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
		}
		if(dp->hitpoints > 0){
			for(CreatureAction * pA : dp->returnHitActions()){
				std::string name1 = pA->getName();
				if(name1.compare("Teleport") == 0){
					//teleport(pA, name1);
					addObjectToDisplay(new GridChar('T', dp, NULL), 19, 16);
					std::string message1 = pA->getMessage();
					writeLine(1, message1);
					update();
					objectGrid[xP][yP]->popStacks();
					mvaddch(yP, xP, objectGrid[xP][yP]->getChar());
					for (int i = 0; (i < 30); i++)
						std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
			}
		}
		writeLine(0, std::to_string(p->hitpoints));
        writeLine(messageHeight+1, "You did " + std::to_string(pDamage) + " damage to the monster.");
		writeLine(messageHeight+2, "The monster did " + std::to_string(monsterDamage) + " damage to you.");
		update();
        usleep(30000);
    }
    if(dp->hitpoints <= 0){
        //execute monster death message
		objectGrid[xP][yP]->popStacks();
		mvaddch(yP, xP, objectGrid[xP][yP]->getChar());
		update();
		for(CreatureAction* cAA: dp->returnDeathActions()){
			writeLine(1, cAA->getMessage());
			for (int i = 0; (i < 5); i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		return 'W';
    	}	
	}
    if(p->hitpoints <= 0){
        for(CreatureAction* cAA: p->returnDeathActions()){
				writeLine(1, "Player is killed");
			for (int i = 0; (i < 5); i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			if(cAA->getName().compare("ChangeDisplayedType") == 0){
				objectGrid[x][y]->floorStack.push('?');
				mvaddch(y, x, objectGrid[x][y]->getChar());
				update();
			}
		return 'L';
    	}
	}
	return 'N';
}

ObjectDisplayGrid::ObjectDisplayGrid(int _width, int _height, int _messages, int gH, int tH) : width(_width), height(_height), messages(_messages), messageHeight(gH+tH), score(0) {	
	// create the 2D array of grid characters
	// note if you want to write messages instead, ncurses
	objectGrid = new GridChar**[width];
	for (int i = 0; i < width; i++) {
		objectGrid[i] = new GridChar*[height];
		for (int j = 0; j < height; j++) {
			objectGrid[i][j] = NULL;
		}
	}
	// initialize ncurses

	// set command window size if running on windows, useful when running in Visual Studio
	// as far as I am aware, no way to do this on linux
	#ifdef _WIN32
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD size = { (short)width, (short)(height + messages) };
		SMALL_RECT DisplayArea = { 0, 0, (short)(size.X - 1), (short)(size.Y - 1) };
		SetConsoleScreenBufferSize(handle, size);
		SetConsoleWindowInfo(handle, TRUE, &DisplayArea);
	#endif
	
	// initializes ncurses
	initscr();
	// makes characters typed immediately available, instead of waiting for enter to be pressed
	cbreak(); 
	// stops typed characters from being shown, makes it easier to get keypresses
	noecho();
	// clears the screen to start
	clear();
}

ObjectDisplayGrid::~ObjectDisplayGrid() {
	// free memory from the dynamically sized object grid
	for (int i = 0; i < width; i++) {
		// delete all character objects in the grid
		for (int j = 0; j < height; j++) {
			delete objectGrid[i][j];
		}
		// delete the column
		delete[] objectGrid[i];
	}
	// delete the array of columns
	delete[] objectGrid;
	objectGrid = NULL;

	// free ncurses data
	endwin();
}

void ObjectDisplayGrid::addObjectToDisplay(GridChar* ch, int x, int y) {
	// note grid objects start from 0,0 and go until width,height
	// x between 0 and width
	//m.lock();
	if ((0 <= x) && (x < width)) {
		// y between 0 and height
		if ((0 <= y) && (y < height)) {
			// delete existing character if present
			if (objectGrid[x][y] != NULL) {
				GridChar *chr = objectGrid[x][y];
				char character = chr->getChar();
				if(character == 'x'){
					if(ch->getChar() == '#'){
						delete ch;
						character = '+';
						GridChar* ch = new GridChar(character, NULL, NULL);
						delete objectGrid[x][y];
						objectGrid[x][y] = ch;
						mvaddch(y, x, ch->getChar());
						update();
						return;
					}
				}
				objectGrid[x][y]->itemStack.push((ch->getItem())); //item
				objectGrid[x][y]->displayableStack.push((ch->getDis()));
				objectGrid[x][y]->floorStack.push((ch->getChar()));
			}
			// add new character to the internal character list
			else
				objectGrid[x][y] = ch;
			// draws the character on the screen, note it is relative to 0,0 of the terminal
			mvaddch(y, x, ch->getChar());
		}
	}
	update();
}

void ObjectDisplayGrid::update() {
	// refreshes ncurses
	refresh();
}

void ObjectDisplayGrid::writeLine(int line, std::string message) {
	// messages start from 0, height and go until width,(height + messages)
	std::string newMessage = "";
	if(line == 0){
		newMessage += "HP: " + message + " Score: " + std::to_string(score);
		score += 10;
		mvaddstr(line, 0, newMessage.c_str());
		clrtoeol();
		return;
	}
	if(line == 1){
		newMessage += "Message: " + message;
		mvaddstr(line, 0, newMessage.c_str());
		clrtoeol();
		return;
	}
	if(line == (messageHeight)){
		newMessage += "Pack: " + message;
		mvaddstr(line, 0, newMessage.c_str());
		clrtoeol();
		return;
	}
	if(line == (messageHeight + 1)){
		newMessage += "Info: " + message;
		mvaddstr(line, 0, newMessage.c_str());
		clrtoeol();
		return;
	}
	mvaddstr(line, 0, message.c_str());
	// clear after what we wrote to EOL
	clrtoeol();
}

void ObjectDisplayGrid::updateBottomDisplay(Player *player){
	std::vector<Item*> items = player->getPack();
	std::string itemStr = "";
	int index = 1;
	if(!items.empty()){
		for(Item * item: items){
			update();
			itemStr += std::to_string(index);
			itemStr += ". ";
			index++;
			itemStr += item->getItemName(2);
			//std::cout << "An item is here: " << itemStr<< std::endl;
			itemStr += ", ";
		}
	}
	//std::cout << "The line be: " << itemStr << std::endl;
	writeLine(messageHeight, itemStr);
	update();
}
void ObjectDisplayGrid::flushFloor(int x, int y, std::vector<Room*> rooms){
	Creature *c = objectGrid[x][y]->getDis();
	Player *p = dynamic_cast<Player*>(c);
	objectGrid[x][y]->popStacks();
	int topH = 2;
	for(Room *room: rooms){
        int xX = room->getPosX();
        int yY = room->getPosY();
        for(int i = xX; i < (room->getWidth()+xX); i++){
            for(int j = yY+topH; j < (room->getHeight()+yY+topH); j++){ 
				for(int k = 0; k < 5; k++)
					objectGrid[i][j]->popStacks();
				mvaddch(j, i, objectGrid[i][j]->getChar());
				writeLine(27, "here");
				update();
            } 
        }
        update();
    }
	addObjectToDisplay(new GridChar('@', p, NULL), x, y);
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
int ObjectDisplayGrid::moveUp(int *xP, int *yP, Player *p, std::vector<Room*> rooms){
	int x = *xP;
	int y = *yP;
	if(objectGrid[x][y-1] == NULL) return 1;  
	if (objectGrid[x][y-1] != NULL) {
		GridChar *chr1 = objectGrid[x][y-1];
		char character1 = chr1->getChar();
		if(character1 == 'x'){
				return 1;
		}
		else if(character1 == 'T' || character1 == 'S' || character1 == 'H'){
			Creature *monster = objectGrid[*xP][y-1]->getDis();
			if(monster != NULL){
				char win_lose = engageInCombat(p, monster, *xP, *yP-1, *xP, *yP);
				return win_lose;
			}
		}
		else{
			*yP -= 1;
			addObjectToDisplay(new GridChar('@', p, NULL), x, y-1);
			GridChar *checkX2 = objectGrid[x][y];
			checkX2->popStacks();
			mvaddch(y, x, checkX2->getChar());
			if(++hpMoveCounter == p->hpMoves){
				hpMoveCounter = 0;
				++(p->hitpoints);
				writeLine(0, std::to_string(p->hitpoints));
			}
			if(hall){
				writeLine(messageHeight+1, "Number of moves left in hallucination: " + std::to_string(--hallucinatioCount));
				if(hallucinatioCount == 0){
					hall = false;
					flushFloor(*xP, *yP, rooms);
				}
				else{
					Hallucinate(rooms, *xP, *yP);
				}
			}
			return 1;
		}
	}
}
int ObjectDisplayGrid::moveLeft(int *xP, int *yP, Player *p, std::vector<Room*> rooms){
	int x = *xP;
	int y = *yP;
	if(objectGrid[x-1][y] == NULL) return 1;  
	if (objectGrid[x-1][y] != NULL) {
		GridChar *chr1 = objectGrid[x-1][y];
		char character1 = chr1->getChar();
		if(character1 == 'x'){
				return 1;
		}
		else if(character1 == 'T' || character1 == 'S' || character1 == 'H'){
			Creature *monster = objectGrid[x-1][y]->getDis();
			char win_lose = engageInCombat(p, monster, x-1, y, *xP, *yP);
			return win_lose;
		}
		else{
			*xP -= 1;
			addObjectToDisplay(new GridChar('@', p, NULL), x-1, y);
			GridChar *checkX2 = objectGrid[x][y];
			checkX2->popStacks();
			mvaddch(y, x, checkX2->getChar());
			if(++hpMoveCounter == p->hpMoves){
				hpMoveCounter = 0;
				++(p->hitpoints);
				writeLine(0, std::to_string(p->hitpoints));
			}
			if(hall){
				writeLine(messageHeight+1, "Number of moves left in hallucination: " + std::to_string(--hallucinatioCount));
				if(hallucinatioCount == 0){
					hall = false;
					flushFloor(*xP, *yP, rooms);
				}
				else{
					Hallucinate(rooms, *xP, *yP);
				}
			}
			return 1;
		}
	}
}
int ObjectDisplayGrid::moveDown(int *xP, int *yP, Player *p, std::vector<Room*> rooms){
	int x = *xP;
	int y = *yP;
	if(objectGrid[x][y+1] == NULL) return 1;  
	if (objectGrid[x][y+1] != NULL) {
		GridChar *chr1 = objectGrid[x][y+1];
		char character1 = chr1->getChar();
		if(character1 == 'x'){
				return 1;
		}
		else if(character1 == 'T' || character1 == 'S' || character1 == 'H'){
			Creature *monster = objectGrid[*xP][y+1]->getDis();
			char win_lose = engageInCombat(p, monster, x, y+1, x, y);
			return win_lose;
		}
		else{
			*yP += 1;
			addObjectToDisplay(new GridChar('@', p, NULL), x, y+1);
			GridChar *checkX2 = objectGrid[x][y];
			checkX2->popStacks();
			mvaddch(y, x, checkX2->getChar());
			if(++hpMoveCounter == p->hpMoves){
				hpMoveCounter = 0;
				++(p->hitpoints);
				writeLine(0, std::to_string(p->hitpoints));
			}
			if(hall){
				writeLine(messageHeight+1, "Number of moves left in hallucination: " + std::to_string(--hallucinatioCount));
				if(hallucinatioCount == 0){
					hall = false;
					flushFloor(*xP, *yP, rooms);
				}
				else{
					Hallucinate(rooms, *xP, *yP);
				}
			}
			return 1;
		}
	}
}
int ObjectDisplayGrid::moveRight(int *xP, int *yP, Player *p, std::vector<Room*> rooms){
	int x = *xP;
	int y = *yP;
	if(objectGrid[x+1][y] == NULL) return 1;  
	if (objectGrid[x+1][y] != NULL) {
		GridChar *chr1 = objectGrid[x+1][y];
		char character1 = chr1->getChar();
		if(character1 == 'x'){
				return 1;
		}
		else if(character1 == 'T' || character1 == 'S' || character1 == 'H'){
			Creature *monster = objectGrid[x+1][y]->getDis();
			char win_lose = engageInCombat(p, monster, x+1, y, x, y);
			return win_lose;
		}
		else{
			*xP += 1;
			addObjectToDisplay(new GridChar('@', p, NULL), x+1, y);
			GridChar *checkX2 = objectGrid[x][y];
			checkX2->popStacks();
			mvaddch(y, x, checkX2->getChar());
			if(++hpMoveCounter == p->hpMoves){
				hpMoveCounter = 0;
				++(p->hitpoints);
				writeLine(0, std::to_string(p->hitpoints));
			}
			if(hall){
				writeLine(messageHeight+1, "Number of moves left in hallucination: " + std::to_string(--hallucinatioCount));
				if(hallucinatioCount == 0){
					hall = false;
					flushFloor(*xP, *yP, rooms);
				}
				else{
					Hallucinate(rooms, *xP, *yP);
				}
			}
			return 1;
		}
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void ObjectDisplayGrid::pickUpItem(Player* player, int x, int y){
	char waste = objectGrid[x][y]->getChar(); //will be @
	objectGrid[x][y]->floorStack.pop(); //Get rid of @
	char character1 = objectGrid[x][y]->getChar(); //should be item if there is one

	for(int i = 0; i < 12; i++)
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
	updateBottomDisplay(player);
	update();
	if(character1 == '?' || character1 == ')' || character1 == ']'){
		Item *itemWaste = objectGrid[x][y]->getItem(); //NULL with @ on top
		objectGrid[x][y]->floorStack.pop(); 
		objectGrid[x][y]->itemStack.pop(); //get rid of @ item
		Item *item = objectGrid[x][y]->getItem();
		if(item == NULL){
			writeLine(24, "No item at current location.");
			update();
		}
		else{
			player->addToPack(item);
		}
		objectGrid[x][y]->itemStack.pop(); //get rid of item
		objectGrid[x][y]->itemStack.push(itemWaste); //add NULL back to stack
	}
	objectGrid[x][y]->floorStack.push(waste);
	return;
}

void ObjectDisplayGrid::dropItem(Player *player, int index, int x, int y){
	Item *item = player->dropFromPack(index);
	if(item == NULL){
		writeLine(1, "There is no item at index: " + std::to_string(index-'0') + "!");
		return;
	}
	objectGrid[x][y]->popStacks();
	char c;
	Scroll *s = dynamic_cast<Scroll*>(item);
	if(s){
		c = '?';
		writeLine(1, "You dropped your scroll!");
		objectGrid[x][y]->itemStack.push(s);
		objectGrid[x][y]->floorStack.push(c);
		objectGrid[x][y]->displayableStack.push(NULL);
		//grid->addObjectToDisplay(new GridChar(c, NULL, s), posX, posY+topH);
	}
	Armor *a = dynamic_cast<Armor*>(item);
	if(a){
		c = ']';
		writeLine(1, "You dropped your armor!");
		objectGrid[x][y]->itemStack.push(a);
		objectGrid[x][y]->floorStack.push(c);
		objectGrid[x][y]->displayableStack.push(NULL);
		//grid->addObjectToDisplay(new GridChar(c, NULL, s), posX, posY+topH);
	}
	Sword *sw = dynamic_cast<Sword*>(item);
	if(sw){
		c = ')';
		writeLine(1, "You dropped your sword!");
		objectGrid[x][y]->itemStack.push(sw);
		objectGrid[x][y]->floorStack.push(c);
		objectGrid[x][y]->displayableStack.push(NULL);
		//grid->addObjectToDisplay(new GridChar(c, NULL, s), posX, posY+topH);
	}
	objectGrid[x][y]->itemStack.push(NULL);
	objectGrid[x][y]->floorStack.push('@');
	objectGrid[x][y]->displayableStack.push(player);
}
void ObjectDisplayGrid::showCommands(){
	std::string message = "Available commands: 'Change, or take off armor: c', 'd', 'E <y>', 'H <command>', 'i', 'p', 'r', 'T', 'w'";
	writeLine(messageHeight+1, message);
}
void ObjectDisplayGrid::detailedCommands(char command){
	std::string message = "";
	switch(command){
		case 'c': 	
			message += "Change/take off armor";
			break;
		case 'd': 	
			message += "Drop Item (must give index number)";
			break;
		case 'E': 	
			message += "End Game (must type Y/y to end)";
			break;
		case '?': 	
			message += "Display all commands";
			break;
		case 'i': 	
			message += "Show/update inventory";
			break;
		case 'p': 	
			message += "Pick up Item";
			break;
		case 'r': 	
			message += "Read scroll (must give index)";
			break;
		case 'T': 	
			message += "Take weapon out of pack (must give index)";
			break;
		case 'w': 	
			message += "Wear armor ((must give index)";
			break;
	}
	writeLine(messageHeight+1, message);
}

void ObjectDisplayGrid::Hallucinate(std::vector<Room*> rooms, int x, int y){
	char characters[14] = {'!', '$', '%', '^', '&', '*', '=', '-', 'F', 'A', '/', 'W', 'Q'};
	//Creature *c = objectGrid[x][y]->getDis();
	//Player *p = dynamic_cast<Player*>(c);
	//objectGrid[x][y]->popStacks();
	std::srand(std::time(0)); 
	char rando = ' ';
	int topH = 2;
    for(Room *room: rooms){
        int x = room->getPosX();
        int y = room->getPosY();
        for(int i = x; i < (room->getWidth()+x); i++){
            for(int j = y+topH; j < (room->getHeight()+y+topH); j++){ 
				rando = characters[(std::rand() % 13)]; 
				addObjectToDisplay(new GridChar(rando, NULL, NULL), i, j);
            } 
        }
		//addObjectToDisplay(new GridChar('@', p, NULL), x, y);
        update();
    }
}
void ObjectDisplayGrid::readScroll(Player* player, int index, std::vector<Room*> rooms, int x, int y){
	Item *sc = player->scrollFromPack(index);
	Scroll *s = dynamic_cast<Scroll*>(sc);
	if(s == NULL){
		writeLine(27, "Invalid scroll");
	}
	if(s){
		for(ItemAction * iA: s->getItemActions()){
			std::string name = iA->getName();
			std::string message = iA->getMessage();
			message += ". It is of value: " + std::to_string(iA->getIntValue()) + ". Name: " + name;
			writeLine(1, message);
			if(name.compare("BlessArmor") == 0){
				if(player->getArmor() != NULL){
					int blessAmt = iA->getIntValue();
					Armor *arm = player->getArmor();
					arm->intValue -= blessAmt;
					player->setArmor(arm);
					if(blessAmt < 0)	writeLine(messageHeight+1, "You have cursed the armor with " + std::to_string(blessAmt) + " hitpoints!");
					else	
						writeLine(messageHeight+1, "You have blessed the armor with " + std::to_string(blessAmt) + " hitpoints!");
				}
				else
					writeLine(messageHeight+1, "There is no armor equipped, scroll has no effect");
			}
			else if(name.compare("Hallucinate") == 0){
				hallucinatioCount = iA->getIntValue();
				writeLine(messageHeight+1, "Number of moves left in hallucination: " + std::to_string(hallucinatioCount));
				hall = true;
				Hallucinate(rooms, x, y);
				return;
			}
		}
		player->dropFromPack(index);
		return;
	}
	else{
		writeLine(messageHeight+1, "There is no valid scroll at the position provided");
	}
}
void ObjectDisplayGrid::wieldSword(Player* player, int index){
	Item *sc = player->scrollFromPack(index);
	Sword *sw = dynamic_cast<Sword*>(sc);
	if(sw){
		player->setSword(sw);
		player->dropFromPack(index);
		writeLine(1, "You equipped sword: " + sw->name);
		return;
	}
	else{
		writeLine(messageHeight+1, "There is no valid sword at the position provided");
	}
}
void ObjectDisplayGrid::wearArmor(Player* player, int index){
	Item *sc = player->scrollFromPack(index);
	Armor *arm = dynamic_cast<Armor*>(sc);
	if(arm){
		player->setArmor(arm);
		player->dropFromPack(index);
		writeLine(1, "You equipped armor: " + arm->name);
		return;
	}
	else{
		writeLine(messageHeight+1, "There is no valid armor at the position provided");
	}
}
void ObjectDisplayGrid::takeArmorOff(Player* player){
	Armor *arm = player->getArmor();
	player->setArmor(nullptr);
	player->addToPack(arm);
	writeLine(1, "You took off your armor... why would you do that? ");
}
void ObjectDisplayGrid::removeSword(Player* player){
	Sword *sw = player->getSword();
	player->setSword(nullptr);
	player->addToPack(sw);
	writeLine(1, "You removed your sword... why would you do that? ");
}
