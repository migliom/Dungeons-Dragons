#include "Displayable.hpp"

Displayable::Displayable(){
}
void Displayable::setInvisible(){
    //std::cout << "setInvisible()" << std::endl;
    visible = true;
    invisible = false;
}
void Displayable::setVisible(){
    //std::cout << "setVisible()" << std::endl;
    visible = false;
    invisible = true;
}
void Displayable::setMaxHit(int maxHit){
    //std::cout << "setMaxHit()...";
    maxHP = maxHit;
    //std::cout << "MaxHit = " << maxHit << std::endl;
}
void Displayable::setHpMove(int _hpMoves){
    //std::cout << "setHPMove()...";
    hpMoves = _hpMoves;
    //std::cout << "HP Moves = " << _hpMoves << std::endl;
}
void Displayable::setHp(int Hp){
    //std::cout << "setHP() -> ";
    hitpoints = Hp;
    //std::cout << "Hitpoints = " << Hp << std::endl;
}
void Displayable::setType(char t){
    //std::cout << "setType()" << std::endl;
    type = t;
}
void Displayable::setIntValue(int v){
    //std::cout << "setIntValue()" << std::endl;
    intValue = v;
}
void Displayable::setPosX(int x){
    //std::cout << "setPosX()...";
    posX = x;
    //std::cout << "PosX: " << x << std::endl;
}
void Displayable::setPosY(int y){
    //std::cout << "setPosY()...";
    posY = y;
    //std::cout << "PosX: " << y << std::endl;
}
void Displayable::setWidth(int _width){
    //std::cout << "setWidth()" << std::endl;
    width = _width;
}
void Displayable::setHeight(int _height){
    //std::cout << "setHeight()" << std::endl;
    height = _height;
}
int Displayable::getPosX(){
    //std::cout << "setPosX()...";
    return posX;
    //std::cout << "PosX: " << x << std::endl;
}
int Displayable::getPosY(){
    //std::cout <<"setPosY()...";
    return posY;
    //std::cout << "PosX: " << y << std::endl;
}
int Displayable::getWidth(){
    //std::cout << "setWidth()" << std::endl;
    return width;
}
int Displayable::getHeight(){
    //std::cout << "setHeight()" << std::endl;
    return height;
}
int Displayable::getHP(){
    //std::cout << "setHeight()" << std::endl;
    return hitpoints;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
Creature::Creature(){

}

int Creature::getSerial(){
    return serial;
}
void Creature::setHP(int _HP){
    //std::cout << "setHP()" << std::endl;
    Displayable::setHp(_HP);
}
void Creature::setHpMoves(int _hpm){
    //std::cout << "setHPMoves()" << std::endl;
    Displayable::setHpMove(_hpm);
}
void Creature::setDeathAction(CreatureAction* action){
    deathActions.push_back(action);
    return;
}
void Creature::setHitAction(CreatureAction* action){
    hitActions.push_back(action);
    return;
}
void Creature::setRoom(int _room){
    room = _room;
}
void Creature::setSerial(int _serial){
    serial = _serial;
}
std::vector <CreatureAction*> Creature::returnHitActions(){
    return hitActions;
}
std::vector <CreatureAction*> Creature::returnDeathActions(){
    return deathActions;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
Player::Player(){
    //std::cout << "new player: " << std::endl;
}
void Player::setArmor(Armor *_armor){
    armor = _armor;;
}
void Player::setSword(Sword *_sword){
    sword = _sword;
}
Armor* Player::getArmor(){
    return armor;
}
Sword* Player::getSword(){
    return sword;
}
void Player::setName(std::string s){
    namePlayer = "Player";
}
void Player::setID(int _room, int _serial){
    //std::cout << "SetID()" << std::endl;
    Creature::setRoom(_room);
    Creature::setSerial(_serial);
    //std::cout << "Player: " << _room << ", Serial: " << _serial << std::endl;
}
void Player::addToPack(Item *item){
    //std::string s = item->getItemName(2);
    //std::cout << "THE ITEM IS: " << s << std::endl;
    pack.push_back(item);
}
Item* Player::dropFromPack(int index){
    index = index - '0';
    //std::cout << "pack size: " << pack.size() << "Index: " << index << std::endl;
    //std::cout << "pack name: " << pack[index-1]->getItemName() << std::endl;
    if(index == 0 && pack.size() == 1){
        Item *j = pack[index];
        pack.erase(pack.begin()+0);
        return j;
    }
    if(index >= pack.size()+1){
        return NULL;
    }
    if(index <= 1 && pack.size() == 0){
        return NULL;
    }
    Item *i = pack[index-1];
    pack.erase(pack.begin()+index-1);
    return i;
}
std::vector<Item*> Player::getPack(){
    return pack;
}
Item* Player::scrollFromPack(int index){
    index = index - '0';
    if(index >= pack.size()+1){
        return NULL;
    }
    if(index <= 1 && pack.size() == 0){
        return NULL;
    }
    Item *i = pack[index-1];
    return i;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//ss
Monster::Monster(){
    //std::cout << "New Monster()" << std::endl;
}
void Monster::setName(std::string _name){
    //std::cout << "Monster::SetName() ";
    nameMonster = _name;
    //std::cout << nameMonster << std::endl;
}
void Monster::setID(int _room, int _serial){
    //std::cout << "Monster::SetID()" << std::endl;
    Creature::setRoom(_room);
    Creature::setSerial(_serial);
    //std::cout << "Monster: " << _room << ", Serial: " << _serial << std::endl;
}

std::string Monster::getName(){
    return nameMonster;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//