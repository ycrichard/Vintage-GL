CC=g++
CFLAGS=-c -I"."
LDFLAGS=-L"./lib" -lglu32 -lfreeglut -lopengl32
SOURCES=main.cpp corps.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Snake

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o Snake
