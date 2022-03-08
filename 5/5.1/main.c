#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 255

typedef struct
{
    char **scelte;
    int num_scelte;
} livello;

void costruisci_albero(livello **val, int *altezza);

int principio_moltiplicazione(char **sol, livello *val, int pos, int altezza, int numero_playlist);

int main()
{
    livello *val;
    int altezza, numero_playlist=0, pos=0;
    char **sol;

    costruisci_albero(&val, &altezza);

    sol=malloc(altezza*sizeof(char*));

    numero_playlist=principio_moltiplicazione(sol, val, pos, altezza, numero_playlist);

    return 0;
}
void costruisci_albero(livello **val, int *altezza)
{
    int i, j;
    FILE *fp;

    fp=fopen("brani.txt", "r");
    fscanf(fp, "%d", altezza);

    *val=malloc(*altezza*sizeof(livello));
    for(i=0; i<*altezza; i++)
    {
        fscanf(fp, "%d", &(*val)[i].num_scelte);
        printf("%d\n", (*val)[i].num_scelte);
        (*val)[i].scelte=malloc((*val)[i].num_scelte*sizeof(char*));
        for(j=0; j<(*val)[i].num_scelte; j++)
        {
            (*val)[i].scelte[j]=malloc(S*sizeof(char));
            fscanf(fp, "%s", (*val)[i].scelte[j]);
        }
    }
    fclose(fp);
}

int principio_moltiplicazione(char **sol, livello *val, int pos, int altezza, int numero_playlist)
{
    int i;

    if(pos>=altezza)
    {
        printf("%d\n", ++numero_playlist);
        for(i=0; i<altezza; i++)
            printf("%s\n", sol[i]);

        return numero_playlist;
    }
    for(i=0; i<val[pos].num_scelte; i++)
    {
        sol[pos]=malloc(S*sizeof(char));
        strcpy(sol[pos], val[pos].scelte[i]);

        numero_playlist=principio_moltiplicazione(sol, val, pos+1, altezza, numero_playlist);
    }

    return numero_playlist;
}
