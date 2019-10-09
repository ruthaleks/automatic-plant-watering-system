all: build run

build: main.cpp
	g++ -o app main.cpp -std=c++17 -Wall -Werror

run: app
	./app 
