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
void Creature::setHP(int _HP){
    //std::cout << "setHP()" << std::endl;
    Displayable::setHp(_HP);
}
void Creature::setHpMoves(int _hpm){
    //std::cout << "setHPMoves()" << std::endl;
    Displayable::setHpMove(_hpm);
}
void Creature::setDeathAction(CreatureAction){

}
void Creature::setHitAction(CreatureAction){

}
void Creature::setRoom(int _room){
    room = _room;
}
void Creature::setSerial(int _serial){
    serial = _serial;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//
Player::Player(){
    //std::cout << "new player: " << std::endl;
}
void Player::setArmor(Item *_sword){
    sword = (Sword *) _sword;
}
void Player::setWeapon(Item *_armor){
    armor = (Armor *)_armor;
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

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_//