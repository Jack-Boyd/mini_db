CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Isrc
BUILD_DIR := build
TARGET := $(BUILD_DIR)/mini_db

SOURCES := \
	src/main.cpp \

OBJECTS := $(SOURCES:src/%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
