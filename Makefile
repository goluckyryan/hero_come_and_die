# Set the compiler and linker flags
CXX = g++
CFLAGS = -Wall -g
LDFLAGS = -lSDL2 -lSDL2main

# Target: executable name
TARGET = hero

# Build the executable
$(TARGET): main.cpp maze.h hero.h monster.h creature.h constant.h
	$(CXX) $(CFLAGS) -o $(TARGET) main.cpp $(LDFLAGS)

# Clean up the build directory
clean:
	rm -f $(TARGET)