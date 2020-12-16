#include "Dungeon.hpp"
Dungeon::Dungeon(){

}
Dungeon::Dungeon(std::string _name, int _width, int _topHeight, int _gameHeight, int _bottomHeight){
    name = _name;
    width = _width;
    topHeight = _topHeight;
    gameHeight = _gameHeight;
    bottomHeight = _bottomHeight;
    std::cout << "Dungeon() " << "\n" << "Name: " << name << ", Width: " << width << ", topHeight: " << topHeight << ", gameHeight: " << gameHeight << ", bottomHeight: " << bottomHeight << std::endl;
}
void Dungeon::getDungeon(std::string name, int width, int gameHeight){

}
void Dungeon::addRoom(Room *room){
    rooms.push_back(room);
}
void Dungeon::addCreature(Creature *creature){
    creatures.push_back(creature);
}
void Dungeon::addPassage(Passage *passage){
    passages.push_back(passage);
}
void Dungeon::addItem(Item *item){
    items.push_back(item);
}
std::string Dungeon::toString(){
    return "";
}
/*void Dungeon::freeRooms(){
    for(std::vector<Rooom *>::iterator room = rooms.begin(); activity != rooms.end(); ++room) { 
        delete *room; 
    }
    rooms.clear();
}*/
std::vector<Room*> Dungeon::getRooms(){
    return rooms;
}
std::vector<Passage*> Dungeon::getPassages(){
    return passages;
}
std::vector<Item*> Dungeon::getItems(){
    return items;
}
std::vector<Creature*> Dungeon::getCreatures(){
    return creatures;
}
std::vector<int> Dungeon::returnDimensions(){
    std::vector<int> dimensions;
    dimensions.push_back(width);
    dimensions.push_back((gameHeight+topHeight+bottomHeight));
    return dimensions;
}
int Dungeon::getTopHeight(){
    return topHeight;
}
int Dungeon::getGameHeight(){
    return gameHeight;
}