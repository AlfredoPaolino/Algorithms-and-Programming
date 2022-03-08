#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR 4
#define NS 10
#define NT 7
#define NZ 6

#define TIPI 4

void perm_r(int pos, char *dist_val, char *sol, int *mark, int tipologia_pietre, int *lunghezza_massima, char *finale);

int check(int pos, char *sol, char nuovo);

int main()
{
    int lunghezza_massima=0, mark[TIPI]={NR, NS, NT, NZ};
    char sol[NR+NS+NT+NZ+1]="\0", dist_val[4+1]="RSTZ", finale[NR+NS+NT+NZ+1]="\0";

    perm_r(0, dist_val, sol, mark, TIPI, &lunghezza_massima, finale);

    printf("%d %s\n", lunghezza_massima, finale);
    return 0;
}

void perm_r(int pos, char *dist_val, char *sol, int *mark, int tipologia_pietre, int *lunghezza_massima, char *finale)
{
    int i;

    if(pos>*lunghezza_massima)
    {
        *lunghezza_massima=pos;
        strcpy(finale, sol);
    }

    for(i=0; i<tipologia_pietre; i++)
    {
        if(mark[i]>0 && check(pos, sol, dist_val[i]))
        {
            mark[i]--;
            sol[pos]=dist_val[i];
            sol[pos+1]='\0';
            perm_r(pos+1, dist_val, sol, mark, tipologia_pietre, lunghezza_massima, finale);
            mark[i]++;
        }
    }
}

int check(int pos, char *sol, char nuovo)
{
    if(pos==0)
        return 1;
    else
    {
        if(sol[pos-1]=='R')
        {
            if(nuovo=='S' || nuovo=='T')
                return 1;
        }
        else if(sol[pos-1]=='S')
        {
            if(nuovo=='S' || nuovo=='T')
                return 1;
        }
        else if(sol[pos-1]=='T')
        {
            if(nuovo=='Z' || nuovo=='R')
                return 1;
        }
        else if(sol[pos-1]=='Z')
        {
            if(nuovo=='Z' || nuovo=='R')
                return 1;
        }
    }
    return 0;
}
