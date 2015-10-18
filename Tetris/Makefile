CC=g++
CFLAGS=-c -I"."
LDFLAGS=-L"./lib" -lglu32 -lfreeglut -lopengl32
SOURCES=main.cpp box.cpp BrickBase.cpp BrickE.cpp BrickI.cpp BrickL1.cpp BrickL2.cpp BrickT.cpp BrickZ1.cpp BrickZ2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Tetris

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o Tetris
