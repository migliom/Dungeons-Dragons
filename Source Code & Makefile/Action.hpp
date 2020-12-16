#ifndef ACTION_H_
#define ACTION_H_
#include <string>
#include <iostream>
class Action{
    private:
    public:
        std::string message;
        int intValue;
        char charVal;
        std::string name;
        std::string type;
        Action();
        virtual ~Action(){};
        void setMessage(std::string);
        void setIntValueAction(int);
        void setCharValue(char);
        std::string getMessage();
        int getIntValue();
        std::string getName();
};

class CreatureAction : public Action{
    private:
    public:
        CreatureAction(std::string, std::string);
};

class ItemAction : public Action{
    private:
    public:
        ItemAction(std::string, std::string);
};

#endif