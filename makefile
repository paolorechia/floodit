CFLAGS = -g -Wall -Wno-unused-result -O3

#all: floodit util floodit_h1 aestrela 

all: util floodit_h1 aestrela 

util: geramapa verifica anima

verifica: mapa.h mapa.c verifica.c

anima: mapa.h mapa.c anima.c

#floodit: mapa.h mapa.c floodit.c

floodit_h1: mapa.h mapa.c floodit_h1.c

geramapa: mapa.h mapa.c geramapa.c

aestrela: mapa.h mapa.c list.h list.c heuri.h heuri.c hashtable.h hashtable.c heap.h heap.c aestrela.c

clean:
	rm -f geramapa verifica anima *.o
	rm -f aestrela
#	rm -f floodit geramapa verifica anima *.o
#	rm -f floodit_h1
