#ifndef DUNGEON_H_
#define DUNGEON_H_

#include "Dungeon.hpp"
#include "Displayable.hpp"
#include "Item.hpp"
#include "ObjectDisplayGrid.hpp"
#include "DungeonXMLHandler.hpp"
#include <string>
#include <vector>
#include <iostream>

class Dungeon{
    private:
        std::string name;
        int width = 0;
        int topHeight = 0;
        int gameHeight = 0;
        int bottomHeight = 0;
        //std::vector<Room*> rooms;
        //std::vector<Passage*> passages;
        //std::vector<Creature*> creatures;
        //std::vector<Item*> items;  
    public:
        Dungeon(std::string _name, int _width, int _topHeight, int _gameHeight, int _bottomHeight);
        Dungeon(); 
        void getDungeon(std::string name, int width, int gameHeight);
        //void addRoom(Room *room);
        void addCreature(Creature *creature);
        //void addPassage(Passage *passage);
        void addItem(Item *item);
        std::string toString();
        void freeRooms();
};


#endif /* STUDENT_H_ */

