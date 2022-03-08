#include <stdio.h>
#include <stdlib.h>

#define N 20
#define M 20

void leggi_file(int matrix[N][M], int *p_righe_max, int *p_colonne_max);

void trova_capolista(int matrix[N][M], int colonna, int righe_max, int punti_capolista, int punti[]);

int main()
{
    int i, j;
    int righe_max, colonne_max, punti_capolista;
    int *p_righe_max=&righe_max , *p_colonne_max=&colonne_max;
    int matrix[N][M], punti[N];

    leggi_file(matrix, p_righe_max, p_colonne_max);

    punti_capolista=0;
    for (i=0;i<N;i++)
        punti[i]=0;

    for (j=0;j<colonne_max;j++)
        trova_capolista(matrix, j, righe_max, punti_capolista, punti);

    return 0;
}

void leggi_file(int matrix[N][M], int *p_righe_max, int *p_colonne_max)
{
    FILE *fp;
    int colonne;
    char c;
    *p_righe_max=0;
    colonne=0;

    fp=fopen("matrice.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%d", &matrix[*p_righe_max][colonne]);
        colonne++;
        c=fgetc(fp);

        if (c=='\n')
        {
            (*p_righe_max)++;
            *p_colonne_max=colonne;
            colonne=0;
        }
    }
    fclose(fp);
}

void trova_capolista(int matrix[N][M], int colonna, int righe_max, int punti_capolista, int punti[])
{
    int riga;

    for (riga=0; riga<righe_max; riga++)
        punti[riga]+=matrix[riga][colonna];

    printf("capolista della giornata %d:\n", colonna+1);

    for (riga=0; riga<righe_max; riga++)
    {
        if (punti[riga]>=punti_capolista)
        {
            punti_capolista=punti[riga];
        }
    }

    for (riga=0; riga<righe_max; riga++)
    {
        if (punti[riga]==punti_capolista)
            printf("squadra %d\n", riga+1);
    }

    printf("con %d punti\n\n", punti_capolista);
}
