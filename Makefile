all: build run

build: main.cpp unitTest.cpp control.cpp devices.cpp
	g++ -o app main.cpp unitTest.cpp control.cpp devices.cpp -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

run: app
	./app 
