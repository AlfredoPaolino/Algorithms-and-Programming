#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

typedef struct node *link;
struct node { int v; int wt; link next;};
struct graph {int V; int E; int **madj; ST tab; link *ladj; link z;};
static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static int **MATRIXinit(int r, int c, int val);
static void  insertEM(Graph G, Edge e);
static void  insertEL(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static link NEW(int v, int wt, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->v = v;
  x->wt = wt;
  x->next = next;
  return x;
}

int **MATRIXinit(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t==NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

void MATRIXprint(FILE *fout, Graph G) {
  int i, j;
  for(i=0; i<G->V; i++) {
    for(j=0; j<G->V; j++)
      fprintf(fout, "%d ", G->madj[i][j]);
    fprintf(fout, "\n");
  }
}

void LISTprint(FILE *fout, Graph G) {
  int i;
  link x;

  for(i=0; i<G->V; i++) {
    fprintf(fout, "%s-> { ", STsearchByIndex(G->tab, i));
    for(x=G->ladj[i]; x!=G->z; x=x->next)
        fprintf(fout, "%s/%d ", STsearchByIndex(G->tab, x->v), x->wt);
    fprintf(fout, "}\n");
  }
  fprintf(fout, "\n");
}

Graph GRAPHinit(int V) {
  int i;

  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXinit(V, V, 0);
  if (G->madj == NULL)
    return NULL;

  G->z = NEW(-1, 0, NULL);
  if (G->z == NULL)
    return NULL;
  G->ladj = malloc(G->V*sizeof(link));
  if (G->ladj == NULL)
    return NULL;
  for (i = 0; i < G->V; i++)
    G->ladj[i] = G->z;

  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  link t, next;

  for (i=0; i<G->V; i++) {
    free(G->madj[i]);
    for (t=G->ladj[i]; t != G->z; t = next) {
      next = t->next;
      free(t);
    }
  }
  free(G->madj);
  STfree(G->tab);
  free(G->ladj);
  free(G->z);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int id1, id2, wt;
  char elaboratore1[MAXC+1], elaboratore2[MAXC+1];
  char rete1[MAXC+1], rete2[MAXC+1];
  Graph G;
  ST temporanea;

  temporanea=STload(fin);
  temporanea=STsortByName(temporanea);
  G = GRAPHinit(STsize(temporanea));
  STcopy(G->tab, temporanea);
  STfree(temporanea);
  rewind(fin);
  while(fscanf(fin, "%s %s %s %s %d", elaboratore1, rete1, elaboratore2, rete2, &wt)!=EOF) {
    id1 = STsearch(G->tab, elaboratore1);
    id2 = STsearch(G->tab, elaboratore2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, wt);
  }
  return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertEM(G, EDGEcreate(id1, id2, wt));
}

static void  insertEM(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
  G->madj[w][v] = wt;
}

static void  insertEL(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  G->ladj[v] = NEW(w, wt, G->ladj[v]);
}

int GRAPHgetIndex(Graph G, char *vertice) {
  int id;

  id = STsearch(G->tab, vertice);
  return id;
}

void  GRAPHprint(FILE *fout, Graph G) {
  int i, j;

  for(i=0; i<G->V; i++) {
    fprintf(fout, "vertice: %s\n", STsearchByIndex(G->tab, i));
    fprintf(fout, "archi:\n");
    for(j=0; j<G->V; j++) {
      if(G->madj[i][j]!=0) {
        fprintf(fout, "%s %s %d\n", STsearchByIndex(G->tab, i), STsearchByIndex(G->tab, j), G->madj[i][j]);
      }
    }
    fprintf(fout, "\n");
  }
}

void  GRAPHmatrixToList(Graph G) {
  int i, j;
  for(i=0; i<G->V; i++) {
    for(j=0; j<G->V; j++) {
      if(G->madj[i][j]!=0)
        insertEL(G, EDGEcreate(i, j, G->madj[i][j]));

    }
  }
}

int MATRIXverificaAdiacenza(Graph G, int id1, int id2, int id3) {
  if(G->madj[id1][id2]!=0 && G->madj[id1][id3]!=0 && G->madj[id2][id3]!=0)
    return 0;
  return 1;
}

int LISTverificaAdiacenza(Graph G, int id1, int id2, int id3) {
link x;
int count=0;

for(x=G->ladj[id1]; x!=G->z; x=x->next) {
    if(x->v==id2 || x->v==id3)
      count++;
}
for(x=G->ladj[id2]; x!=G->z; x=x->next) {
    if(x->v==id3)
      count++;
}
if(count==3)
  return 0;
return 1;
}
