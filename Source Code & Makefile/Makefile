CXX=g++ -O

LIBS = /usr/local/Cellar/xerces-c/3.2.3/include
INCLUDE = /usr/local/Cellar/xerces-c/3.2.3/lib

CXXFLAGS=-std=c++11 -Wall -g -I /usr/local/Cellar/xerces-c/3.2.3/include -L /usr/local/Cellar/xerces-c/3.2.3/lib
CLASSES = DungeonXMLHandler.cpp Displayable.cpp ObjectDisplayGrid.cpp Item.cpp Structure.cpp Dungeon.cpp GridChar.cpp KeyboardListener.cpp

HEADERS = $(CLASSES:%.cpp=%.hpp)
SOURCES = Rogue.cpp main.cpp $(CLASSES)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Rogue

CURSES=-lncurses
	# Have to include threads on linux
	CXXFLAGS += -pthread
	# running -f means it does not error on missing files
	RM=rm -f
	# Linux needs the zip command to do zip files, install using apt-get
	ZIP=zip -r

# Build then run
run: $(EXECUTABLE)
	./$(EXECUTABLE) dungeon.xml
.PHONY: run

%.xml: $(EXECUTABLE)
	./$(EXECUTABLE) $@
# Build the project, default command
$(EXECUTABLE): $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(CURSES) -lxerces-c
	
# Compile .o files
# Cannot think of a good way to watch only the required headers for each .o file
%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) $<

# Clean the project
clean:
	$(RM) *.o
	$(RM) $(EXECUTABLE)
	$(RM) $(EXECUTABLE).exe
	$(RM) $(EXECUTABLE).zip

# Clean then build
rebuild: clean $(EXECUTABLE)
.PHONY: rebuild

# Create a zip file with all relevant files to build the project
ZIPFILES=$(SOURCES) $(HEADERS) Makefile lib/* include/* pdcurses.dll \
	PDCursesExample.sln PDCursesExample.vcxproj PDCursesExample.vcxproj.filters
zip: $(ZIPFILES)
	$(ZIP) $(EXECUTABLE).zip $(ZIPFILES)
.PHONY: zip

