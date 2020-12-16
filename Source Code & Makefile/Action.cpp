#include "Action.hpp"

Action::Action(){
}
void Action::setMessage(std::string _str)
{
    //std::cout << "Action::setValue()" << std::endl;
    message = _str;
}
std::string Action::getMessage()
{
    return message;
}
std::string Action::getName()
{
    return name;
}
void Action::setIntValueAction(int _varo)
{
    //std::cout << "Action::setIntValue()" << std::endl;
    intValue = _varo;
}

void Action::setCharValue(char _varo)
{
    //std::cout << "Action::setCharValue()" << std::endl;
    charVal = _varo;
}

CreatureAction::CreatureAction(std::string _name, std::string _type){
    name = _name;
    type = _type;
}

ItemAction::ItemAction(std::string _name, std::string _type){
    name = _name;
    type = _type;
}

int Action::getIntValue(){
    return intValue;
}