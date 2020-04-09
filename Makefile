# Makefile pour TP2.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).


# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
#OPTIONS = -g -O0 -Wall
OPTIONS = -O2 -Wall

all: tp2 testdate	

tp2: tp2.cpp date.o stock.o 
	g++ ${OPTIONS} -o tp2 tp2.cpp date.o stock.o medicament.o

date.o: date.cpp date.h
	g++ ${OPTIONS} -c -o date.o date.cpp

medicament.o: medicament.cpp medicament.h date.o
	g++ ${OPTIONS} -c -o medicament.o medicament.cpp

stock.o: stock.cpp stock.h medicament.o
	g++ ${OPTIONS} -c -o stock.o stock.cpp

testdate: testDate.cpp date.o
	g++ $(OPTIONS) -o testdate testDate.cpp date.o

clean:
	rm -rf tp2 testdate *~ *.o

