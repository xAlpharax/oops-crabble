# C++ Compiler and C++ Compiler Flags
CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++23

# Directories
SRC_DIR=src
OBJ_DIR=obj

# SFML Flags
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Files
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE=scrabble

# Rules
all: $(EXECUTABLE)

# Build target
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(SFML_FLAGS)

# Rule to compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)

# Phony targets
.PHONY: all clean
