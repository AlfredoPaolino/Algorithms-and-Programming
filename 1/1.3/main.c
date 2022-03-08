#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
#define M 3

typedef struct
{
    char selettore[N];
    int indice;
    char direzione[N];
    int posizione;
} richiesta;

void salva_matrice(int matrice[N][M], int *pnr, int *pnc);

void stampa_matrice(int matrice[N][M], int nr, int nc);

richiesta elabora_scelta(richiesta tabella);

void ruota(int matrice[N][M], int nr, int nc, richiesta tabella);

int main()
{
    int nr, nc;
    int *pnr=&nr, *pnc=&nc;
    int matrice[N][M];
    richiesta tabella;

    salva_matrice(matrice, pnr, pnc);

    do
    {
        stampa_matrice(matrice, nr, nc);
        tabella=elabora_scelta(tabella);

        if(strcmp(tabella.selettore,"fine")!=0)
            ruota(matrice, nr, nc, tabella);
    }
    while (strcmp(tabella.selettore,"fine")!=0);

    return 0;
}

 void salva_matrice(int matrice[N][M],int *pnr, int *pnc)
 {
    FILE *fp;
    int i, j;

    fp=fopen("matrice.txt", "r");
    fscanf(fp,"%d %d", pnr, pnc);
        for (i=0;i<*pnr;i++)
        {
            for (j=0;j<*pnc;j++)
                fscanf(fp,"%d", &matrice[i][j]);
            fgetc(fp);
        }
    fclose(fp);
 }

void stampa_matrice(int matrice[N][M], int nr, int nc)
{
    int i, j;

    for (i=0;i<nr;i++)
        {
            for (j=0;j<nc;j++)
                printf("%d ", matrice[i][j]);
            printf("\n");
        }
}

richiesta elabora_scelta(richiesta tabella)
{
    printf("<riga> <colonna> <fine>: ");
    scanf("%s", tabella.selettore);

    if (strcmp(tabella.selettore, "fine")!=0)
    {
        printf("<indice>: ");
        scanf("%d", &tabella.indice);
        printf("<destra> <sinistra> <su> <giu>: ");
        scanf("%s", tabella.direzione);
        printf("<posizioni>: ");
        scanf("%d", &tabella.posizione);
    }

    return tabella;
}

void ruota(int matrice[N][M], int nr, int nc, richiesta tabella)
{
    int i, j;
    int temp[tabella.posizione];
    j=0;

    if(strcmp(tabella.direzione,"sinistra")==0)
        tabella.posizione=nc-tabella.posizione;
    if(strcmp(tabella.direzione,"su")==0)
        tabella.posizione=nr-tabella.posizione;

    if(strcmp(tabella.selettore, "riga")==0)
    {
        for (i=nc-tabella.posizione;i<nc;i++, j++)
           temp[j]=matrice[tabella.indice][i];
        for (i=nc-1;i>=tabella.posizione;i--)
            matrice[tabella.indice][i]=matrice[tabella.indice][i-tabella.posizione];
        for (i=0;i<tabella.posizione;i++)
            matrice[tabella.indice][i]=temp[i];
    }

    else if(strcmp(tabella.selettore, "colonna")==0)
    {
        for (i=nr-tabella.posizione;i<nr;i++, j++)
           temp[j]=matrice[i][tabella.indice];
        for (i=nr-1;i>=tabella.posizione;i--)
            matrice[i][tabella.indice]=matrice[i-tabella.posizione][tabella.indice];
        for (i=0;i<tabella.posizione;i++)
            matrice[i][tabella.indice]=temp[i];
    }
}
