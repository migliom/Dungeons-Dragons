#include "DungeonXMLHandler.hpp"
int currRoomX = 0;
int currRoomY = 0;
bool actionBool = 0;
int case_insensitive_match(std::string s1, std::string s2) {
    //convert s1 and s2 into lower case strings
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower); //std overloads tolower, ::tolower is the definition in the global namespace
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.compare(s2) == 0)
        return 1;
    return 0;
}

inline std::string boolToString(bool booleanValue){
    return booleanValue ? "true": "false";
}

DungeonXMLHandler::DungeonXMLHandler() {
}

Dungeon* DungeonXMLHandler::getDungeon(){
    return dungeonBeingParsed;
}

std::string xmlChToString(const XMLCh* xmlChName, int length = -1){
    //Xerces Parses file into XMLCh* string. So use Transcode to allocate a char* buffer
    char * chStarName = xercesc::XMLString::transcode(xmlChName); 
    if(length == -1){
        std::string StrName(chStarName);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }
    else{
        std::string StrName(chStarName,0,length);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }
}

const XMLCh* getXMLChAttributeFromString(const xercesc::Attributes& attributes, const char * strGet){
    XMLCh * xmlChGet = xercesc::XMLString::transcode(strGet);
    const XMLCh * xmlChAttr = attributes.getValue(xmlChGet);
    xercesc::XMLString::release((&xmlChGet));
    return xmlChAttr;
}

