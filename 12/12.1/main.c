#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "myQ.h"
int main()
{
    Graph G;
    FILE *fin;

    int num;
    char name[20];
    myQ porcodio;
    porcodio=myQinit();
    char las1[20], las2[20];
    int wt;

    fin=fopen("grafo.txt", "r");
    G=GRAPHload(fin);
    GRAPHstore(G, stdout);
    GRAPHtoDAG(G);
   // fscanf(fin,"%d", &num);
   // for(int i=0; i<num; i++)
   //     fscanf(fin,"%s", name);
  //  while (fscanf(fin, "%s %s %d", las1, las2, &wt)!=EOF)
    //    myQinsert(porcodio, EDGEcreate(1, 1, wt));
    return 0;
}
