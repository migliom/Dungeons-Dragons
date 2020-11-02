#include "ObjectDisplayGrid.hpp"
#include "Dungeon.hpp"
#include "Action.hpp"
#include "Displayable.hpp"
#include "Item.hpp"
#include "Structure.hpp"
#include "ObjectDisplayGrid.hpp"
#include "KeyboardListener.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
std::atomic_bool isRunning(true);
int playerX = 0;
int playerY = 0;
static void addRooms(Dungeon* dungeon, ObjectDisplayGrid* grid){
    char wall = 'x';
    char floor = '.';
    
    std::vector<Room*> rooms = dungeon->getRooms();
    int topH = dungeon->getTopHeight();
    for(Room *room: rooms){
        int x = room->getPosX();
        int y = room->getPosY();
        for(int i = x; i < (room->getWidth()+x); i++){
            for(int j = y+topH; j < (room->getHeight()+y+topH); j++){
                if((i == x || i == (room->getWidth()+x-1)) || (j == y+topH || j == (room->getHeight()+y-1+topH))) //|| i == (room->getWidth()) && j == y || j == room->getHeight())
                    grid->addObjectToDisplay(new GridChar(wall), i, j);
                else
                    grid->addObjectToDisplay(new GridChar(floor), i, j);   
                for (int i = 0; (isRunning && i < 5); i++) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            grid->update();
            } 
        }
        grid->update();
    }
    grid->update();
}
static void initDisplay(ObjectDisplayGrid* grid, int width, int height, int HP){
    grid->writeLine(0, "HP: " + std::to_string(HP) + " Core: 0");
    grid->update();
    return;
}

static void addPassages(ObjectDisplayGrid *grid, Dungeon *dungeon){
    int topH = dungeon->getTopHeight();
    std::vector<Passage*> passages = dungeon->getPassages();
    for(Passage *passage: passages){
        std::vector<int> x = passage->getX();
        std::vector<int> y = passage->getY();
        for(int i = 0; i < x.size(); i++){
            if(x[i] == x[i+1]){
                if(y[i] < y[i+1]){
                    for(int j = y[i]; j <= y[i+1]; j++)
                    {
                        grid->addObjectToDisplay(new GridChar('#'), x[i], (j+topH));
                        grid->update();
                    }
                }
                else{
                    for(int j = y[i]; j >= y[i+1]; j--){  
                        grid->addObjectToDisplay(new GridChar('#'), x[i], (j+topH));
                        grid->update();
                    }
                } 
            }
            else{
                for(int k = x[i]; k <= x[i+1]; k++){
                    grid->addObjectToDisplay(new GridChar('#'), k, (y[i]+topH));
                    grid->update();
                }
            }
            grid->update();
        }
        grid->update();
    }
}
static void addCreaturesandItems(ObjectDisplayGrid *grid, Dungeon *dungeon){
    int topH = dungeon->getTopHeight();
    std::vector <Item*> items = dungeon->getItems();
    std::vector <Creature*> creatures = dungeon->getCreatures();
    for(Item *item: items){
        int posX = item->getPosX();
        int posY = item->getPosY();
        //std::cout << "PosX: " << posX << " PosY: " << posY << std::endl;
        char c = ' ';
        Scroll *s = dynamic_cast<Scroll*>(item);
        if(s)
            c = ']';
        Sword *sw = dynamic_cast<Sword*>(item);
        if(sw)
            c = ')';
        Armor *a = dynamic_cast<Armor*>(item);
        if(a)
            c = ']';
        grid->addObjectToDisplay(new GridChar(c), posX, posY+topH);
        grid->update();
        for(int i = 0; i < 5; i++)
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

     for(Creature *creature: creatures){
        int posX = creature->getPosX();
        int posY = creature->getPosY();
        char ch = ' ';
        Monster *m = dynamic_cast<Monster*>(creature);
        if(m){
            std::string name = m->getName();
            if(name == "Hobgoblin")
                ch = 'H';
            else if(name == "Snake")
                ch = 'S';
            else if(name == "Troll")
                ch = 'T';
        }
        Player *p = dynamic_cast<Player*>(creature);
        if(p)
            ch = '@';
        grid->addObjectToDisplay(new GridChar(ch), posX, posY+topH);
        grid->update();
        for(int i = 0; i < 5; i++)
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
void displayDungeon(Dungeon *dungeon){
    std::vector<int> dimensions = dungeon->returnDimensions();
    std::vector<Room*> rooms = dungeon->getRooms();
    std::vector<Passage*> passages = dungeon->getPassages();
    std::vector<Creature*> creatures = dungeon->getCreatures();
    std::vector<Item*> items = dungeon->getItems();

    ObjectDisplayGrid pgrid(dimensions[0], dimensions[1], 2);
    ObjectDisplayGrid *grid = &pgrid;
    int playerHitpoints = 0;
    for(Creature* creature: creatures){ 
        Player *player = dynamic_cast<Player*>(creature);
        if(player){
            playerHitpoints=player->getHP();
            playerX =player->getPosX();
            playerY =(player->getPosY() + dungeon->getTopHeight());
        }
    }
    //std::thread displayThread(initDisplay, grid, dimensions[0], dimensions[1], playerHitpoints);
    //displayThread.join();
    initDisplay(grid, dimensions[0], dimensions[1], playerHitpoints);
    //std::thread displayRooms(addRooms, dungeon, grid);
    //displayRooms.join();
    addRooms(dungeon, grid);
    //std::thread displayPassages(addPassages, grid, dungeon);
    //displayPassages.join();
    addPassages(grid, dungeon);

    addCreaturesandItems(grid, dungeon);
    KeyboardListener listener(grid);
    //std::thread keyboardThread(&KeyboardListener::run, &listener, &playerX, &playerY);
    //keyboardThread.join();
    listener.run(&playerX, &playerY);
}