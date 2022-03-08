#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHgetIndex(Graph G, char *vertice);
void  MATRIXprint(FILE *fout, Graph G);
void  LISTprint(FILE *fout, Graph G);
void  GRAPHprint(FILE *fout, Graph G);
void  GRAPHmatrixToList(Graph G);
int   MATRIXverificaAdiacenza(Graph G, int id1, int id2, int id3);
int   LISTverificaAdiacenza(Graph G, int id1, int id2, int id3);

#endif // GRAFO_H_INCLUDED
