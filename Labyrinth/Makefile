CC=g++
CFLAGS=-c -I"."
LDFLAGS=-L"./lib" -lglu32 -lfreeglut -lopengl32 -Wl,--subsystem,windows
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