void DungeonXMLHandler::startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes){
    char * qNameStr = xercesc::XMLString::transcode(qName);
    if (DEBUG > 1) {
        std::cout << CLASSID << ".startElement qName: " << qNameStr << std::endl;
    }
    if (case_insensitive_match(qNameStr,"Rooms") || case_insensitive_match(qNameStr,"Passages")) {
        //std::cout << "Rooms: " << std::endl;
    }
    else if (case_insensitive_match(qNameStr,"Dungeon")) {
		std::string dungeonName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string dungeonWidth = xmlChToString(getXMLChAttributeFromString(attributes,"width"));
        int dungeonWidthI = std::stoi(dungeonWidth);
        std::string dungeonTHeight = xmlChToString(getXMLChAttributeFromString(attributes,"topHeight"));
        int dungeonTHeightI = std::stoi(dungeonTHeight);
        std::string dungeonGameHeight = xmlChToString(getXMLChAttributeFromString(attributes,"gameHeight"));
        int dungeonGameHeightI = std::stoi(dungeonGameHeight);
        std::string dungeonBHeight = xmlChToString(getXMLChAttributeFromString(attributes,"bottomHeight"));
        int dungeonBHeightI = std::stoi(dungeonBHeight);

        Dungeon *dungeon = new Dungeon(dungeonName, dungeonWidthI, dungeonTHeightI, dungeonGameHeightI, dungeonBHeightI);
        dungeonBeingParsed = dungeon;
    
    } else if (case_insensitive_match(qNameStr,"Room")) {
        int roomNum = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room")));
        bRoom = true;
        bPlayer = false;
        bMonster = false;
        bArmor = false;
        bScroll = false;
        bSword = false;

        Displayable *structure1 = new Room("newRoom");
        structure1->setID(roomNum, 2);
        dungeonBeingParsed->addRoom(dynamic_cast<Room*>(structure1));
        displayableBeingParsed = structure1;

    }else if (case_insensitive_match(qNameStr,"Passage")) {
        int roomNum1 = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room1")));
        int roomNum2 = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"room2")));
        bPassage = true;
        bRoom = false;
        bPlayer = false;
        bMonster = false;
        bArmor = false;
        bScroll = false;
        bSword = false;

        Displayable *structure2 = new Passage();
        structure2->setID(1, 2);
        dungeonBeingParsed->addPassage(dynamic_cast<Passage*>(structure2));
        displayableBeingParsed = structure2;

    }else if (case_insensitive_match(qNameStr,"Player")) {
        std::string playerName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string playerRoom = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        int playerRoomI = std::stoi(playerRoom);
        std::string playerSerial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        int playerSerialI = std::stoi(playerSerial);
        bPlayer = true;
        bRoom = false;
        bMonster = false;
        bArmor = false;
        bScroll = false;
        bSword = false;
        Displayable *creature1 = new Player();

        creature1->setName("");
        creature1->setID(playerRoomI, playerSerialI); 
        displayableBeingParsed = creature1;
        dungeonBeingParsed->addCreature(dynamic_cast<Creature*>(creature1));
        //Is this technically a downcast or an upcast? It is a displayable of type creature
    }else if (case_insensitive_match(qNameStr,"Monster")) {
        std::string monsterName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string monsterRoom = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        int monsterRoomI = std::stoi(monsterRoom);
        std::string monsterSerial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        int monsterSerialI = std::stoi(monsterSerial);

        bMonster = true;
        bRoom = false;
        bPlayer = false;
        bArmor = false;
        bScroll = false;
        bSword = false;
        Displayable *creature2 = new Monster(); 
        creature2->setName(monsterName);
        creature2->setID(monsterRoomI, monsterSerialI);
        //roomBeingParsed->setCreature(((Monster *) creature2)); 
        displayableBeingParsed = creature2;
        dungeonBeingParsed->addCreature(dynamic_cast<Creature*>(creature2));

    }else if (case_insensitive_match(qNameStr,"Scroll")) {
        std::string scrollName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string scrollRoom = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        int scrollRoomI = std::stoi(scrollRoom);
        std::string scrollSerial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        int scrollSerialI = std::stoi(scrollSerial);
        bScroll = true;
        bRoom = false;
        bPlayer = false;
        bMonster = false;
        bArmor = false;
        bSword = false;
        Displayable * item1 = new Scroll(scrollName); 
        item1->setID(scrollRoomI, scrollSerialI);
        //item1->setCreature(((Scroll *) item1)); 
        dungeonBeingParsed->addItem(dynamic_cast<Item*>(item1));
        displayableBeingParsed = item1;

    }else if (case_insensitive_match(qNameStr,"Sword")) {
        std::string swordName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string swordRoom = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        int swordRoomI = std::stoi(swordRoom);
        std::string swordSerial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        int swordSerialI = std::stoi(swordSerial);
        bSword = true;
        bRoom = false;
        bPlayer = false;
        bMonster = false;
        bArmor = false;
        bScroll = false;
        Displayable * item2 = new Sword(swordName); 
        item2->setID(swordRoomI, swordSerialI);
        //item1->setCreature(((Scroll *) item1)); 
        dungeonBeingParsed->addItem(dynamic_cast<Item*>(item2));
        displayableBeingParsed = item2;

    }else if (case_insensitive_match(qNameStr,"Armor")) {
        std::string armorName = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string armorRoom = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        int armorRoomI = std::stoi(armorRoom);
        std::string armorSerial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        int armorSerialI = std::stoi(armorSerial);

        bArmor = true;
        bRoom = false;
        bPlayer = false;
        bMonster = false;
        bScroll = false;
        bSword = false;
        Displayable * item3 = new Scroll(armorName); 
        item3->setID(armorRoomI, armorSerialI);
        //item1->setCreature(((Scroll *) item1)); 
        dungeonBeingParsed->addItem(dynamic_cast<Item*>(item3));
        displayableBeingParsed = item3;
    }else if (case_insensitive_match(qNameStr,"CreatureAction")) {
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string type = xmlChToString(getXMLChAttributeFromString(attributes,"type"));
        Action *action = new CreatureAction(name, type);
        actionBeingParsed = action; 
        actionBool = 1;

    }else if (case_insensitive_match(qNameStr,"ItemAction")) {
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string type = xmlChToString(getXMLChAttributeFromString(attributes,"type"));
        Action *action1 = new ItemAction(name, type);
        actionBeingParsed = action1; 
        actionBool = 1;

    }
        
    else if (case_insensitive_match(qNameStr,"visible")) {
        bVisible = true;
    } else if (case_insensitive_match(qNameStr,"posX")) {
        bPosx = true;
    } else if (case_insensitive_match(qNameStr,"posY")) {
        bPosy = true;
    } else if (case_insensitive_match(qNameStr,"width")) {
        bWidth = true;
    } else if (case_insensitive_match(qNameStr,"height")) {
        bHeight = true;
    } else if (case_insensitive_match(qNameStr,"type")) {
        bType = true;
    } else if (case_insensitive_match(qNameStr,"hp")) {
        bHP = true;
    } else if (case_insensitive_match(qNameStr,"maxhit")) {
        bMaxHit = true;
    } else if (case_insensitive_match(qNameStr,"hpMoves")) {
        bHPMoves = true;   
    } else if (case_insensitive_match(qNameStr,"actionMessage")) {
        bActionMessage = true;   
    } else if (case_insensitive_match(qNameStr,"ActionIntValue")) {
        bActionIntValue = true;
    }else if (case_insensitive_match(qNameStr,"ActionCharValue")) {
        bActionCharValue = true;
    }else if (case_insensitive_match(qNameStr,"ItemIntValue")) {
        bItemIntValue = true;
    }
    else {
        std::cout <<"Unknown qname: " << qNameStr << std::endl;
    }
    xercesc::XMLString::release(&qNameStr);
}

