#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define L 25
#define N 20
#define MAX 10

typedef struct
{
    char parola[MAX][L+1];
    int posizione[MAX];
    int contatore;
} dati;

int salva_sequenze(char sequenze[N][L+1]);

void inizializza_contatore(dati occorrenze[N]);

void leggi_testo(int numero_sequenze, char sequenze[N][L+1], dati occorrenze[N]);

char estrai_parola(FILE *fp, char lettura[L+1]);

void stampa_occorrenze(int numero_sequenze, char sequenze[N][L+1], dati occorrenze[N]);

int main()
{
    int numero_sequenze;
    char sequenze[N][L+1];
    dati occorrenze[N];

    inizializza_contatore(occorrenze);

    numero_sequenze=salva_sequenze(sequenze);

    leggi_testo(numero_sequenze, sequenze, occorrenze);

    stampa_occorrenze(numero_sequenze, sequenze, occorrenze);

    return 0;
}

int salva_sequenze(char sequenze[N][L+1])
{
    FILE *fp;
    int numero_sequenze, i;

    fp=fopen("sequenze.txt", "r");
    fscanf(fp, "%d", &numero_sequenze);
    for(i=0; i<numero_sequenze; i++)
        fscanf(fp, "%s", sequenze[i]);
    fclose(fp);

    return numero_sequenze;
}

void inizializza_contatore(dati occorrenze[N])
{
    int i;

    for(i=0; i<N; i++)
        occorrenze[i].contatore=0;
}

void leggi_testo(int numero_sequenze, char sequenze[N][L+1], dati occorrenze[N])
{
    FILE *fp;
    int i, j, finito;
    char lettura[L+1], letturalow[L+1], car;
    char sequenzelow[N][L+1];

    for(i=0; i<numero_sequenze; i++)
    {
        for(j=0; j<strlen(sequenze[i]); j++)
            sequenzelow[i][j]=tolower(sequenze[i][j]);
        sequenzelow[i][j]='\0';
    }

    fp=fopen("testo.txt", "r");
    finito=0;
    j=1;
    while(!finito)
    {
        car=estrai_parola(fp, lettura);

        if (strlen(lettura)>0)
        {
            for(i=0; i<strlen(lettura); i++)
                letturalow[i]=tolower(lettura[i]);
            letturalow[i]='\0';

            for(i=0; i<numero_sequenze; i++)
            {
                if(strstr(letturalow, sequenzelow[i])!=NULL && occorrenze[i].contatore<MAX)
                {
                    strcpy(occorrenze[i].parola[occorrenze[i].contatore], lettura);
                    occorrenze[i].posizione[occorrenze[i].contatore]=j;
                    occorrenze[i].contatore++;
                }
            }

            j++;
        }
    if(car==EOF)
        finito=1;
    }
    fclose(fp);
}

char estrai_parola(FILE *fp, char lettura[L+1])
{
    int i;
    char car;
    i=0;

    do
    {
        car=fgetc(fp);
        if(isalnum(car))
        {
            lettura[i]=car;
            i++;
        }
    }
    while (isalnum(car));

    lettura[i]='\0';
    return car;
}

void stampa_occorrenze(int numero_sequenze, char sequenze[N][L+1], dati occorrenze[N])
{
    int i, j;

    for(i=0; i<numero_sequenze; i++)
    {
        printf("la sequenza %s e' contenuta in:\n", sequenze[i]);
        for(j=0; j<occorrenze[i].contatore; j++)
            printf("%s (posizione %d)\n", occorrenze[i].parola[j], occorrenze[i].posizione[j]);
        printf("\n");
    }
}
