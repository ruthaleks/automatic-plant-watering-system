CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
COMMONSRC =  control.cpp potManager.cpp tankManager.cpp sensorMonitor.cpp actuatorController.cpp devices.cpp lib/print.cpp readParams.cpp
SRC = main.cpp $(COMMONSRC)
TESTSRC = $(COMMONSRC) unittest/test.cpp
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
