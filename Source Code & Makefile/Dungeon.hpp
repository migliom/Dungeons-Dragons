#ifndef DUNGEON_H_
#define DUNGEON_H_
#include "Item.hpp"
#include <string>
#include <vector>
#include <iostream>
class Room;
class Passage;

class Dungeon{
    private:
        std::string name;
        int width = 0;
        int topHeight = 0;
        int gameHeight = 0;
        int bottomHeight = 0;
        std::vector<Room*> rooms;
        std::vector<Passage*> passages;
        std::vector<Creature*> creatures;
        std::vector<Item*> items;  
    public:
        Dungeon(std::string _name, int _width, int _topHeight, int _gameHeight, int _bottomHeight);
        Dungeon(); 
        virtual ~Dungeon() {};
        void getDungeon(std::string name, int width, int gameHeight);
        void addCreature(Creature *creature);
        void addItem(Item *item);
        void addRoom(Room *room);
        void addPassage(Passage *passage);
        std::vector<Room*> getRooms();
        std::vector<Passage*> getPassages();
        std::vector<Item*> getItems();
        std::vector<Creature*> getCreatures();
        //void addPassage(Passage *passage);
        std::string toString();
        std::vector<int> returnDimensions();
        void freeRooms();
        int getTopHeight();
        int getGameHeight();
};


#endif /* STUDENT_H_ */

