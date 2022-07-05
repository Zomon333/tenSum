CC = g++
FLAGS = -std=c++20

SOURCE_DIR = ./src
INCLUDE_DIR = ./include
LIBRARY_DIR = ./lib
OUT_DIR = ./output

LIBS = 

NAME = "tenPair"

all:
	g++ $(FLAGS) $(SOURCE_DIR)/*.cpp -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) $(LIBS) -o $(OUT_DIR)/$(NAME)

remake:
	make clean
	make

clean:
	rm $(OUT_DIR)/*

