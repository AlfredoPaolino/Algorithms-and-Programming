#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 30
#define MAX 1000

typedef enum {r_stampa, r_data, r_codice, r_partenza, r_capolinea, r_lettura, r_fine} indice;

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

void compila_tabella(dati **tabella, int *righe);

void apertura_menu(void);

int leggi_comando(void);

void smista(dati **tabella, int *righe, int scelta, int *flag_ordinamenti, dati ***tabella_data, dati ***tabella_codice, dati ***tabella_partenza, dati ***tabella_capolinea);

void ordina_data(dati *tabella, int righe, dati ***tabella_data);
void ordina_codice(dati *tabella, int righe, dati ***tabella_codice);
void ordina_partenza(dati *tabella, int righe, dati ***tabella_partenza);
void ordina_capolinea(dati *tabella, int righe, dati ***tabella_capolinea);

void smista_stampa(dati *tabella, int righe, int scelta_ordinamento, int *flag_ordinamenti, dati **tabella_data, dati **tabella_codice, dati **tabella_partenza, dati **tabella_capolinea);

void apertura_menu_stampa(void);

void stampa_ordinamento(dati **tabella_stampa, int righe, FILE *fp);
void stampa_originale(dati *tabella_stampa, int righe, FILE *fp);

int confronta_date(char data1[], char data2[], char ora_partenza1[], char ora_partenza2[], char ora_arrivo1[], char ora_arrivo2[]);

void free_tutto(int righe, int *flag_ordinamenti, dati **tabella_data, dati **tabella_codice, dati **tabella_partenza, dati **tabella_capolinea);

int main()
{
    int righe, scelta, flag_ordinamenti[r_capolinea], i;
    dati *tabella, **tabella_data, **tabella_codice, **tabella_partenza, **tabella_capolinea;

    for(i=0; i<r_capolinea; i++)
        flag_ordinamenti[i]=0;

    compila_tabella(&tabella, &righe);

    do
    {

        apertura_menu();

        scelta=leggi_comando();

        smista(&tabella, &righe, scelta, flag_ordinamenti, &tabella_data, &tabella_codice, &tabella_partenza, &tabella_capolinea);

    }
    while(scelta!=r_fine);

    return 0;
}

void compila_tabella(dati **tabella, int *righe)
{
    FILE *fp;
    int i;
    char nome_file[S+1];

    printf("inserire nome file:\n");
    scanf("%s", nome_file);
    fp=fopen(nome_file, "r");
    fscanf(fp, "%d", righe);

    *tabella=malloc(*righe*sizeof(dati));
    for(i=0; i<*righe; i++)
    {
        fscanf(fp, "%s %s %s %s %s %s %d", (*tabella)[i].codice_tratta, (*tabella)[i].partenza, (*tabella)[i].destinazione, (*tabella)[i].data, (*tabella)[i].ora_partenza, (*tabella)[i].ora_arrivo, &(*tabella)[i].ritardo);
    }
    fclose(fp);

}

