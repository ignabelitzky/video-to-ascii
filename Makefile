CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -march=native -O3 -ffast-math -Wno-stringop-overflow
LIBS := -lncurses `pkg-config --cflags --libs opencv` -lpthread -lm -ldl

.PHONY: all clean

TARGET := converter

SRC := src/main.cpp src/menu.cpp src/audio.cpp src/helper.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(OBJ) $(TARGET)