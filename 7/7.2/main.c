#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR 3
#define NS 9
#define NT 9
#define NZ 9

#define VAL_NR 11
#define VAL_NS 5
#define VAL_NT 3
#define VAL_NZ 17

#define MAX_RIP 7

typedef enum {R, S, T, Z, TIPI} pietre;

void perm_r(int pos, char *dist_val, char *sol, int *mark, int *mark_or, int *valore, int *valore_attuale, int *valore_massimo, char *finale);

int check1(int pos, char *sol, char nuovo);

int check2(int pos, char *sol, char nuovo);

int main()
{
    int valore_attuale=0, valore_massimo=0, mark[TIPI]={NR, NS, NT, NZ}, mark_or[TIPI]={NR, NS, NT, NZ}, valore[TIPI]={VAL_NR, VAL_NS, VAL_NT, VAL_NZ};
    char sol[NR+NS+NT+NZ+1]="\0", dist_val[TIPI+1]="RSTZ", finale[NR+NS+NT+NZ+1]="\0";

    perm_r(0, dist_val, sol, mark, mark_or, valore, &valore_attuale, &valore_massimo, finale);

    printf("%d %s\n", valore_massimo, finale);
    return 0;
}

void perm_r(int pos, char *dist_val, char *sol, int *mark, int *mark_or, int *valore, int *valore_attuale, int *valore_massimo, char *finale)
{
    int i;

    if(*valore_attuale>*valore_massimo && mark_or[Z]-mark[Z]<=mark_or[S]-mark[S])
    {
        *valore_massimo=*valore_attuale;
        strcpy(finale, sol);
    }

    for(i=0; i<TIPI; i++)
    {
        if(mark[i]>0 && check1(pos, sol, dist_val[i]) && check2(pos, sol, dist_val[i]))
        {
            mark[i]--;
            sol[pos]=dist_val[i];
            sol[pos+1]='\0';
            *valore_attuale+=valore[i];
            perm_r(pos+1, dist_val, sol, mark, mark_or, valore, valore_attuale, valore_massimo, finale);
            mark[i]++;
            *valore_attuale-=valore[i];
        }
    }
}

int check1(int pos, char *sol, char nuovo)
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
    return 0;
    }
}

int check2(int pos, char *sol, char nuovo)
{
    int i;

    if(pos<MAX_RIP)
        return 1;
    else
    {
        for(i=pos-MAX_RIP; i<pos; i++)
        {
            if(sol[i]!=nuovo)
                return 1;
        }
        return 0;
    }
}
