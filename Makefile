all: build run

build: main.cpp unitTest.cpp
	g++ -o app main.cpp unitTest.cpp -std=c++17 -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

run: app
	./app 
