CC = g++
C_FLAGS = -std=c++1y -g
L_FLAGS = -lpng
OBJ_NAME = PCNN
OBJS = obj/main.o

all: obj $(OBJS)
	$(CC) $(L_FLAGS) $(OBJS) -o $(OBJ_NAME)
obj:
	mkdir obj

clean:
	rm -rf obj/*

obj/main.o: src/main.cpp
	$(CC) $(C_FLAGS) -c src/main.cpp -o obj/main.o
