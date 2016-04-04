CXX=g++
CFLAGS=-std=c++11
DEBUG=-g -O2
SDL=-lSDL2main -lSDL2 -lSDL2_image -lsqlite3
SRCS=main.cpp App.cpp GameObject.cpp Mask.cpp TextureBank.cpp FileManager.cpp Stringify.cpp Texture.cpp ExternalLibs/bitmask.cpp CardGame/Card.cpp CardGame/In_Play.cpp CardGame/Player.cpp CardGame/DataBase.cpp CardGame/Create_Deck.cpp

OBJS=${SRCS:.cpp=.o}
OUT=game

all: compile moveLibObjs
	${CXX} ${OBJS} ${SDL} -o ${OUT}
	make clean

debug: compile-debug moveLibObjs
	${CXX} ${OBJS} $(SDL) -o ${OUT} 

compile:
	${CXX} ${CFLAGS} -c ${SRCS}

compile-debug:
	${CXX} ${CFLAGS} ${DEBUG} -c ${SRCS}


moveLibObjs:
	mv bitmask.o ExternalLibs
	mv Card.o CardGame
	mv In_Play.o CardGame
	mv Player.o CardGame
	mv DataBase.o CardGame
	mv Create_Deck.o CardGame
clean:
	rm -f *.o */*.o
