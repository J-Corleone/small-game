INC = include/*.hh



all: run

run: main
	./main

main: main.cc $(INC)
	-rm main
	g++ main.cc -lncurses -o main
