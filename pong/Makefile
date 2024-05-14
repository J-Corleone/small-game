# INC = include/*.hh
LD = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC += main.cc

all: run

run: main
	./main

main: $(SRC) $(INC)
	g++ $< $(LD) -o main

