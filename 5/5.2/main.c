#include <stdio.h>
#include <stdlib.h>

int** salva_matrice(int *nr, int *nc);

void separa(int **matrice, int nr, int nc, int **v_bianco, int **v_nero, int *count_bianco, int *count_nero);

int main()
{
    int nr, nc, i;
    int **matrice, *v_bianco, *v_nero, count_bianco, count_nero;

    matrice=salva_matrice(&nr, &nc);

    separa(matrice, nr, nc, &v_bianco, &v_nero, &count_bianco, &count_nero);

    printf("vettore bianco: ");
    for(i=0; i<count_bianco; i++)
        printf("%d ", v_bianco[i]);

    printf("\nvettore nero: ");
    for(i=0; i<count_nero; i++)
        printf("%d ", v_nero[i]);

    return 0;
}

int** salva_matrice(int *nr, int *nc)
{
    int i, j;
    FILE *fp;
    int **matrice;

    fp=fopen("matrice.txt", "r");
    fscanf(fp, "%d %d", nr, nc);

    matrice=malloc(*nr*sizeof(int*));

    for(i=0; i<*nr; i++)
        matrice[i]=malloc(*nc* sizeof(int));

    for(i=0; i<*nr; i++)
    {
        for (j=0; j<*nc; j++)
            fscanf(fp, "%d", &matrice[i][j]);
    }
    fclose(fp);
    return matrice;
}

void separa(int **matrice, int nr, int nc, int **v_bianco, int **v_nero, int *count_bianco, int *count_nero)
{
    int i, j;
    *count_bianco=0;
    *count_nero=0;

    if((nc%2)==0)
        *v_bianco=malloc(nr*nc/2* sizeof(int));
    else
        *v_bianco=malloc((nr*nc/2+1)* sizeof(int));
    *v_nero=malloc(nr*nc/2* sizeof(int));

    for (i=0; i<nr; i++)
    {
        for (j=0; j<nc; j++)
        {
            if(((i+j)%2)==0)
                (*v_bianco)[(*count_bianco)++]=matrice[i][j];
            else
                (*v_nero)[(*count_nero)++]=matrice[i][j];
        }
    }
}

