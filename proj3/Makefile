CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -pthread

# Source Files
SRC = src/main.cpp src/OpenStreetMap.cpp src/XMLReader.cpp src/DataSource.cpp src/StreetMap.cpp

# Object Files
OBJ = $(SRC:.cpp=.o)

# Target Executable
TARGET = ./driver

# Google Test
GTEST_DIR = /usr/src/gtest
GTEST_LIB = -lgtest -lgtest_main

# Build the main executable
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(GTEST_LIB)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the compiled program
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET)
