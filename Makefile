all: build run

build: main.cpp control.cpp devices.cpp pot.cpp tank.cpp
	g++ -o app main.cpp control.cpp devices.cpp tank.cpp pot.cpp -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

run: app
	./app 
