#include <stdio.h>
#include <stdlib.h>

#define N 6

typedef struct
{
    int tempo_inizio;
    int tempo_fine;
} attivita;

void seleziona_attivita(attivita *v);

void seleziona_attivita_r(attivita *v, int *sol, int *best_sol, int pos, int durata_attuale, int *durata_massima);

int check1(attivita *v, int *sol, int pos, int durata_attuale, int durata_massima);

int check2(attivita *v, int *sol, int pos);

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
    seleziona_attivita(v);

    return 0;
}

void seleziona_attivita(attivita *v)
{
    int sol[N], best_sol[N], durata_attuale=0, durata_massima=0, i;
    seleziona_attivita_r(v, sol, best_sol, 0, durata_attuale, &durata_massima);
    printf("\nattivita' compatibili con durata massima: ");
    for(i=0; i<N; i++)
    {
        if(best_sol[i]==1)
            printf("(%d %d) ",v[i].tempo_inizio, v[i].tempo_fine);
    }
    printf("\n");
}

void seleziona_attivita_r(attivita *v, int *sol, int *best_sol, int pos, int durata_attuale, int *durata_massima)
{
    int i;

    if(pos==N)
    {
        if(durata_attuale>*durata_massima)
        {
            *durata_massima=durata_attuale;
            for(i=0; i<N; i++)
                best_sol[i]=sol[i];
        }
        return;
    }
    if(check1(v, sol, pos, durata_attuale, *durata_massima))
    {
        if (check2(v, sol, pos))
        {
            sol[pos]=1;
            durata_attuale+=v[pos].tempo_fine-v[pos].tempo_inizio;
            seleziona_attivita_r(v, sol, best_sol, pos+1, durata_attuale, durata_massima);
            durata_attuale-=v[pos].tempo_fine-v[pos].tempo_inizio;
        }
        sol[pos]=0;
        seleziona_attivita_r(v, sol, best_sol, pos+1, durata_attuale, durata_massima);
    }
}

int check1(attivita *v, int *sol, int pos, int durata_attuale, int durata_massima)
{
    int i, rimanente=0;

    for(i=pos; i<N; i++)
    {
        rimanente+=v[i].tempo_fine-v[i].tempo_inizio;
    }
    if(durata_attuale+rimanente<durata_massima)
        return 0;
    return 1;
}

int check2(attivita *v, int *sol, int pos)
{
    int i;
    for(i=0; i<pos; i++)
    {
        if(sol[i]==1)
        {
            if((v[pos].tempo_inizio>=v[i].tempo_inizio && v[pos].tempo_inizio<v[i].tempo_fine) || (v[pos].tempo_fine>v[i].tempo_inizio && v[pos].tempo_fine<=v[i].tempo_fine))
                return 0;
        }
    }
    return 1;
}
