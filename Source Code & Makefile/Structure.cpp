#include "Structure.hpp"
Room::Room(std::string _name){
    name = _name;
    std::cout << "adding a new room: " << _name << std::endl;
}

void Room::setID(int id, int random){
    std::cout << "setID()" << std::endl;
    ID = id;
}

void Room::setCreature(Creature *_creature){
    ++numCreatures;
    creatures.push_back(_creature);
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
Passage::Passage(){

}

void Passage::setName(std::string _sname){
    name = _sname;
}

void Passage::setID(int _room1, int _room2){
    room1 = _room1;
    room2 = _room2;
}