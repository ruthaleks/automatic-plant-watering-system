CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
SRC = main.cpp control.cpp potManager.cpp tankManager.cpp sensorMonitor.cpp actuatorController.cpp devices.cpp
TESTSRC = control.cpp potManager.cpp tankManager.cpp sensorMonitor.cpp actuatorController.cpp devices.cpp unittest/test.cpp
OBJ = app
PI_OBJ = appPi
TESTOBJ = appTest


all: build run  
test: buildtest runtest

build: $(SRC)
	$(CC) -o $(OBJ) $(SRC)  $(CPPFLAGS) -DDEBUG

buildtest: $(TESTSRC) 
	$(CC) -o $(TESTOBJ) $(TESTSRC)  $(CPPFLAGS) -DDEBUG

pi: $(SRC) drivers.cpp
	$(CC) -o $(PI_OBJ) $(SRC) drivers.cpp $(CPPFLAGS) -lwiringPi -DPI -DDEBUG

run: $(OBJ)
	./$(OBJ)

runtest: $(TESTOBJ)
	./$(TESTOBJ)
