#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR 30
#define NS 20
#define NT 12
#define NZ 7

void inizializza_matrice(int matrice4d[NR+1][NS+1][NT+1][NZ+1]);

int fR(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4]);
int fS(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4]);
int fT(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4]);
int fZ(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4]);

int max(int a, int b);

int main()
{
    int matrice4d[NR+1][NS+1][NT+1][NZ+1], numero_pietre[4]={NR, NS, NT, NZ}, lunghezza_masssima=0;

    inizializza_matrice(matrice4d);
    matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=fR(matrice4d, numero_pietre);
    if(matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]>lunghezza_masssima)
        lunghezza_masssima=matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]];

    inizializza_matrice(matrice4d);
    matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=fS(matrice4d, numero_pietre);
    if(matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]>lunghezza_masssima)
        lunghezza_masssima=matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]];

    inizializza_matrice(matrice4d);
    matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=fT(matrice4d, numero_pietre);
    if(matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]>lunghezza_masssima)
        lunghezza_masssima=matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]];

    inizializza_matrice(matrice4d);
    matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=fZ(matrice4d, numero_pietre);

    if(matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]>lunghezza_masssima)
        lunghezza_masssima=matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]];

    printf("lunghezza massima: %d", lunghezza_masssima);
    return 0;
}


void inizializza_matrice(int matrice4d[NR+1][NS+1][NT+1][NZ+1])
{
    int i, j, k, l;

    for(i=0; i<=NR; i++)
    {
        for(j=0; j<=NS; j++)
        {
            for(k=0; k<=NT; k++)
            {
                for(l=0; l<=NZ; l++)
                    matrice4d[i][j][k][l]=-1;
            }
        }
    }
}

int fR(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4])
{
    int a, b;

    if(numero_pietre[0]==0)
        return 0;

    if(matrice4d[numero_pietre[0]-1][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]==-1)
    {
        numero_pietre[0]-=1;
        a=fS(matrice4d, numero_pietre);
        b=fT(matrice4d, numero_pietre);
        matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=max(a, b);
        numero_pietre[0]+=1;
    }
    return matrice4d[numero_pietre[0]-1][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]+1;
}

int fS(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4])
{
    int a, b;

   if(numero_pietre[1]==0)
        return 0;

    if(matrice4d[numero_pietre[0]][numero_pietre[1]-1][numero_pietre[2]][numero_pietre[3]]==-1)
    {
        numero_pietre[1]-=1;
        a=fS(matrice4d, numero_pietre);
        b=fT(matrice4d, numero_pietre);
        matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=max(a, b);
        numero_pietre[1]+=1;
    }
    return matrice4d[numero_pietre[0]][numero_pietre[1]-1][numero_pietre[2]][numero_pietre[3]]+1;
}

int fT(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4])
{
    int a, b;

    if(numero_pietre[2]==0)
        return 0;

    if(matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]-1][numero_pietre[3]]==-1)
    {
        numero_pietre[2]-=1;
        a=fZ(matrice4d, numero_pietre);
        b=fR(matrice4d, numero_pietre);
        matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=max(a, b);
        numero_pietre[2]+=1;
    }
    return matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]-1][numero_pietre[3]]+1;
}

int fZ(int matrice4d[NR+1][NS+1][NT+1][NZ+1], int numero_pietre[4])
{
    int a, b;

   if(numero_pietre[3]==0)
        return 0;

    if(matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]-1]==-1)
    {
        numero_pietre[3]-=1;
        a=fZ(matrice4d, numero_pietre);
        b=fR(matrice4d, numero_pietre);
        matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]]=max(a, b);
        numero_pietre[3]+=1;
    }

    return matrice4d[numero_pietre[0]][numero_pietre[1]][numero_pietre[2]][numero_pietre[3]-1]+1;
}

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
