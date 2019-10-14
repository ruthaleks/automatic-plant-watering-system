all: build run

build: main.cpp control.cpp devices.cpp pot.cpp tank.cpp sensor.cpp actuator.cpp
	g++ -o app main.cpp control.cpp devices.cpp tank.cpp pot.cpp sensor.cpp actuator.cpp -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

run: app
	./app 
