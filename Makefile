CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -pedantic -march=native -O3 -ffast-math
LIBS := -lncurses `pkg-config --cflags --libs opencv`

.PHONY: all clean

TARGET := converter

SRC := src/main.cpp src/menu.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(OBJ) $(TARGET)