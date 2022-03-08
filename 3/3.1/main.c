#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef enum {FALSO, VERO} boolean;

typedef enum {max_base_i, max_altezza_i, max_area_i, err} indice;

typedef struct
{
    int base;
    int altezza;
    int riga;
    int colonna;
} dati;

void inizializza_struttura(dati massimo[]);

void salva_matrice(int matrice[N][N], int *p_nr, int *p_nc);

void leggi_matrice(int matrice[N][N], int nr, int nc, dati massimo[]);

void confronta_rettangoli(int basecfr, int altezzacfr, int rigacfr, int colonnacfr, dati massimo[]);

void stampa_massimi(dati massimo[]);

int riconosci_regione(int matrice[N][N], int nr, int nc, int riga, int colonna, int *p_base, int *p_altezza);

int main()
{
    dati massimo[err];
    int matrice[N][N];
    int nr, nc;
    int *p_nr=&nr, *p_nc=&nc;

    inizializza_struttura(massimo);

    salva_matrice(matrice, p_nr, p_nc);

    leggi_matrice(matrice, nr, nc, massimo);

    stampa_massimi(massimo);

    return 0;
}

void inizializza_struttura(dati massimo[])
{
    int i;

    for (i=0; i<err; i++)
    {
        massimo[i].base=0;
        massimo[i].altezza=0;
        massimo[i].riga=0;
        massimo[i].colonna=0;
    }
}

void salva_matrice(int matrice[N][N], int *p_nr, int *p_nc)
{
    FILE *fp;
    int i, j;

    fp=fopen("mappa.txt", "r");
    fscanf(fp, "%d %d", p_nr, p_nc);
    for (i=0; i<*p_nr; i++)
    {
        for (j=0; j<*p_nc; j++)
            fscanf(fp, "%d", &matrice[i][j]);
    }
    fclose(fp);
}

void leggi_matrice( int matrice[N][N], int nr, int nc, dati massimo[])
{
    int i, j, trovato;
    int base, altezza;
    int *p_base=&base, *p_altezza=&altezza;

    for (i=0; i<nr; i++)
    {
        for (j=0; j<nc;j++)
        {
            trovato=riconosci_regione(matrice, nr, nc, i, j, p_base, p_altezza);

            if(trovato==1)
            {
                printf("rettangolo trovato: estr. sup. sx=(%d,%d), base=%d, altezza=%d, area=%d\n", i, j, base, altezza, base*altezza);
            }
                confronta_rettangoli(base, altezza, i, j, massimo);
        }
    }
}

int riconosci_regione(int matrice[N][N], int nr, int nc, int riga, int colonna, int *p_base, int *p_altezza)
{
    int k;
    *p_base=0;
    *p_altezza=0;

    if ((riga-1<0||matrice[riga-1][colonna]==0)&&(colonna-1<0||matrice[riga][colonna-1]==0)&&matrice[riga][colonna]==1)
    {
        (*p_base)++;
        (*p_altezza)++;
        k=1;

        while (colonna+k<nc && matrice[riga][colonna+k]==1)
        {
            (*p_base)++;
            k++;
        }

        k=1;
        while (riga+k<nr && matrice[riga+k][colonna]==1)
        {
            (*p_altezza)++;
            k++;
        }

        return VERO;
    }

    return FALSO;
}

void confronta_rettangoli(int basecfr, int altezzacfr, int rigacfr, int colonnacfr, dati massimo[])
{
    int areacfr;
    areacfr=basecfr*altezzacfr;

    if (basecfr>massimo[max_base_i].base)
    {
        massimo[max_base_i].base=basecfr;
        massimo[max_base_i].altezza=altezzacfr;
        massimo[max_base_i].riga=rigacfr;
        massimo[max_base_i].colonna=colonnacfr;
    }

    if (altezzacfr>massimo[max_altezza_i].altezza)
    {
        massimo[max_altezza_i].base=basecfr;
        massimo[max_altezza_i].altezza=altezzacfr;
        massimo[max_altezza_i].riga=rigacfr;
        massimo[max_altezza_i].colonna=colonnacfr;
    }

    if (areacfr>massimo[max_area_i].base*massimo[max_area_i].altezza)
    {
        massimo[max_area_i].base=basecfr;
        massimo[max_area_i].altezza=altezzacfr;
        massimo[max_area_i].riga=rigacfr;
        massimo[max_area_i].colonna=colonnacfr;
    }
}

void stampa_massimi(dati massimo[])
{
    printf("max base: estr. sup. sx=(%d,%d), base=%d, altezza=%d, area=%d\n", massimo[max_base_i].riga, massimo[max_base_i].colonna, massimo[max_base_i].base, massimo[max_base_i].altezza, massimo[max_base_i].base*massimo[max_base_i].altezza);
    printf("max altezza: estr. sup. sx=(%d,%d), base=%d, altezza=%d, area=%d\n", massimo[max_altezza_i].riga, massimo[max_altezza_i].colonna, massimo[max_altezza_i].base, massimo[max_altezza_i].altezza, massimo[max_altezza_i].base*massimo[max_altezza_i].altezza);
    printf("max area: estr. sup. sx=(%d,%d), base=%d, altezza=%d, area=%d", massimo[max_area_i].riga, massimo[max_area_i].colonna, massimo[max_area_i].base, massimo[max_area_i].altezza, massimo[max_area_i].base*massimo[max_area_i].altezza);
}
