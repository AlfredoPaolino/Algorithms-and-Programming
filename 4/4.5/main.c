#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 30
#define MAX 1000

typedef enum {r_stampa, r_data, r_codice, r_partenza, r_capolinea, r_fine} indice;

typedef struct
{
    char codice_tratta[S+1];
    char partenza[S+1];
    char destinazione[S+1];
    char data[S+1];
    char ora_partenza[S+1];
    char ora_arrivo[S+1];
    int ritardo;
} dati;

int compila_tabella(dati tabella[]);

void apertura_menu(void);

int leggi_comando(void);

void smista(dati tabella[], int righe, int scelta, dati *tabella_data[], dati *tabella_codice[], dati *tabella_partenza[], dati *tabella_capolinea[], int flag_ordinamenti[]);

void ordina_data(dati tabella[], int righe, dati *tabella_data[], int flag_ordinamenti[]);
void ordina_codice(dati tabella[], int righe, dati *tabella_codice[], int flag_ordinamenti[]);
void ordina_partenza(dati tabella[], int righe, dati *tabella_partenza[], int flag_ordinamenti[]);
void ordina_capolinea(dati tabella[], int righe, dati *tabella_capolinea[], int flag_ordinamenti[]);

void smista_stampa(dati tabella[], int righe, int scelta_ordinamento, dati *tabella_data[], dati *tabella_codice[], dati *tabella_partenza[], dati *tabella_capolinea[]);

void apertura_menu_stampa(void);

void stampa_ordinamento(dati *tabella_stampa[], int righe, FILE *fp);
void stampa_originale(dati tabella_stampa[], int righe, FILE *fp);

int confronta_date(char data1[], char data2[], char ora_partenza1[], char ora_partenza2[], char ora_arrivo1[], char ora_arrivo2[]);

int main()
{
    int i, righe, scelta, flag_ordinamenti[r_capolinea-1];
    dati tabella[MAX];
    dati *tabella_data[MAX], *tabella_codice[MAX], *tabella_partenza[MAX], *tabella_capolinea[MAX];

    for(i=0; i<r_capolinea-1; i++)
        flag_ordinamenti[i]=0;

    righe=compila_tabella(tabella);

    do
    {
        apertura_menu();

        scelta=leggi_comando();

        smista(tabella, righe, scelta, tabella_data, tabella_codice, tabella_partenza, tabella_capolinea, flag_ordinamenti);
    }
    while(scelta!=r_fine);

    return 0;
}

int compila_tabella(dati tabella[])
{
    FILE *fp;
    int righe, i;

    fp=fopen("corse.txt", "r");
    fscanf(fp, "%d", &righe);
    for(i=0; i<righe; i++)
    {
        fscanf(fp, "%s %s %s %s %s %s %d", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione, tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, &tabella[i].ritardo);
    }
    fclose(fp);

    return righe;
}

void apertura_menu(void)
{
    printf("\ninserisci \"stampa\" per: stampare i contenuti del log\n\n");
    printf("inserisci \"data\" per: ordinare il log per data (ora in caso di parita')\n\n");
    printf("inserisci \"codice\" per: ordinare il log per codice\n\n");
    printf("inserisci \"partenza\" per: ordinare il log per stazione di partenza\n\n");
    printf("inserisci \"capolinea\" per: ordinare il log per stazione di arrivo\n\n");
    printf("inserisci \"fine\" per: chiudere il programma\n\n");
}

