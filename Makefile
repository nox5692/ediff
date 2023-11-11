# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic -Wno-long-long -Werror -g -O2

# Define target executable and source files
TARGET = ediff
# SRC = src/main.cpp
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Define doxygen documentation generation command
DOXYGEN = doxygen
DOXYGEN_CONFIG = Doxyfile
DOXYGEN_SRC = doc

# Define phony targets
.PHONY: all clean doc run compile

# Default target - build the executable
all: compile doc

compile: $(TARGET)
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpng

# Target for generating Doxygen documentation
doc: $(DOXYGEN_CONFIG)
	$(DOXYGEN) $<

# Target for cleaning up object files and executables
clean:
	rm -rf $(TARGET) $(OBJ) $(DOXYGEN_SRC)

run:
	./$(TARGET)
