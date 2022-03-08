#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 20

int main()
{
    FILE *fp;
    int nr, nc, dim,i, j, k, l, count, max, imax, jmax;
    int matrix[N][N];

    //lettura file

    fp=fopen("matrice.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);
    for (i=0;i<nr;i++)
    {
        for (j=0;j<nc;j++)
        {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }

    //richiesta

    do
    {
        max=INT_MIN;
        printf("inserire dimensioni sottomatrice desiderata: ");
        scanf("%d", &dim);
        if (dim<nr && dim<nc && dim>0)
        {
            for (i=0;i<nr-dim+1;i++)
            {
                for(j=0;j<nc-dim+1;j++)
                {
                    count=0;
                    for(k=i;k<i+dim;k++)
                    {
                        for(l=j;l<j+dim;l++)
                        {
                            printf("%d ", matrix[k][l]);
                            count+=matrix[k][l];
                        }
                        if (count>max)
                        {
                            max=count;
                            imax=i;
                            jmax=j;
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            }
            printf("imax:%d jmax:%d \n\n", imax, jmax);
            for(i=imax;i<imax+dim;i++)
            {
                for(j=jmax;j<jmax+dim;j++)
                printf("%d ", matrix[i][j]);
                printf("\n");
            }
            printf("\n");
        }
    }
    while (dim<nr && dim<nc && dim>0);
    return 0;
}
