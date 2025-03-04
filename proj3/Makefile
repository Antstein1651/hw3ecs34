# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# List of source files
SRC = $(wildcard *.cpp)            # Automatically find all .cpp files
OBJ = $(SRC:.cpp=.o)                # Convert .cpp filenames to .o filenames

# Name of the final executable
TARGET = driver

# Default rule: Build the executable
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)