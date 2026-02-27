# ===== Compiler settings =====
CXX := clang++
CXXFLAGS := -std=c++26 -Wall -Wextra -pedantic -g

# ===== Directories =====
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
LLDB := lldb

# ===== Files =====
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET := main

# ===== Default target =====
all: $(TARGET)

# ===== Link =====
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ===== Compile =====
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# ===== Clean =====
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# ===== Run =====
r: all
	./$(TARGET)

debug: all
	$(LLDB) ./$(TARGET)


.PHONY: all clean run