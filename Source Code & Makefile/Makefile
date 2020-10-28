WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
G++ = g++ --std=c++17 -g $(WARNING) $(ERROR) -I /usr/local/Cellar/xerces-c/3.2.3/include -L /usr/local/Cellar/xerces-c/3.2.3/lib

SRCS = Action.cpp Displayable.cpp Dungeon.cpp DungeonXMLHandler.cpp Item.cpp main.cpp ObjectDisplayGrid.cpp Structure.cpp
OBJS = $(SRCS:%.cpp=%.o)

step1: $(OBJS)
	$(G++) $(OBJS) -o step1 -lxerces-c

.cpp.o:
	$(G++) -c $*.cpp

clean: # remove all machine generated files
	rm -f step1 *.o a.out output?

badScroll.xml: step1
	./step1 badScroll.xml
death.xml: step1
	./step1 death.xml
dropPack.xml: step1
	./step1 dropPack.xml
hallucinate.xml: step1
	./step1 hallucinate.xml
dungeon.xml: step1
	./step1 dungeon.xml
testDrawing.xml: step1
	./step1 testDrawing.xml
wear.xml: step1
	./step1 wear.xml
