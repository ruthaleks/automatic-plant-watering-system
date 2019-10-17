CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
SRC = main.cpp control.cpp pot.cpp tank.cpp sensorMonitor.cpp actuatorController.cpp devices.cpp
OBJ = app

PI_OBJ = appPi


all: build run

build: $(SRC) drivers.cpp
	$(CC) -o $(OBJ) $(SRC) $(CPPFLAGS)

pi: $(SRC) drivers.cpp
	$(CC) -o $(PI_OBJ) $(SRC) drivers.cpp $(CPPFLAGS) -lwiringPi -DPI

run: $(OBJ)
	./$(OBJ) 