int leggi_comando(void)
{
    char comando[10];

    scanf("%s", comando);

    if (strcmp(comando, "stampa")==0 || strcmp(comando, "originale")==0)
        return r_stampa;

    else if (strcmp(comando, "data")==0)
        return r_data;

    else if (strcmp(comando, "codice")==0)
        return r_codice;

    else if (strcmp(comando, "partenza")==0)
        return r_partenza;

    else if (strcmp(comando, "capolinea")==0)
        return r_capolinea;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void smista(dati tabella[], int righe, int scelta, dati *tabella_data[], dati *tabella_codice[], dati *tabella_partenza[], dati *tabella_capolinea[], int flag_ordinamenti[])
{
    int scelta_ordinamento;

    switch(scelta)
    {
        case 0:
            apertura_menu_stampa();

            scelta_ordinamento=leggi_comando();

            if(scelta_ordinamento==0 || flag_ordinamenti[scelta_ordinamento-1]==1)
                smista_stampa(tabella, righe, scelta_ordinamento, tabella_data, tabella_codice, tabella_partenza, tabella_capolinea);
            else
                printf("\nordinamento non presente\n");
            break;

        case 1:
            ordina_data(tabella, righe, tabella_data, flag_ordinamenti);
            break;

        case 2:
            ordina_codice(tabella, righe, tabella_codice, flag_ordinamenti);
            break;

        case 3:
            ordina_partenza(tabella, righe, tabella_partenza, flag_ordinamenti);
            break;

        case 4:
            ordina_capolinea(tabella, righe, tabella_capolinea, flag_ordinamenti);
            break;

        case 5:
            break;

        default:
            printf("\ncomando non valido\n");
            break;
    }
}

void ordina_data(dati tabella[], int righe, dati *tabella_data[], int flag_ordinamenti[])
{
    int i, j, k, min;
    int flag_ordinato[righe];

    for(i=0; i<righe; i++)
        flag_ordinato[i]=0;

    for(i=0; i<righe; i++)
    {
        j=0;
        while(flag_ordinato[j]==1)
            j++;
        tabella_data[i]=&tabella[j];
        min=j;

        for(k=j; k<righe; k++)
        {
            if(flag_ordinato[k]==0 && confronta_date(tabella[k].data, tabella_data[i]->data, tabella[k].ora_partenza, tabella_data[i]->ora_partenza, tabella[k].ora_arrivo, tabella_data[i]->ora_arrivo)<0)
                {
                    tabella_data[i]=&tabella[k];
                    min=k;
                }
        }
        flag_ordinato[min]=1;
    }
    flag_ordinamenti[r_data-1]=1;
}

void ordina_codice(dati tabella[], int righe, dati *tabella_codice[], int flag_ordinamenti[])
{
    int i, j, k, min;
    int flag_ordinato[righe];

    for(i=0; i<righe; i++)
        flag_ordinato[i]=0;

    for(i=0; i<righe; i++)
    {
        j=0;
        while(flag_ordinato[j]==1)
            j++;
        tabella_codice[i]=&tabella[j];
        min=j;

        for(k=j; k<righe; k++)
        {
            if(flag_ordinato[k]==0 && strcmp(tabella[k].codice_tratta, tabella_codice[i]->codice_tratta)<0)
                {
                    tabella_codice[i]=&tabella[k];
                    min=k;
                }
        }
        flag_ordinato[min]=1;
    }
    flag_ordinamenti[r_codice-1]=1;
}

void ordina_partenza(dati tabella[], int righe, dati *tabella_partenza[], int flag_ordinamenti[])
{
    int i, j, k, min;
    int flag_ordinato[righe];

    for(i=0; i<righe; i++)
        flag_ordinato[i]=0;

    for(i=0; i<righe; i++)
    {
        j=0;
        while(flag_ordinato[j]==1)
            j++;
        tabella_partenza[i]=&tabella[j];
        min=j;

        for(k=j; k<righe; k++)
        {
            if(flag_ordinato[k]==0 && strcmp(tabella[k].partenza, tabella_partenza[i]->partenza)<0)
                {
                    tabella_partenza[i]=&tabella[k];
                    min=k;
                }
        }
        flag_ordinato[min]=1;
    }
    flag_ordinamenti[r_partenza-1]=1;
}

void ordina_capolinea(dati tabella[], int righe, dati *tabella_capolinea[], int flag_ordinamenti[])
{
    int i, j, k, min;
    int flag_ordinato[righe];

    for(i=0; i<righe; i++)
        flag_ordinato[i]=0;

    for(i=0; i<righe; i++)
    {
        j=0;
        while(flag_ordinato[j]==1)
            j++;
        tabella_capolinea[i]=&tabella[j];
        min=j;

        for(k=j; k<righe; k++)
        {
            if(flag_ordinato[k]==0 && strcmp(tabella[k].destinazione, tabella_capolinea[i]->destinazione)<0)
                {
                    tabella_capolinea[i]=&tabella[k];
                    min=k;
                }
        }
        flag_ordinato[min]=1;
    }
    flag_ordinamenti[r_capolinea-1]=1;
}

void smista_stampa(dati tabella[], int righe, int scelta_ordinamento, dati *tabella_data[], dati *tabella_codice[], dati *tabella_partenza[], dati *tabella_capolinea[])
{
    char output[S+1];
    FILE *fp;

    printf("\ninserire \"file\" o \"video\":\n\n");
        scanf("%s", output);

    if(strcmp(output, "video")==0)
        fp=stdout;

    else if(strcmp(output, "file")==0)
        fp=fopen("output.txt", "w");

    switch(scelta_ordinamento)
        {
            case 0:
                stampa_originale(tabella, righe, fp);
                break;

            case 1:
                stampa_ordinamento(tabella_data, righe, fp);
                break;

            case 2:
                stampa_ordinamento(tabella_codice, righe, fp);
                break;

            case 3:
                stampa_ordinamento(tabella_partenza, righe, fp);
                break;

            case 4:
                stampa_ordinamento(tabella_capolinea, righe, fp);
                break;
        }
}

void apertura_menu_stampa(void)
{
    printf("\ninserisci \"originale\" per: stampare il log originale\n\n");
    printf("inserisci \"data\" per: stampare il log oridnato per data (ora in caso di parita')\n");
    printf("inserisci \"codice\" per: stampare il log ordinato per codice\n\n");
    printf("inserisci \"partenza\" per: stampare il log ordinato per stazione di partenza\n\n");
    printf("inserisci \"capolinea\" per: stampare il log ordinato per stazione di arrivo\n\n");
}

void stampa_ordinamento(dati *tabella_stampa[], int righe, FILE *fp)
{
    int i;

        for(i=0; i<righe; i++)
            fprintf(fp, "%s %s %s %s %s %s %d\n", tabella_stampa[i]->codice_tratta, tabella_stampa[i]->partenza, tabella_stampa[i]->destinazione, tabella_stampa[i]->data, tabella_stampa[i]->ora_partenza, tabella_stampa[i]->ora_arrivo, tabella_stampa[i]->ritardo);
            fclose(fp);
}

void stampa_originale(dati tabella_stampa[], int righe, FILE *fp)
{
    int i;

    for(i=0; i<righe; i++)
        fprintf(fp, "%s %s %s %s %s %s %d\n", tabella_stampa[i].codice_tratta, tabella_stampa[i].partenza, tabella_stampa[i].destinazione, tabella_stampa[i].data, tabella_stampa[i].ora_partenza, tabella_stampa[i].ora_arrivo, tabella_stampa[i].ritardo);
}

int confronta_date(char data1[], char data2[], char ora_partenza1[], char ora_partenza2[], char ora_arrivo1[], char ora_arrivo2[])
{
    int giorno1, mese1, anno1;
    int giorno2, mese2, anno2;

    sscanf(data1, "%d/%d/%d", &giorno1, &mese1, &anno1);
    sscanf(data2, "%d/%d/%d", &giorno2, &mese2, &anno2);

    if(anno1<anno2 || (anno1==anno2 && mese1<mese2) || (anno1==anno2 && mese1==mese2 && giorno1<giorno2) || (anno1==anno2 && mese1==mese2 && giorno1==giorno2 && ora_partenza1<ora_partenza2) || (anno1==anno2 && mese1==mese2 && giorno1==giorno2 && ora_partenza1==ora_partenza2 && ora_arrivo1<ora_arrivo2))
        return -1;
    else
        return 1;
}

