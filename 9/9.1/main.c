#include <stdio.h>
#include <stdlib.h>

#define N 6

typedef struct
{
    int tempo_inizio;
    int tempo_fine;
} attivita;

void sort_attivita(attivita *v);

void seleziona_attivita(attivita *v);

void stampa_attivita(attivita *v, int *prev, int indice);

int main()
{
    attivita v[N];
    int i;

    printf("inserire dati:\n");
    for(i=0; i<N; i++)
    {
        printf("\nattivita' %d: ", i);
        scanf("%d %d", &v[i].tempo_inizio, &v[i].tempo_fine);
    }
    sort_attivita(v);
    seleziona_attivita(v);
    return 0;
}
void sort_attivita(attivita *v)
{
    int i, j, min;
    attivita temp;

    for(i=0; i<N-1; i++)
    {
        min=i;
        for(j=i+1; j<N; j++)
        {
            if(v[j].tempo_inizio<v[min].tempo_inizio)
                min=j;
        }
        temp=v[i];
        v[i]=v[min];
        v[min]=temp;
    }
}

void seleziona_attivita(attivita *v)
{
    int i, j, prev[N], durata[N], durata_base, max_indice=0;
    for(i=0; i<N; i++)
    {
        prev[i]=-1;
        durata[i]=v[i].tempo_fine-v[i].tempo_inizio;
        durata_base=durata[i];
        for(j=0; j<i; j++)
        {
           if(v[i].tempo_inizio>=v[j].tempo_fine && durata[i]<durata_base+durata[j])
           {
               prev[i]=j;
               durata[i]=durata_base+durata[j];
           }
        }
    }
    for(i=0; i<N; i++)
        {
            if(durata[i]>durata[max_indice])
                max_indice=i;
        }
    stampa_attivita(v, prev, max_indice);
}

void stampa_attivita(attivita *v, int *prev, int indice)
{
    if(prev[indice]==-1)
    {
        printf("\nattivita' compatibili con durata massima: ");
        printf("(%d %d) ", v[indice].tempo_inizio, v[indice].tempo_fine);
        return;
    }
    stampa_attivita(v, prev, prev[indice]);
    printf("(%d %d) ", v[indice].tempo_inizio, v[indice].tempo_fine);
}
