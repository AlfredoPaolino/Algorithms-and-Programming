#include <stdio.h>
#include <stdlib.h>

#define N 10

int main()
{
    int i, j, count, temp, flag, ultimo;
    int v[N];
    count=0;
    temp=0;

    //inserimento vettore

    for(i=0;i<N;i++)
    {
        printf("inserire v[%d] ", i);
        scanf("%d", &v[i]);
    }

    //ricerca lunghezza sottovettori massimi

    for(i=0;i<N;i++)
    {
        if (v[i]!=0)
            temp++;
        else
        {
            if (temp>count)
            count=temp;
            temp=0;
        }
    }

    // stampa dei sottovettori massimi

    for (i=0;i<(N-count);i++)
    {
       flag=0;
       for(j=i;j<i+count;j++)
        {
            if (v[j]==0)
                {
                  ultimo=j;
                  flag=1;
                }
        }
        if (flag==1)
            i=ultimo;
        else
        {
            for (j=i;j<i+count;j++)
                printf("%d ", v[j]);
                printf("\n");
        }
    }
    return 0;
}