void DungeonXMLHandler::endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName)  {
        if(bMonster || bPlayer || bArmor || bSword || bScroll){
            if(bVisible){
                displayableBeingParsed->setVisible();
                bVisible = false;
            }
            else if(bPosx){
                displayableBeingParsed->setPosX(std::stoi(data)+currRoomX);
                bPosx = false;
            }
            else if(bPosy){
                displayableBeingParsed->setPosY(std::stoi(data)+currRoomY);
                bPosy = false;
            }
        }
        if(bPassage){
            Passage *passage = dynamic_cast<Passage*>(displayableBeingParsed);
            if(bVisible){
                passage->setVisible();
                bVisible = false;
            }
            if(bPosx){
                passage->addX(std::stoi(data));
                bPosx = false;
            }
            if(bPosy){
                passage->addY(std::stoi(data));
                bPosy = false;
            }
        }
        if (bRoom) { //both structures and displayables can be visible
            //SEE IF WE NEED TO CAST IF IT  IS ONLY FILLING IN ATTRIBUTES OF BASE CLASS
            if(bVisible){
                displayableBeingParsed->setVisible();
                bVisible = false;
            }
            else if(bPosx){
                displayableBeingParsed->setPosX(std::stoi(data));
                currRoomX = std::stoi(data);
                bPosx = false;
            }
            else if(bPosy){
                displayableBeingParsed->setPosY(std::stoi(data));
                currRoomY = std::stoi(data);
                bPosy = false;
            }
            Room *room = (Room *) displayableBeingParsed;
            if(bWidth){
                room->setWidth(std::stoi(data));
                bWidth = false;
            }
            else if(bHeight){
                room->setHeight(std::stoi(data));
                bHeight = false;
            }
            else if(bType){
                room->setVisible();
                bType = false;
            }
            else if(bHP){
                room->setVisible();
                bHP = false;
            }
            else if(bMaxHit){
                room->setVisible();
                bMaxHit = false;
            }
        //-----------------------------------------------------// 
        } else if (bPlayer) {
            Player *player = (Player *) displayableBeingParsed;
            if(bHP){
                player->setHP((std::stoi(data)));
                bHP = false;
            }
            else if(bMaxHit){
                player->setMaxHit((std::stoi(data)));
                bMaxHit = false;
            }
            if(bHPMoves){
                player->setHpMove((std::stoi(data)));
                bHPMoves = false;
            }
        }
        //-----------------------------------------------------// 
        else if (bMonster) {
            Monster *monster = (Monster *) displayableBeingParsed;
            if(bHP){
                monster->setHP((std::stoi(data)));
                bHP = false;
            }
            else if(bMaxHit){
                monster->setMaxHit((std::stoi(data)));
                bMaxHit = false;
            }
            else if(bType){
                monster->setType((char)data[0]);
                bType = false;
            }
        }
        //----------------------------------------------//
        else if (bSword) {
            Sword *sword = (Sword *) displayableBeingParsed;
            if(bIntValue){
                sword->setIntValue((std::stoi(data)));
                bIntValue = false;
            }
        }
        //----------------------------------------------//
        else if (bArmor) {
            Armor *armor = (Armor *) displayableBeingParsed;
            if(bIntValue){
                armor->setIntValue((std::stoi(data)));
                bIntValue = false;
            }
        }
        //----------------------------------------------//
        else if (bScroll) {
            Scroll *scroll = (Scroll *) displayableBeingParsed;
            if(bIntValue){
                scroll->setIntValue((std::stoi(data)));
                bIntValue = false;
            }
        }
        else if (bActionMessage){
            actionBeingParsed->setMessage(data);
            bActionMessage = false;
        }else if (bActionIntValue || bItemIntValue){
            actionBeingParsed->setIntValue(std::stoi(data));
            bActionIntValue = false;
            bItemIntValue = false;
        }else if (bActionCharValue){
            actionBeingParsed->setCharValue(std::stoi(data));
            bActionCharValue = false;
        }

        //-----------------------------------------------------// 
        char *  qNameStr = xercesc::XMLString::transcode(qName);
        if (case_insensitive_match(qNameStr,"Room") || case_insensitive_match(qNameStr,"Monster") || case_insensitive_match(qNameStr,"Player") || case_insensitive_match(qNameStr,"Sword") || case_insensitive_match(qNameStr,"Armor") || case_insensitive_match(qNameStr,"Scroll")) {
            displayableBeingParsed = nullptr;
        } else if (case_insensitive_match(qNameStr,"CreatureAction") || case_insensitive_match(qNameStr,"ItemAction")) {
            //ADD CREATURE ACTION TO THE CORRESPONDING CREATURE
            Item *item = dynamic_cast<Item*>(displayableBeingParsed);
            if(item){
                ItemAction *iA = dynamic_cast<ItemAction*>(actionBeingParsed);
                item->addItemAction(iA);
            }
            else{
                Creature *crature = dynamic_cast<Creature*>(displayableBeingParsed);
                CreatureAction *cA = dynamic_cast<CreatureAction*>(actionBeingParsed);
                crature->addCreatureAction(cA);
            }
            actionBeingParsed = nullptr;
        }
        xercesc::XMLString::release(&qNameStr);
}

void DungeonXMLHandler::characters(const XMLCh * const ch, const XMLSize_t length) {
        data = xmlChToString(ch,(int)length);
        if (DEBUG > 1) {
			std::cout << CLASSID + ".characters: " << data << std::endl;
            //std::cout.flush();
        }
}

void DungeonXMLHandler::fatalError(const xercesc::SAXParseException& exception)
{
    char* message = xercesc::XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << std::endl;
    xercesc::XMLString::release(&message);
}