void apertura_menu(void)
{
    printf("\ninserisci \"stampa\" per: stampare i contenuti del log\n\n");
    printf("inserisci \"data\" per: ordinare il log per data (ora in caso di parita')\n\n");
    printf("inserisci \"codice\" per: ordinare il log per codice\n\n");
    printf("inserisci \"partenza\" per: ordinare il log per stazione di partenza\n\n");
    printf("inserisci \"capolinea\" per: ordinare il log per stazione di arrivo\n\n");
    printf("inserisci \"lettura\" per: leggere un nuovo file\n\n");
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

    else if (strcmp(comando, "lettura")==0)
        return r_lettura;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void smista(dati **tabella, int *righe, int scelta, int *flag_ordinamenti, dati ***tabella_data, dati ***tabella_codice, dati ***tabella_partenza, dati ***tabella_capolinea)
{
    int scelta_ordinamento;
    switch(scelta)
    {
        case 0:
            apertura_menu_stampa();

            scelta_ordinamento=leggi_comando();
            if(scelta_ordinamento==0 || flag_ordinamenti[scelta_ordinamento-1]==1)
                smista_stampa(*tabella, *righe, scelta_ordinamento, flag_ordinamenti, *tabella_data, *tabella_codice, *tabella_partenza, *tabella_capolinea);
            else
                printf("\nordinamento non presente\n");
            break;

        case 1:
            if(flag_ordinamenti[r_data-1]==0)
            {
                ordina_data(*tabella, *righe, tabella_data);
                flag_ordinamenti[r_data-1]=1;
            }
            else
                printf("\nordinamento gia' eseguito\n");
            break;

        case 2:
            if(flag_ordinamenti[r_codice-1]==0)
            {
                ordina_codice(*tabella, *righe, tabella_codice);
                flag_ordinamenti[r_codice-1]=1;
            }
            else
                printf("\nordinamento gia' eseguito\n");
            break;

        case 3:
            if(flag_ordinamenti[r_partenza-1]==0)
            {
                ordina_partenza(*tabella, *righe, tabella_partenza);
                flag_ordinamenti[r_partenza-1]=1;
            }
            else
                printf("\nordinamento gia' eseguito\n");
            break;

        case 4:
            if(flag_ordinamenti[r_capolinea-1]==0)
            {
                ordina_capolinea(*tabella, *righe, tabella_capolinea);
                flag_ordinamenti[r_capolinea-1]=1;
            }
            else
                printf("\nordinamento gia' eseguito\n");
            break;

        case 5:
            free_tutto(*righe, flag_ordinamenti, *tabella_data, *tabella_codice, *tabella_partenza, *tabella_capolinea);
            compila_tabella(tabella, righe);
            break;

        case 6:
            break;

        default:
            printf("\ncomando non valido\n");
            break;
    }
}

void ordina_data(dati *tabella, int righe, dati ***tabella_data)
{
    int i, j;
    dati *temp;

    *tabella_data=malloc(righe*sizeof(dati*));

    for(i=0; i<righe; i++)
        (*tabella_data)[i]=&tabella[i];

    for(i=1; i<righe; i++)
    {
        j=i-1;
        temp=(*tabella_data)[i];

        while(j>=0 && confronta_date(temp->data, (*tabella_data)[j]->data, temp->ora_partenza, (*tabella_data)[j]->ora_partenza, temp->ora_arrivo, (*tabella_data)[j]->ora_arrivo)<0)
        {
            (*tabella_data)[j+1]=(*tabella_data)[j];
            j--;
        }
        (*tabella_data)[j+1]=temp;
    }
}

void ordina_codice(dati *tabella, int righe, dati ***tabella_codice)
{
    int i, j;
    dati* temp;

    *tabella_codice=malloc(righe*sizeof(dati*));

    for(i=0; i<righe; i++)
        (*tabella_codice)[i]=&tabella[i];

    for(i=1; i<righe; i++)
    {
        j=i-1;
        temp=(*tabella_codice)[i];

        while(j>=0 && strcmp(temp->codice_tratta, (*tabella_codice)[j]->codice_tratta)<0)
        {
            (*tabella_codice)[j+1]=(*tabella_codice)[j];
            j--;
        }
        (*tabella_codice)[j+1]=temp;
    }
}

void ordina_partenza(dati *tabella, int righe, dati ***tabella_partenza)
{
    int i, j;
    dati* temp;

    *tabella_partenza=malloc(righe*sizeof(dati*));

    for(i=0; i<righe; i++)
        (*tabella_partenza)[i]=&tabella[i];

    for(i=1; i<righe; i++)
    {
        j=i-1;
        temp=(*tabella_partenza)[i];

        while(j>=0 && strcmp(temp->partenza, (*tabella_partenza)[j]->partenza)<0)
        {
            (*tabella_partenza)[j+1]=(*tabella_partenza)[j];
            j--;
        }
        (*tabella_partenza)[j+1]=temp;
    }
}

void ordina_capolinea(dati *tabella, int righe, dati ***tabella_capolinea)
{
    int i, j;
    dati *temp;

    *tabella_capolinea=malloc(righe*sizeof(dati*));

    for(i=0; i<righe; i++)
        (*tabella_capolinea)[i]=&tabella[i];

    for(i=1; i<righe; i++)
    {
        j=i-1;
        temp=(*tabella_capolinea)[i];

        while(j>=0 && strcmp(temp->destinazione, (*tabella_capolinea)[j]->destinazione)<0)
        {
            (*tabella_capolinea)[j+1]=(*tabella_capolinea)[j];
            j--;
        }
        (*tabella_capolinea)[j+1]=temp;
    }
}

void smista_stampa(dati *tabella, int righe, int scelta_ordinamento, int *flag_ordinamenti, dati **tabella_data, dati **tabella_codice, dati **tabella_partenza, dati **tabella_capolinea)
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
    fclose(fp);
}

void apertura_menu_stampa(void)
{
    printf("\ninserisci \"originale\" per: stampare il log originale\n\n");
    printf("inserisci \"data\" per: stampare il log oridnato per data (ora in caso di parita')\n");
    printf("inserisci \"codice\" per: stampare il log ordinato per codice\n\n");
    printf("inserisci \"partenza\" per: stampare il log ordinato per stazione di partenza\n\n");
    printf("inserisci \"capolinea\" per: stampare il log ordinato per stazione di arrivo\n\n");
}

void stampa_originale(dati *tabella_stampa, int righe, FILE *fp)
{
    int i;

    for(i=0; i<righe; i++)
        fprintf(fp, "%s %s %s %s %s %s %d\n", tabella_stampa[i].codice_tratta, tabella_stampa[i].partenza, tabella_stampa[i].destinazione, tabella_stampa[i].data, tabella_stampa[i].ora_partenza, tabella_stampa[i].ora_arrivo, tabella_stampa[i].ritardo);
}

void stampa_ordinamento(dati **tabella_stampa, int righe, FILE *fp)
{
    int i;

    for(i=0; i<righe; i++)
        fprintf(fp, "%s %s %s %s %s %s %d\n", tabella_stampa[i]->codice_tratta, tabella_stampa[i]->partenza, tabella_stampa[i]->destinazione, tabella_stampa[i]->data, tabella_stampa[i]->ora_partenza, tabella_stampa[i]->ora_arrivo, tabella_stampa[i]->ritardo);
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

void free_tutto(int righe, int *flag_ordinamenti, dati **tabella_data, dati **tabella_codice, dati **tabella_partenza, dati **tabella_capolinea)
{
    int i;
    if(flag_ordinamenti[r_data-1]==1)
    {
        for(i=0; i<righe; i++)
            free(tabella_data[i]);
        free(tabella_data);
    }
        if(flag_ordinamenti[r_codice-1]==1)
    {
        for(i=0; i<righe; i++)
            free(tabella_codice[i]);
        free(tabella_codice);
    }
        if(flag_ordinamenti[r_partenza-1]==1)
    {
        for(i=0; i<righe; i++)
            free(tabella_partenza[i]);
        free(tabella_partenza);
    }
        if(flag_ordinamenti[r_capolinea-1]==1)
    {
        for(i=0; i<righe; i++)
            free(tabella_capolinea[i]);
        free(tabella_capolinea);
    }
}
