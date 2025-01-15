# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Source files and output
SRCS := src/main.cpp src/leafnode.cpp src/sequencenode.cpp src/btmanager.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := program

# Default target
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compilation step
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony targets
.PHONY: all

