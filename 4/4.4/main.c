#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 30
#define MAX 1000

typedef enum {r_stampa, r_data, r_codice, r_partenza, r_capolinea, r_ricerca, r_fine} indice;

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

int leggi_comando(void );

void smista(dati tabella[], int righe, int scelta, int *p_flag);

void ordina_data(dati tabella[], int righe, int *p_flag);
void ordina_codice(dati tabella[], int righe, int *p_flag);
void ordina_partenza(dati tabella[], int righe, int *p_flag);
void ordina_capolinea(dati tabella[], int righe, int *p_flag);

void ricerca(dati tabella[], int righe, int *p_flag);

void stampa(char output[], dati tabella[], int righe);

int confronta_date(char data1[], char data2[], char ora_partenza1[], char ora_partenza2[], char ora_arrivo1[], char ora_arrivo2[]);

void tabcpy(dati tab1[], dati tab2[], int riga1, int riga2);

int main()
{
    int righe, scelta;
    int flag_date=0;
    int *p_flag=&flag_date;
    dati tabella[MAX];

    righe=compila_tabella(tabella);

    do
    {
        apertura_menu();

        scelta=leggi_comando();

        smista(tabella, righe, scelta, p_flag);
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
    printf("inserisci \"ricerca\" per: ricercare una tratta da stazione di partenza\n(anche parziale)\n\n");
    printf("inserisci \"fine\" per: chiudere il programma\n\n");
}

int leggi_comando(void)
{
    char comando[10];

    scanf("%s", comando);

    if (strcmp(comando, "stampa")==0)
        return r_stampa;

    else if (strcmp(comando, "data")==0)
        return r_data;

    else if (strcmp(comando, "codice")==0)
        return r_codice;

    else if (strcmp(comando, "partenza")==0)
        return r_partenza;

    else if (strcmp(comando, "capolinea")==0)
        return r_capolinea;

    else if (strcmp(comando, "ricerca")==0)
        return r_ricerca;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void smista(dati tabella[], int righe, int scelta, int *p_flag)
{
    char output[S+1];

    switch(scelta)
    {
        case 0:
            printf("\ninserire \"file\" o \"video\":\n\n");
            scanf("%s", output);
            stampa(output, tabella, righe);
            break;

        case 1:
            ordina_data(tabella, righe, p_flag);
            break;

        case 2:
            ordina_codice(tabella, righe, p_flag);
            break;

        case 3:
            ordina_partenza(tabella, righe, p_flag);
            break;

        case 4:
            ordina_capolinea(tabella, righe, p_flag);
            break;

        case 5:
            ricerca(tabella, righe, p_flag);
            break;

        case 6:
            break;

        default:
            printf("comando non valido");
            break;
    }
}

void ordina_data(dati tabella[], int righe, int *p_flag)
{
    int i, j;
    dati temp;

    for(i=1; i<righe; i++)
    {
        temp=tabella[i];

        for(j=i-1; j>=0 && (confronta_date(temp.data, tabella[j].data, temp.ora_partenza, tabella[j].ora_partenza, temp.ora_arrivo, tabella[j].ora_arrivo)<0); j--)
            tabella[j+1]=tabella[j];

        if(tabella[j+1].data!=temp.data)
            tabella[j+1]=temp;
    }
    *p_flag=0;
}

void ordina_codice(dati tabella[], int righe, int *p_flag)
{
    int i, j;
    dati temp;

    for(i=1; i<righe; i++)
    {
        temp=tabella[i];

        for(j=i-1; j>=0 && (strcmp(temp.codice_tratta, tabella[j].codice_tratta)<0); j--)
            tabella[j+1]=tabella[j];

        if(tabella[j+1].codice_tratta!=temp.codice_tratta)
            tabella[j+1]=temp;
    }
    *p_flag=0;
}

void ordina_partenza(dati tabella[], int righe, int *p_flag)
{
    int i, j;
    dati temp;

    for(i=1; i<righe; i++)
    {
        temp=tabella[i];

        for(j=i-1; j>=0 && (strcmp(temp.partenza, tabella[j].partenza)<0); j--)
            tabella[j+1]=tabella[j];

        if(tabella[j+1].partenza!=temp.partenza)
            tabella[j+1]=temp;
    }
    *p_flag=1;
}

void ordina_capolinea(dati tabella[], int righe, int *p_flag)
{
    int i, j;
    dati temp;

    for(i=1; i<righe; i++)
    {
        temp=tabella[i];

        for(j=i-1; j>=0 && (strcmp(temp.destinazione, tabella[j].destinazione)<0); j--)
            tabella[j+1]=tabella[j];

        if(tabella[j+1].destinazione!=temp.destinazione)
            tabella[j+1]=temp;
    }
    *p_flag=0;
}

void ricerca(dati tabella[], int righe, int *p_flag)
{
    int i, j, l, r, trovato;
    char stazione[S+1];

    printf("\ninserire stazione di partenza (anche parziale):\n\n");
    scanf("%s", stazione);
    printf("\ntratte disponibili:\n\n");
    if(*p_flag==1)
    {
        l=0;
        r=righe;
        trovato=0;

        while(!trovato && l<=r)
        {
            i=(r-l)/2;

            if(strncmp(tabella[i].partenza, stazione, strlen(stazione))<0)
                r=i-1;

            else if(strncmp(tabella[i].partenza, stazione, strlen(stazione))>0)
                l=i+1;

            else if(strncmp(tabella[i].partenza, stazione, strlen(stazione))==0)
                trovato=1;
        }
        if(trovato==1)
            printf("%s %s\n", tabella[i].partenza, tabella[i].destinazione);

        j=i-1;
        while(strncmp(tabella[j].partenza, stazione, strlen(stazione))==0)
        {
            printf("%s %s\n", tabella[j].partenza, tabella[j].destinazione);
            j--;
        }

        j=i+1;
        while(strncmp(tabella[j].partenza, stazione, strlen(stazione))==0)
        {
            printf("%s %s\n", tabella[j].partenza, tabella[j].destinazione);
            j++;
        }
    }

    else if(*p_flag==0)
    {
        for(i=0; i<righe; i++)
        {
            if(strncmp(tabella[i].partenza, stazione, strlen(stazione))==0)
                printf("%s %s\n", tabella[i].partenza, tabella[i].destinazione);
        }
    }
}

void stampa(char output[], dati tabella[], int righe)
{
    int i;
    FILE *fp;

    if(strcmp(output, "video")==0)
    {
        for(i=0; i<righe; i++)
            printf("%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione, tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
    }

    else if(strcmp(output, "file")==0)
    {
        fp=fopen("output.txt", "w");
        for(i=0; i<righe; i++)
            fprintf(fp, "%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione, tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
        fclose(fp);
    }
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
