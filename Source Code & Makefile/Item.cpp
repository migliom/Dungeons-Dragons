#include "Item.hpp"
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
void Item::setOwner(){
    //this->creature = creature;
    std::cout << "Set owner()" << std::endl;
}
void Item::addItemAction(ItemAction *itemAction){
    itemActions.push_back(itemAction);
}
std::string Item::getItemName(int){
    return name;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
Scroll::Scroll(std::string _name){
    //std::cout << "Scroll::Scroll()" << std::endl;
    setName(_name);
}
void Scroll::setName(std::string _name){
    name = _name;
}
void Scroll::setID(int _room, int _serial){
    //std::cout << "Scroll::setID()" << std::endl;
    room = _room;
    serial = _serial;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
Armor::Armor(std::string _name){
    //std::cout << "Armor::Armor()" << std::endl;
    name = _name;
}

void Armor::setID(int _room, int _serial){
    //std::cout << "Armor::setID()" << std::endl;
    room = _room;
    serial = _serial;
}
void Armor::setName(std::string _name){
    //std::cout << "Armor::setName()" << std::endl;
    name = _name;
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
Sword::Sword(std::string _name){
    //std::cout << "Sword::Sword()" << std::endl;
    name = _name;
}

void Sword::setID(int _room, int _serial){
    //std::cout << "Sword::setID()" << std::endl;
    room = _room;
    serial = _serial;
}