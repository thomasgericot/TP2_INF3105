# Makefile pour TP2.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).


# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
#OPTIONS = -g -O0 -Wall
OPTIONS = -O2 -Wall

all : tp2 testdate

tp2 : tp2.cpp date.o stock.o 
	g++ ${OPTIONS} -o tp2 tp2.cpp date.o stock.o 

date.o : date.cpp date.h
	g++ ${OPTIONS} -c -o date.o date.cpp

stock.o : stock.cpp stock.h arbreavl.h
	g++ ${OPTIONS} -c -o stock.o stock.cpp

testdate : testdate.cpp date.o
	g++ $(OPTIONS) -o testdate testdate.cpp date.o

clean:
	rm -rf tp2 testdate *~ *.o

