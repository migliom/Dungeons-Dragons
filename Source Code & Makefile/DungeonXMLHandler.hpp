#ifndef DUNGEONXMLHANDLER_H_
#define DUNGEONXMLHANDLER_H_

#include "Dungeon.hpp"
#include "Action.hpp"
#include "Displayable.hpp"
//#include "Dungeon.hpp"
#include "Item.hpp"
#include "ObjectDisplayGrid.hpp"
#include "Structure.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>
class Dungeon;

class DungeonXMLHandler : public xercesc::DefaultHandler{
    private:
        int DEBUG = 1;
        std::string CLASSID = "DungeonXMLHandler";
        std::string data;
        int roomCount = 0;
        bool bRoom = false;
        bool bPassage = false;
        Dungeon *dungeonBeingParsed;
        Displayable *displayableBeingParsed;
        Action *actionBeingParsed;
        bool bVisible = false;
		bool bPosx = false;
		bool bPosy = false;
		bool bWidth = false;
		bool bHeight = false;
        bool bPlayer = false;
        bool bScroll = false;
        bool bMonster = false;
        bool bSword = false;
        bool bArmor = false;
        bool bType = false;
        bool bHP = false;
        bool bMaxHit = false;
        bool bHPMoves = false;
        bool bIntValue = false;
        bool bActionMessage = false;
        bool bActionIntValue = false;
        
    public:
        //std::vector<Room*>getRooms();
        DungeonXMLHandler();
        void startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes) ;
        void endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName) ;
        void fatalError(const xercesc::SAXParseException&);
        void characters(const XMLCh * const ch, const XMLSize_t length ) ;
        std::string toString();
        Dungeon *getDungeon();
};
#endif