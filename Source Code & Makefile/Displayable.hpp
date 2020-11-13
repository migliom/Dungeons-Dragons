#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
//#include "Item.hpp"
#include "Action.hpp"

class Item;
class Sword;
class Armor;

class Displayable{
    private:
        /*bool visible = false;
        bool invisible = false;
        int maxHP = 0;
        int hpMoves = 0;
        int hitpoints = 0;
        char type;
        int value = 0;
        int posX = 0;
        int posY = 0;
        int width = 0;
        int height = 0;
        int intValue = 0;*/
    public:
        bool visible = false;
        bool invisible = false;
        int maxHP = 0;
        int hpMoves = 0;
        int hitpoints = 0;
        char type;
        int value = 0;
        int posX = 0;
        int posY = 0;
        int width = 0;
        int height = 0;
        int intValue = 0;
        Displayable();
        void setInvisible();
        virtual void setID(int, int) {};
        virtual void setName(std::string) {};
        void setVisible();
        void setMaxHit(int maxHit);
        void setHpMove(int hpMoves);
        void setHp(int Hp);
        void setType(char t);
        void setIntValue(int v);
        void setPosX(int x);
        void setPosY(int y);
        void setWidth(int x);
        void setHeight(int y);
        int getPosX();
        int getPosY();
        int getWidth();
        int getHeight();
        int getHP();
        virtual void addX(int) {};
        virtual void addY(int) {};
        virtual int getSerial() {};
};

class Creature : public Displayable{
    private:
        std::vector <CreatureAction*> creatureActions;
        int serial;
        int room;
    public:
        Creature();
        void setRoom(int);
        void addCreatureAction(CreatureAction *creatureAction);
        virtual void setID(int, int) {};
        virtual void setName(std::string) {};
        void setSerial(int);
        int getSerial();
        void setHP(int);
        void setHpMoves(int);
        void setDeathAction(CreatureAction);
        void setHitAction(CreatureAction);
        std::vector <CreatureAction*> getCreatureActions();
};

class Player : public Creature{
    private:
        Sword *sword;
        Armor *armor;
        std::vector <Item*> pack;
        std::string namePlayer;
    public:
        void setArmor(Item *sword);
        void addToPack(Item*);
        Item *dropFromPack(int);
        void setWeapon(Item *armor);
        void setName(std::string);
        void setID(int, int);
        Player();
        std::vector<Item*> getPack();
};

class Monster : public Creature{
    private:
        std::string nameMonster;
    public:
        Monster();
        void setName(std::string);
        void setID(int, int);
        std::string getName();
};
#endif