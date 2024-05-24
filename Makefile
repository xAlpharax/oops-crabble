# Compiler and flags
CXX = gcc
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = $(SRCDIR)

# SFML paths (change these to match your SFML installation)
SFML_LIBDIR = /usr/lib
SFML_INCDIR = /usr/include

# SFML libraries (you can add more if needed)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = scrabble

# Rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ -L$(SFML_LIBDIR) $(SFML_LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -I$(SFML_INCDIR) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)

# Phony targets
.PHONY: all clean
