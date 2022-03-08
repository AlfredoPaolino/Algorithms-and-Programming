#include <stdio.h>
#include <stdlib.h>

#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);

int main()
{
    int N, i, v[maxN], P, dir;

    //inizializzazione vettore

    do
    {
        printf("inserire lunghezza vettore: ");
        scanf("%d", &N);
        if (N>maxN)
            printf("lunghezza troppo elevata\n");
    }
    while (N>maxN);
    for (i=0;i<N;i++)
    {
        printf("inserire v[%d]: ", i);
        scanf("%d", &v[i]);
    }

    //richieste e chiamata a funzione

    do
    {
        printf("indicare il numero di posti: ");
        scanf("%d", &P);
        if (P!=0)
        {
            do
            {
                printf("indicare la direzione (1 per destra -1 per sinistra): ");
                scanf("%d", &dir);
                if (dir!=-1 && dir!=1)
                    printf("direzione errata\n");
            }
            while (dir!=-1 && dir!=1);
        }
        if (P!=0)
        {
            P=P%N;
            ruota(v, N, P, dir);
        }
    }
    while (P!=0);

    //stampa

    for (i=0;i<N;i++)
        printf("%d ", v[i]);
    return 0;
}

void ruota(int v[maxN], int N, int P, int dir)
{
    int i, j;
    int temp[P];
    if(dir==1)
    {
        j=0;
        for (i=N-P;i<N;i++)
        {
           temp[j]=v[i];
           j++;
        }
        for (i=N-1;i>=P;i--)
            v[i]=v[i-P];
        for (i=0;i<P;i++)
            v[i]=temp[i];
    }
    else if (dir==-1)
    {
        j=0;
        for (i=0;i<P;i++)
         temp[i]=v[i];
        for (i=P;i<N;i++)
        {
            v[j]=v[i];
            j++;
        }
        j=N-P;
        for (i=0;i<P;i++)
        {
            v[j]=temp[i];
            j++;
        }
    }
}


/*void ruota(int v[maxN], int N, int P, int dir)
{
    int i, pos, count, tempin, tempout;
    pos=0;
    if (dir==1)
    {
        for (i=0;i<P;i++)
        {
            count=0;
            while (count<N)
            {
                if(count==0)
                    tempin=v[pos];
                if (pos+1<N)
                {
                    tempout=v[pos+1];
                    v[pos+1]=tempin;
                    tempin=tempout;
                    pos=pos+1;
                }
                else
                {
                    tempout=v[0];
                    v[0]=tempin;
                    tempin=tempout;
                    pos=0;
                }
            count++;
            }
        }
    }
    if (dir==-1)
    {
        for (i=0;i<P;i++)
        {
            count=0;
            while (count<N)
            {
                if(count==0)
                    tempin=v[pos];
                if (pos-1>=0)
                {
                    tempout=v[pos-1];
                    v[pos-1]=tempin;
                    tempin=tempout;
                    pos=pos-1;
                }
                else
                {
                    tempout=v[N-1];
                    v[N-1]=tempin;
                    tempin=tempout;
                    pos=N-1;
                }
            count++;
            }
        }
    }
}*/
