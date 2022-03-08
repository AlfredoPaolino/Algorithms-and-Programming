#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int u;
    int v;
} arco;

void compila_tabella(arco **tabella, int *numero_vertici, int *numero_archi);

void powerset(int *sol, int pos, int numero_vertici, arco *tabella);

int confronta_vertexcover(int *sol, int numero_vertici, arco *tabella);

void stampa_vertexcover(int *sol, int numero_vertici);

int main()
{
    int numero_vertici, numero_archi, *sol, pos=0;
    arco *tabella;

    compila_tabella(&tabella, &numero_vertici, &numero_archi);

    sol=malloc(numero_vertici*sizeof(int));
    printf("per il grafo selezionato esistono i seguenti vertex cover:\n");
    powerset(sol, pos, numero_vertici, tabella);
    return 0;
}

void compila_tabella(arco **tabella, int *numero_vertici, int *numero_archi)
{
    FILE *fp;
    int i;

    fp=fopen("archi.txt", "r");
    fscanf(fp, "%d %d", numero_vertici, numero_archi);

    *tabella=malloc(*numero_archi*sizeof(arco));

    for(i=0; i<*numero_archi; i++)
    {

        fscanf(fp, "%d %d", &(*tabella)[i].u, &(*tabella)[i].v);
    }
    fclose(fp);
}

void powerset(int *sol, int pos, int numero_vertici, arco *tabella)
{
    int flag_stampa;

    if(pos>=numero_vertici)
    {
        flag_stampa=confronta_vertexcover(sol, numero_vertici, tabella);
        if(flag_stampa)
            stampa_vertexcover(sol, numero_vertici);
        return;
    }
    sol[pos]=0;
    powerset(sol, pos+1, numero_vertici, tabella);
    sol[pos]=1;
    powerset(sol, pos+1, numero_vertici, tabella);
}

int confronta_vertexcover(int *sol, int numero_vertici, arco *tabella)
{
    int i, j, flag_valido=1, flag_setcover[numero_vertici];

    for(i=0; i<numero_vertici; i++)
        flag_setcover[i]=0;

    for(i=0; i<numero_vertici; i++)
    {
            for(j=0; j<numero_vertici; j++)
            {
                if(sol[i]==1 && (tabella[j].u==i || tabella[j].v==i))
                    flag_setcover[j]=1;
            }
    }
    for(i=0; i<numero_vertici; i++)
    {
        if(flag_setcover[i]==0)
            flag_valido=0;
    }

    return flag_valido;
}

void stampa_vertexcover(int *sol, int numero_vertici)
{
    int i;

    printf("{ ");
    for(i=0; i<numero_vertici; i++)
    {
        if (sol[i]==1)
            printf("%d ", i);
    }
    printf("}\n");
}
