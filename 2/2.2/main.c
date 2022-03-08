#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 30
#define MAX 1000

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine} comandi;

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

void apertura_menu();

int leggi_comando();

void seleziona_dati(dati tabella[], int righe, int scelta);


int confronta_date(int riga, char data_in[], char data_out[], dati tabella[]);
void elabora_date_partenza(dati tabella[], int righe, char data_in[], char data_out[]);
void elabora_partenza(dati tabella[], int righe, char fermata_partenza[]);
void elabora_capolinea(dati tabella[], int righe, char capolinea[]);
void elabora_date_ritardo(dati tabella[], int righe, char data_in[], char data_out[]);
void elabora_ritardo_totale(dati tabella[], int righe, char codice[]);

int main()
{
    int scelta, righe;
    dati tabella[MAX];

    righe=compila_tabella(tabella);

    do
    {
        apertura_menu();

        scelta=leggi_comando();

        seleziona_dati(tabella, righe, scelta);
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

void apertura_menu()
{
    printf("inserisci \"date\" per: elencare tutte le corse partite in un certo intervallo di date\n\n");
    printf("inserisci \"partenza\" per: elencare tutti le corse partite da una certa fermata\n\n");
    printf("inserisci \"capolinea\" per: elencare tutti le corse che fanno capolinea in una certa fermata\n\n");
    printf("inserisci \"ritardo\" per: elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date\n\n");
    printf("inserisci \"ritardo_tot\" per: elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta\n\n");
    printf("inserisci \"fine\" per: chiudere il programma\n\n");
}

int leggi_comando()
{
    char comando[10];

    scanf("%s", comando);

    if (strcmp(comando, "date")==0)
        return r_date;

    else if (strcmp(comando, "partenza")==0)
        return r_partenza;

    else if (strcmp(comando, "capolinea")==0)
        return r_capolinea;

    else if (strcmp(comando, "ritardo")==0)
        return r_ritardo;

    else if (strcmp(comando, "ritardo_tot")==0)
        return r_ritardo_tot;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void seleziona_dati(dati tabella[], int righe, int scelta)
{
    char data_in[S], data_out[S], fermata_partenza[S], capolinea[S], codice[S];

    switch(scelta)
    {
        case 0:
            printf("inserire due date nel formato <gg/mm/aaaa>:\n");
            scanf("%s %s", data_in, data_out);
            elabora_date_partenza(tabella, righe, data_in, data_out);
            break;

        case 1:
            printf("inserire fermata di partenza:\n");
            scanf("%s", fermata_partenza);
            elabora_partenza(tabella, righe, fermata_partenza);
            break;

        case 2:
            printf("inserire capolinea:\n");
            scanf("%s", capolinea);
            elabora_capolinea(tabella, righe, capolinea);
            break;

        case 3:
            printf("inserire due date nel formato <gg/mm/aaaa>:\n");
            scanf("%s %s", data_in, data_out);
            elabora_date_ritardo(tabella, righe, data_in, data_out);
            break;

        case 4:
            printf("inserire codice di tratta:\n");
            scanf("%s", codice);
            elabora_ritardo_totale(tabella, righe, codice);
            break;

        case 5:
            break;

        default:
            printf("comando non valido");
            break;
    }
}

int confronta_date(int riga, char data_in[], char data_out[], dati tabella[])
{
    int flag_in, flag_out;
    int giorno_in, mese_in, anno_in;
    int giorno_out, mese_out, anno_out;
    int giorno, mese, anno;

    sscanf(data_in, "%d/%d/%d", &giorno_in, &mese_in, &anno_in);
    sscanf(data_out, "%d/%d/%d", &giorno_out, &mese_out, &anno_out);

    sscanf(tabella[riga].data, "%d/%d/%d", &giorno, &mese, &anno);
    flag_in=1;
    flag_out=1;

    if(anno<anno_in || (anno==anno_in && mese<mese_in) || (anno==anno_in && mese==mese_in && giorno<giorno_in))
        flag_in=0;
    if(anno>anno_out || (anno==anno_out && mese>mese_out) || (anno==anno_out && mese==mese_out && giorno>giorno_out))
        flag_out=0;
    if(flag_in==1 && flag_out==1)
            return 0;

    return -1;
}

void elabora_date_partenza(dati tabella[], int righe, char data_in[], char data_out[])
{
    int i, compreso;
    printf("corse in partenza tra il %s e il %s:\n\n", data_in, data_out);
    for(i=0; i<righe; i++)
    {
        compreso=confronta_date(i, data_in, data_out, tabella);
        if(compreso==0)
            printf("%s\n", tabella[i].codice_tratta);
    }
    printf("\n");
}

void elabora_partenza(dati tabella[], int righe, char fermata_partenza[])
{
    int i;

    printf("corse in partenza da %s:\n\n", fermata_partenza);
    for(i=0; i<righe; i++)
    {
        if(strcmp(fermata_partenza, tabella[i].partenza)==0)
            printf("%s\n", tabella[i].codice_tratta);
    }
    printf("\n");
}

void elabora_capolinea(dati tabella[], int righe, char capolinea[])
{
    int i;

    printf("corse con capolinea a %s:\n\n", capolinea);
    for(i=0; i<righe; i++)
    {
        if(strcmp(capolinea, tabella[i].destinazione)==0)
            printf("%s\n", tabella[i].codice_tratta);
    }
    printf("\n");
}

void elabora_date_ritardo(dati tabella[], int righe, char data_in[], char data_out[])
{
    int i, compreso;
    printf("corse in ritardo tra il %s e il %s:\n\n", data_in, data_out);
    for(i=0; i<righe; i++)
    {
        compreso=confronta_date(i, data_in, data_out, tabella);
        if(compreso==0 && tabella[i].ritardo!=0)
            printf("%s\n", tabella[i].codice_tratta);
    }
    printf("\n");
}

void elabora_ritardo_totale(dati tabella[], int righe, char codice[])
{
    int i, ritardo_totale;
    ritardo_totale=0;

    printf("la corsa %s ha accumulato un ritardo totale di:\n\n", codice);
    for(i=0; i<righe; i++)
    {
        if(strcmp(codice, tabella[i].codice_tratta)==0)
           ritardo_totale=ritardo_totale+tabella[i].ritardo;
    }
    printf("%d minuti\n\n", ritardo_totale);
}
