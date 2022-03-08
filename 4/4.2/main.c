#include <stdio.h>
#include <stdlib.h>

#define N 9

void quick_sort(int v[], int l, int r);

int partition(int v[], int l, int r);

void swap(int v[], int i, int j);

int majority( int v[]);

int main()
{
    int v[N]={3,3,9,4,3,5,3,3,1};
    int l=0;
    int r=N;
    int maggioritario;

    quick_sort(v, l, r);

    maggioritario=majority(v);

    if(maggioritario!=-1)
        printf("l'elemento maggioritario e': %d", maggioritario);
    else
        printf("non e' presente un elemento maggioritario");
    return 0;
}

void quick_sort(int v[], int l, int r)
{
   int q;

   if(r<=l)
        return;

    q=partition(v, l, r);

    quick_sort(v, l, q-1);

    quick_sort(v, q+1, r);
}

int partition(int v[], int l, int r)
{
    int i, j, x;
    i=l-1;
    j=r;
    x=v[r];

    for( ; ; )
    {
        while(v[++i]<x);
        while(v[--j]>x)
        {
            if(j==l)
                break;
        }
        if(i>=j)
            break;

        swap(v, i, j);

    }

    swap(v, i, r);

    return i;
}

void swap(int v[], int i, int j)
{
    int temp;
    temp=v[j];
    v[j]=v[i];
    v[i]=temp;
}

int majority( int v[])
{
    int i;

    for(i=0; i<N; i++)
    {
        if(v[i]==v[i+N/2])
            return v[i];
    }

    return -1;
}
