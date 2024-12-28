CC=g++
CCFLAGS= -Wall -Werror -std=c++17 -g
LIBFLAGS= 
SRC= $(wildcard *.cc)
OBJ= $(SRC:.cc=.o)
STTGAME = State-and-game/
EXEC= escapegame


all: $(EXEC)

sttandgame:
	cd $(STTGAME) ; make

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@  -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depends:
	g++ -MM $(SRC) > .depends

-include .depends

clean:
	rm -f $(OBJ) $(EXEC) *.*~


