GCC = g++
LIBS = -lncurses `pkg-config --cflags --libs opencv`
SRC = src/main.cpp src/menu.cpp

all:
	$(GCC) -o converter $(SRC) $(LIBS)

clean:
	rm converter
