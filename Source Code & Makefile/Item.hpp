#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <vector>
#include <iostream>
#include "Displayable.hpp"
#include "Action.hpp"

//class Displayable;

class Item : public Displayable{
    private:
        std::vector <ItemAction*> itemActions;
        //Creature* owner;
        int room;
        int serial;
        //std::string name;
    public:
        std::string name;
        void addItemAction(ItemAction*);
        void setOwner();
        std::string getItemName(int);
};

class Scroll : public Item{
    private:
        int room;
        int serial;
    public:
        Scroll(std::string);
        void setID(int, int);
        void setName(std::string);
        
};

class Armor : public Item{
    private:
        int room;
        int serial;
    public:
        Armor(std::string);
        void setName(std::string);
        void setID(int, int);
};

class Sword : public Item{
    private:
        int room;
        int serial;
    public:
        Sword(std::string);
        void setID(int, int);
};

#endif