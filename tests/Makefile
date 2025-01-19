CC=g++
CCFLAGS= -Wall -Werror -std=c++17 -g -I../include
LIBFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SRC= $(wildcard ../src/*.cc)
OBJ= $(filter-out ../bin/main.o, $(SRC:../src/%.cc=../bin/%.o))
TST= test.cc
OBJ_TEST = $(TST:.cc=.o)
EXEC= testcase.out
ASSETS_DIR=../ASSETS
ASSETS_DEST=./ASSETS

all: $(EXEC) copy_assets

$(EXEC): $(OBJ) $(OBJ_TEST)
	$(CC) $(CCFLAGS) $(OBJ) $(OBJ_TEST) -o $@ $(LIBFLAGS)

../bin/%.o: ../src/%.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

copy_assets:
	mkdir -p $(ASSETS_DEST)
	cp -r $(ASSETS_DIR)/* $(ASSETS_DEST)/

clean:
	rm -f ../bin/*.o *.o $(EXEC)
	rm -rf $(ASSETS_DEST)

.PHONY: all clean copy_assets