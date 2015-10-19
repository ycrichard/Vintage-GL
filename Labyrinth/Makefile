CC=g++

SYS := $(shell g++ -dumpmachine)
ifneq (, $(findstring linux, $(SYS)))
	CFLAGS=-c
	LDFLAGS=-lGL -lGLU -lglut
else ifneq (, $(findstring mingw, $(SYS)))
	CFLAGS=-c -I"C:\Program Files\Common Files\MinGW\freeglut\include"
	LDFLAGS=-L"C:\Program Files\Common Files\MinGW\freeglut\lib\x64" -lopengl32 -lglu32 -lfreeglut -Wl,--subsystem,windows
else ifneq (, $(findstring darwin, $(SYS)))
	CFLAGS=-c -I"/opt/local/include"
	LDFLAGS=-L"/opt/local/lib" -lGL -lGLU -lglut
endif

SOURCES=main.cpp PersonnageBase.cpp Joueur.cpp EnnemiBase.cpp EnnemiVert.cpp EnnemiRouge.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Labyrinth

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o Labyrinth
