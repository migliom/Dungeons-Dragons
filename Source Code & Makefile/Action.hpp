#ifndef ACTION_H_
#define ACTION_H_
#include <string>
#include <iostream>
class Action{
    private:
        std::string message;
        int intValue;
        char charVal;
    public:
        void setMessage(std::string);
        void setIntValue(int);
        void setCharValue(char);
};

class CreatureAction : public Action{
    private:
    public:
        CreatureAction();
};

class ItemAction : public Action{
    private:
    public:
        ItemAction();
};

#endif