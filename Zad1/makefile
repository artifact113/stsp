CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=measurement.cpp algorithms.cpp reader.cpp data_structure.cpp main.cpp neighbour_generator.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

