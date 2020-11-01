#ifndef STRUCTURE_H_
#define STRUCTURE_H_

//#include "Dungeon.hpp"
#include "Displayable.hpp"
//#include "Structure.hpp"
#include "Item.hpp"
#include "ObjectDisplayGrid.hpp"
#include "DungeonXMLHandler.hpp"
#include <string>
#include <vector>
#include <iostream>

class Structure : public Displayable{
    public:
        virtual void setID(int, int) {};
        virtual void setName(std::string) {};
        virtual void addX(int) {};
        virtual void addY(int) {};
};

class Room : public Structure{
    private:
        std::string name;
        int numCreatures = 0;
        int numItems = 0;
        std::vector<Creature*> creatures;
        std::vector<Item*> items;
        int ID;
    public:
        Room(std::string _name);
        void setID(int id, int);
        void setName(std::string) {};
        void setCreature(Creature*);
        void setItem(Item*);
        Creature* getCreature();
        Item* getItem();
};

class Passage : public Structure{
    private:
        std::string name;
        int room1, room2;
        std::vector <int> xPos;
        std::vector <int> yPos;
    public:
        std::vector<int> getY();
        std::vector<int> getX();
        Passage();
        void addX(int);
        void addY(int);
        void setName(std::string _name);
        void setID(int room1, int room2);
};
#endif