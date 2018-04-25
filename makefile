CFLAGS = -g -Wall -Wno-unused-result -O3 

all: floodit util heuristicas

util: geramapa verifica anima

heuristicas: floodit_h1

floodit: mapa.h mapa.c floodit.c

floodit_h1: mapa.h mapa.c floodit_h1.c

geramapa: mapa.h mapa.c geramapa.c

verifica: mapa.h mapa.c verifica.c

anima: mapa.h mapa.c anima.c

clean:
	rm -f floodit geramapa verifica anima *.o
	rm -f floodit_h1
