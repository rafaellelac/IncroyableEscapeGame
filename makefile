CC=g++
CCFLAGS= -Wall -Werror -std=c++17 -g -Iinclude
LIBFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SRC= $(wildcard src/*.cc)
OBJ= $(SRC:src/%.cc=bin/%.o)
EXEC= escapegame

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@ $(LIBFLAGS)

bin/%.o: src/%.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depends:
	$(CC) -MM $(SRC) -Iinclude > .depends

	-include .depends

clean:
	rm -f bin/*.o $(EXEC) *.*~

.PHONY: all clean