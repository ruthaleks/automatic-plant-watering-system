CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
SRC = main.cpp control.cpp pot.cpp tank.cpp sensor.cpp actuator.cpp
OBJ = app

PI_OBJ = appPi


all: build run

build: $(SRC) devices.cpp
	$(CC) -o $(OBJ) $(SRC) devices.cpp $(CPPFLAGS)

pi: $(SRC) drivers.cpp
	$(CC) -o $(PI_OBJ) $(SRC) drivers.cpp $(CPPFLAGS) -lwiringPi -DPI

run: $(OBJ)
	./$(OBJ) 
