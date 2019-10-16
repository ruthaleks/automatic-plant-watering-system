CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
SRC = main.cpp control.cpp pot.cpp tank.cpp sensor.cpp actuator.cpp
OBJ = app

PI_OBJ = appPi


all: build run

build: $(SRC)
	$(CC) -o $(OBJ) $(SRC) $(CPPFLAGS)

pi: $(SRC)
	$(CC) -o $(PI_OBJ) $(SRC) $(CPPFLAGS) -DPI

run: $(OBJ)
	./$(OBJ) 
