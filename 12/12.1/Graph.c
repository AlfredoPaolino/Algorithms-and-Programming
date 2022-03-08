#include "Graph.h"

#define maxWT INT_MAX
#define MAXC 10

typedef struct node *link;
struct node { int v; int wt; int analizzato; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static link  NEW(int v, int wt, int analizzato, link next);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);

static link NEW(int v, int wt, int anaizzato, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->v = v;
  x->wt = wt;
  x->analizzato=anaizzato;
  x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;

  G->V = V;
  G->E = 0;
  G->z = NEW(-1, 0, 0, NULL);
  if (G->z == NULL)
    return NULL;
  G->ladj = malloc(G->V*sizeof(link));
  if (G->ladj == NULL)
    return NULL;
  for (v = 0; v < G->V; v++)
    G->ladj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int v;
  link t, next;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = next) {
      next = t->next;
      free(t);
    }
  STfree(G->tab);
  free(G->ladj);
  free(G->z);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);
  if (G == NULL)
    return NULL;

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, wt, 0);
  }
  return G;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = t->next)
      a[E++] = EDGEcreate(v, t->v, t->wt, 0);
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;
  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

}

int GRAPHgetIndex(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt, int analizzato) {
  insertE(G, EDGEcreate(id1, id2, wt, analizzato));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2, 0, 0));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt, analizzato=e.analizzato;

  G->ladj[v] = NEW(w, wt, analizzato, G->ladj[v]);
  G->E++;
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  link x;
  if (G->ladj[v]->v == w) {
    G->ladj[v] = G->ladj[v]->next;
    G->E--;
  }
  else
    for (x = G->ladj[v]; x != G->z; x = x->next)
      if (x->next->v == w) {
        x->next = x->next->next;
        G->E--;
  }
}

static Graph reverse(Graph G, Graph R) {
  int v;
  link t;
  for (v=0; v < G->V; v++)
    for (t= G->ladj[v]; t != G->z; t = t->next)
      GRAPHinsertE(R, t->v, v, t->wt, 0);
  return R;
}

static void SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post) {
  link t;
  scc[w] = time1;
  for (t = G->ladj[w]; t != G->z; t = t->next)
    if (scc[t->v] == -1)
      SCCdfsR(G, t->v, scc, time0, time1, post);
  post[(*time0)++]= w;
}

int GRAPHscc(Graph G, int *vCount, int *sccG) {
  int v, time0 = 0, time1 = 0, *sccR, *postG, *postR;
  Graph R;

  R = GRAPHinit(G->V);
  reverse(G, R);

  sccR = malloc(G->V * sizeof(int));
  postG = malloc(G->V * sizeof(int));
  postR = malloc(G->V * sizeof(int));

  for (v=0; v < G->V; v++) {
    sccG[v] = -1;
    sccR[v] = -1;
    postG[v] = -1;
    postR[v] = -1;
    vCount[v] = 0;

  }

  for (v=0; v < G->V; v++)
    if (sccR[v] == -1)
      SCCdfsR(R, v, sccR, &time0, time1, postR);

  time0 = 0;
  time1 = 0;

  for (v = G->V-1; v >= 0; v--)
    if (sccG[postR[v]]==-1){
      SCCdfsR(G,postR[v], sccG, &time0, time1, postG);
      time1++;
    }
  //printf("strongly connected components \n");
  //for (v = 0; v < G->V; v++)
   // printf("node %s in scc %d \n", STsearchByIndex(G->tab, v), sccG[v]);
  for(v = 0; v < G->V; v++)
    vCount[sccG[v]]++;
  GRAPHfree(R);
  return time1;
}

void  GRAPHtoDAG(Graph G)
{
    int v, i, j, maxFlag, flag, *vCount, *sccG, id1, id2, wt, maxId1, maxId2, level;
    int card=0, finito=0;
    link t;
    myQ Qu;
    Edge *stampa;

    vCount=malloc(G->V*sizeof(int));
    sccG=malloc(G->V*sizeof(int));
    stampa=malloc((G->E-G->V+1)*sizeof(Edge));
    Qu=myQinit();

    maxFlag=GRAPHscc(G, vCount, sccG);

    do
    {
        level=0;
        for(v=0; v<G->V; v++)
        {
            for(t=G->ladj[v]; t!=G->z; t=t->next)
            {
                if(t->analizzato==0)
                {
                    GRAPHremoveE(G, v, t->v);
                    flag=GRAPHscc(G, vCount, sccG);
                    printf("%d: %d-%d\n", flag, v, t->v);
                    if(flag==maxFlag)
                    {
                        myQinsert(Qu, EDGEcreate(v, t->v, t->wt, 0));
                        level++;
                    }
                    else if(flag>maxFlag)
                    {
                        maxFlag=flag;
                        for(i=0; i<level; i++)
                            myQfreeFromHead(Qu);
                        myQinsert(Qu, EDGEcreate(v, t->v, t->wt, 0));
                        level=0;
                        level++;
                    }
                    GRAPHinsertE(G, v, t->v, t->wt, 0);
                }
            }
        }
        myQprint(Qu);
        if(maxFlag<G->V)
        {
            stampa[card]=myQextractFromHead(Qu);
            GRAPHremoveE(G, stampa[card].v, stampa[card].w);
            card++;
        }
        if(maxFlag==G->V)
        {
            for(i=0; i<level; i++)
            {
                stampa[card]=myQextractFromHead(Qu);
                GRAPHremoveE(G, stampa[card].v, stampa[card].w);
                for(j=0; j<card+1; j++)
                printf("\n\n%d %d %d\n", stampa[j].v, stampa[j].w, stampa[j].wt);
                GRAPHinsertE(G, stampa[card].v, stampa[card].w, stampa[card].wt, 1);
                printf(" size: %d", myQsize(Qu));
                maxFlag=GRAPHscc(G, vCount, sccG);
            }

            if(myQsize(Qu)==0)
                finito=1;
        }
    }
    while(finito==0);
}
