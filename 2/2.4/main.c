#include <stdio.h>
#include <stdlib.h>

void leggi_file();

void salva_ordina_vettore(FILE *fp, int lunghezza);

void insertion_sort(int vettore[], int lunghezza);

void selection_sort(int vettore[], int lunghezza);

void shell_sort(int vettore[], int lunghezza);

void stampa(int scambi, int interno, int esterno);

int main()
{
    leggi_file();
    return 0;
}

void leggi_file()
{
    FILE *fp;
    int sequenze, lunghezza, i;

    fp=fopen("sort.txt", "r");
    fscanf(fp, "%d", &sequenze);

    for(i=0; i<sequenze; i++)
    {
        fscanf(fp, "%d", &lunghezza);
        printf("vettore di %d interi\n\n", lunghezza);
        salva_ordina_vettore(fp, lunghezza);
    }
    fclose(fp);
}

void salva_ordina_vettore(FILE *fp, int lunghezza)
{
    int i;
    int vettore[lunghezza];

    for(i=0; i<lunghezza; i++)
        fscanf(fp, "%d", &vettore[i]);

    insertion_sort(vettore, lunghezza);

    selection_sort(vettore, lunghezza);

    shell_sort(vettore, lunghezza);

}

void insertion_sort(int vettore[], int lunghezza)
{
    int i, j, temp;
    int vettore_ins[lunghezza];
    int count_scambi=0, count_int=0, count_est=0;

    for(i=0; i<lunghezza; i++)
        vettore_ins[i]=vettore[i];

    for(i=1; i<lunghezza; i++)
    {
        temp=vettore[i];
        for(j=i-1; j>=0 && temp<vettore_ins[j]; j--)
        {
           vettore_ins[j+1]=vettore_ins[j];
           count_int++;
           count_scambi++;
        }
        if(vettore_ins[j+1]!=temp)
        {
            count_scambi++;
            vettore_ins[j+1]=temp;
        }
        count_est++;
    }
    printf("dati insertion sort\n");

    stampa(count_scambi, count_int, count_est);

}

void selection_sort(int vettore[], int lunghezza)
{
    int i, j, min, temp;
    int vettore_sel[lunghezza];
    int count_scambi=0, count_int=0, count_est=0;

    for(i=0; i<lunghezza; i++)
        vettore_sel[i]=vettore[i];

    for(i=0; i<lunghezza; i++)
    {
        min=i;
        for(j=i+1; j<lunghezza; j++)
        {
            if(vettore_sel[j]<vettore_sel[min])
                min=j;
            count_int++;
        }
        if(vettore_sel[i]!=vettore_sel[min])
        {
            temp=vettore_sel[min];
            vettore_sel[min]=vettore_sel[i];
            vettore_sel[i]=temp;
            count_scambi++;
        }
        count_est++;
    }
    printf("dati selection sort\n");

    stampa(count_scambi, count_int, count_est);

}

void shell_sort(int vettore[], int lunghezza)
{
    int i, j, temp;
    int vettore_shell[lunghezza];
    int h=1;
    int count_scambi=0, count_int=0, count_est=0;

    for(i=0; i<lunghezza; i++)
        vettore_shell[i]=vettore[i];

    while(h<lunghezza/3)
        h=3*h+1;

    while(h>=1)
    {
        for(i=h; i<lunghezza; i++)
        {
            temp=vettore_shell[i];
            for(j=i-h; j>=0 && temp<vettore_shell[j]; j-=h)
            {
                vettore_shell[j+h]=vettore_shell[j];
                count_int++;
                count_scambi++;
            }
            if(vettore_shell[j+h]!=temp);
            {
                vettore_shell[j+h]=temp;
                count_scambi++;
            }
            count_est++;
        }
        h=h/3;
    }
    printf("dati shell sort\n");

    stampa(count_scambi, count_int, count_est);

}

void stampa(int scambi, int interno, int esterno)
{
    printf("numero scambi: %d\n", scambi);
    printf("numero iterazioni ciclo interno: %d\n", interno);
    printf("numero iterazioni ciclo esterno: %d\n", esterno);
    printf("numero iterazioni totali: %d\n\n", interno+esterno);
}
