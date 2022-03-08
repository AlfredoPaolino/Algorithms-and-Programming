#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void apertura_menu();
void smista(int scelta, Graph G);

int main(int argc, char **argv)
{
    Graph G;
    FILE *fin;
    int scelta;

    fin=fopen(argv[1], "r");
    G=GRAPHload(fin);
    fclose(fin);
    do
    {
        apertura_menu();
        scanf("%d", &scelta);
        smista(scelta, G);
    }
    while(scelta!=3);
    GRAPHfree(G);
    return 0;
}

void apertura_menu()
{
    printf("0 per: elencare vertici e archi in ordine alfabetico\n");
    printf("1 per: verificare se 3 vertici sono adicaenti a coppie\n");
    printf("2 per: generare la lista di adiacenza\n");
    printf("3 per: terminare l'esecuzione\n");
}

void smista(int scelta, Graph G)
{
    char vertice1[MAXC+1], vertice2[MAXC+1], vertice3[MAXC+1];
    int id1, id2, id3, completo;

    switch(scelta)
    {
    case 0:
        GRAPHprint(stdout, G);
        break;

    case 1:
        printf("inserire i nomi dei tre vertici:\n");
        scanf("%s %s %s", vertice1, vertice2, vertice3);
        id1=GRAPHgetIndex(G, vertice1);
        id2=GRAPHgetIndex(G, vertice2);
        id3=GRAPHgetIndex(G, vertice3);
        completo=MATRIXverificaAdiacenza(G, id1, id2, id3);
        if(completo==0)
            printf("\ni tre vertici formano un sottografo completo\n\n");
        else
            printf("\ni tre vertici non formano un sottografo completo\n\n");
        break;

    case 2:
        GRAPHmatrixToList(G);
        LISTprint(stdout, G);
        break;

    case 3:

        break;

    default:

        printf("comando non valido\n");
        break;
    }
}
