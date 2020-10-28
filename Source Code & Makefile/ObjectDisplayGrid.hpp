#ifndef OBJECTDISPLAYGRID_H_
#define OBJECTDISPLAYGRID_H_
#include "Dungeon.hpp"
#include "Displayable.hpp"
#include "Item.hpp"
#include "ObjectDisplayGrid.hpp"
#include "DungeonXMLHandler.hpp"
#include "Structure.hpp"
#include <string>
#include <vector>
#include <iostream>
class ObjectDisplayGrid{
    private:
        int width = 0;
        int topHeight = 0;
        int gameHeight = 0;
        int bottomHeight = 0;
    public:
        void getObjectDisplayGrid(int, int, int);
        void setTopMessageHeight(int);
};
#endif