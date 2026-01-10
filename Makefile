CXX = g++
INCLUDES = -I./headers
CXXFLAGS = -Wall -Wextra -std=c++17 $(INCLUDES)

TARGET = rub
LDLIBS = -lSDL2

SRC_DIR = src
OBJ_DIR = obj


SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/cube.cpp $(SRC_DIR)/geometry.cpp $(SRC_DIR)/camera.cpp

OBJS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
