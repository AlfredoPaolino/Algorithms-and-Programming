#include <stdio.h>
#include <stdlib.h>
#include "titoli.h"

#define SOGLIA_MAX 2

void apertura_menu();
void smista(int scelta, LISTtitoli_t lista_titoli);

int main()
{
    int scelta;
    LISTtitoli_t lista_titoli;
    lista_titoli=LISTinit();
    do
    {
        apertura_menu();
        scanf("%d", &scelta);
        smista(scelta, lista_titoli);
    }
    while(scelta!=0);
    return 0;
}

void apertura_menu()
{
    printf("1 per: leggere un file\n");
    printf("2 per: ricerca di un titolo\n");
    printf("3 per: ricerca di una quotazione in una certa data\n");
    printf("4 per: ricerca di quotazione minima e massima in intervallo\n");
    printf("5 per: ricerca di quotazione minima e massima su tutto il periodo\n");
    printf("6 per: bilanciare un albero di quotazioni\n");
    printf("0 per: chiudere il programma\n");
}

void smista(int scelta, LISTtitoli_t lista_titoli)
{
    char buffer[20+1], dataDown[20+1], dataUp[20+1];
    BSTquotazioni_t x;
    data_t data;
    float quotazione, quotazioneMin=INT_MAX, quotazioneMax=0;
    int altezzaMin=INT_MAX, altezzaMax=0;
    FILE *fin;
    switch(scelta)
    {
    case 1:
        printf("\ninserire nome del file da leggere: ");
        scanf("%s", buffer);
        fin=fopen(buffer, "r");
        LISTread(fin, lista_titoli);
        LISTbstFill(lista_titoli);
        break;
    case 2:
        printf("\ninserire codice titolo da ricercare: ");
        scanf("%s", buffer);
        x=LISTsearchBSTByCode(lista_titoli, buffer);
        break;
    case 3:
        printf("\ninserire codice titolo da ricercare: ");
        scanf("%s", buffer);
        x=LISTsearchBSTByCode(lista_titoli, buffer);
        if(x==NULL)
            return;
        printf("\ninserire data della quotazione nella forma <aaaa>/<mm>/<gg>: ");
        scanf("%s", buffer);
        data=DATSstringToData(buffer);
        quotazione=BSTsearchQuotazioneByData(x, data);
        printf("%f\n", quotazione);
        break;
    case 4:
        printf("\ninserire codice titolo da ricercare: ");
        scanf("%s", buffer);
        x=LISTsearchBSTByCode(lista_titoli, buffer);
        if(x==NULL)
            return;
        printf("\ninserire data minima: ");
        scanf("%s%*c", dataDown);
        printf("\ninserire data massima: ");
        scanf("%s", dataUp);
        BSTquotazioneMinMax(x, &quotazioneMin, &quotazioneMax, DATSstringToData(dataDown), DATSstringToData(dataUp));
        printf("%f %f", quotazioneMin, quotazioneMax);
        break;
    case 5:
        printf("\ninserire codice titolo da ricercare: ");
        scanf("%s", buffer);
        x=LISTsearchBSTByCode(lista_titoli, buffer);
        if(x==NULL)
            return;
        BSTquotazioneMinMax(x, &quotazioneMin, &quotazioneMax, DATAsetNull(), DATAsetInf());
        printf("%f %f", quotazioneMin, quotazioneMax);
        break;
    case 6:
        printf("\ninserire codice titolo da ricercare: ");
        scanf("%s", buffer);
        x=LISTsearchBSTByCode(lista_titoli, buffer);
        if(x==NULL)
            return;
        BSTaltezzaMinMax(x, &altezzaMin, &altezzaMax);
        if(altezzaMax-altezzaMin>SOGLIA_MAX)
            BSTbalance(x);
        break;
    case 0:
        break;
    default:
        printf("\ncomando non valido\n\n");
        break;
    }
}
