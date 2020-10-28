#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include "Dungeon.hpp"
#include "Displayable.hpp"
#include "Structure.hpp"
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
};

class Room : public Structure{
    private:
        std::string name;
        int numCreatures = 0;
        std::vector<Creature*> creatures;
        int ID;
    public:
        Room(std::string _name);
        void setID(int id, int);
        void setName(std::string) {};
        void setCreature(Creature*);
};

class Passage : public Structure{
    private:
        std::string name;
        int room1, room2;
    public:
        Passage();
        void setName(std::string _name);
        void setID(int room1, int room2);
};
#endif