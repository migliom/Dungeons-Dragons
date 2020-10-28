#include "Action.hpp"
void Action::setMessage(std::string _str)
{
    std::cout << "Action::setValue()" << std::endl;
    message = _str;
}

void Action::setIntValue(int _varo)
{
    std::cout << "Action::setIntValue()" << std::endl;
    intValue = _varo;
}

void Action::setCharValue(char _varo)
{
    std::cout << "Action::setCharValue()" << std::endl;
    charVal = _varo;
}

CreatureAction::CreatureAction(){
    std::cout << "CreatureAction()" << std::endl;
}

ItemAction::ItemAction(){
    std::cout << "ItemAction()" << std::endl;
}