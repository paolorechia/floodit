CFLAGS = -g -Wall -Wno-unused-result -O3 

#all: floodit util heuristicas heap heuri tree
all: floodit util heuristicas guloso aestrela

util: geramapa verifica anima

heuristicas: floodit_h1

floodit: mapa.h mapa.c floodit.c

floodit_h1: mapa.h mapa.c floodit_h1.c

geramapa: mapa.h mapa.c geramapa.c

verifica: mapa.h mapa.c verifica.c

anima: mapa.h mapa.c anima.c

#heap: heap.h heap.c

#heuri: mapa.h mapa.c heuri.h heuri.c

#tree: mapa.h mapa.c heuri.h heuri.c tree.h tree.c

guloso: mapa.h mapa.c list.h list.c heuri.h heuri.c tree.h tree.c guloso.c

guloso2: mapa.h mapa.c list.h list.c heuri.h heuri.c guloso2.c

aestrela: mapa.h mapa.c list.h list.c heuri.h heuri.c tree.h tree.c heap.h heap.c aestrela.c

aestrela2: mapa.h mapa.c list.h list.c heuri.h heuri.c tree.h tree.c heap.h heap.c aestrela2.c

memtest: mapa.h mapa.c list.h list.c heuri.h heuri.c tree.h tree.c heap.h heap.c memtest.c

clean:
	rm -f floodit geramapa verifica anima *.o
	rm -f floodit_h1
