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
        int room;
        int serial;
    public:
        std::vector<ItemAction*> getItemActions();
        std::string name;
        virtual void addItemAction(ItemAction*);
        virtual void setOwner();
        virtual std::string getItemName(int);
        virtual void test() {};
};

class Scroll : public Item{
    private:
        int room;
        int serial;
    public:
        Scroll(std::string);
        virtual void test() {};
        virtual void setID(int, int);
        virtual void setName(std::string);
        
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