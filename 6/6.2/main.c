#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {r_tastiera, r_file, r_ricerca, r_estrai, r_date, r_stampa, r_fine} indice;

typedef struct
{
    char codice[5+1];
    char nome[50+1];
    char cognome[50+1];
    char data_di_nascita[10+1];
    char via[50+1];
    char citta[50+1];
    int cap;
} anagrafica;

typedef struct node* link;

struct node
{
    anagrafica val;
    link next;
};

void apertura_menu(void);

int leggi_comando(void);

void smista(link *hp, int scelta);

link nuovo_nodo(anagrafica val, link next);

void inserimento_ordinato(link *hp, anagrafica lettura);

anagrafica ricerca_codice(link *hp, char *codice_utente);

anagrafica estrai_nodo(link *hp, char *codice_utente);

anagrafica estrai_intervallo(link *hp, char *data_fine);

void stampa_lista(link *hp);

anagrafica nulla(void);

int confronta_date(char *data1, char *data2);

int main()
{
    link head=NULL;
    int scelta;

    do
    {
        apertura_menu();

        scelta=leggi_comando();

        smista(&head, scelta);

    }
    while(scelta!=r_fine);

    return 0;
}

void apertura_menu(void)
{
    printf("\ninserisci \"tastiera\" per: inserire un nuovo elemento da tastiera\n\n");
    printf("\ninserisci \"file\" per: inserire nuovi elementi da file\n\n");
    printf("\ninserisci \"ricerca\" per: trovare un elemento con dato codice\n\n");
    printf("\ninserisci \"estrai\" per: estrarre un elemento previa ricerca per codice\n\n");
    printf("\ninserisci \"date\" per: estrarre elementi compresi tra due date\n\n");
    printf("\ninserisci \"stampa\" per: salvare su file\n\n");
    printf("\ninserisci \"fine\" per: chiudere il programma\n\n");
}

int leggi_comando(void)
{
    char comando[10];

    scanf("%s", comando);

    if (strcmp(comando, "tastiera")==0)
        return r_tastiera;

    else if (strcmp(comando, "file")==0)
        return r_file;

    else if (strcmp(comando, "ricerca")==0)
        return r_ricerca;

    else if (strcmp(comando, "estrai")==0)
        return r_estrai;

    else if (strcmp(comando, "date")==0)
        return r_date;

    else if (strcmp(comando, "stampa")==0)
        return r_stampa;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void smista(link *hp, int scelta)
{
    anagrafica lettura, trovata, estratto;
    char nome_file[50+1], codice_utente[50+1], data_inizio[50+1], data_fine[50+1], temp[50+1];
    FILE *fp;

    switch(scelta)
    {
        case 0:
            printf("\ninserisci nuovo elemento nella forma: <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n\n");
            scanf("%s %s %s %s %s %s %d", lettura.codice, lettura.nome, lettura.cognome, lettura.data_di_nascita, lettura.via, lettura.citta, &lettura.cap);
            inserimento_ordinato(hp, lettura);
            break;

        case 1:
            printf("\ninserisci nome file: ");
            scanf("%s", nome_file);
            fp=fopen(nome_file, "r");
            while(fscanf(fp, "%s %s %s %s %s %s %d", lettura.codice, lettura.nome, lettura.cognome, lettura.data_di_nascita, lettura.via, lettura.citta, &lettura.cap)!=EOF)
                inserimento_ordinato(hp, lettura);
            fclose(fp);
            break;

        case 2:
            if(*hp!=NULL)
            {
                printf("\ninserire codice da ricercare: ");
                scanf("%s", codice_utente);
                trovata=ricerca_codice(hp, codice_utente);
                printf("%s %s %s %s %s %s %d", trovata.codice, trovata.nome, trovata.cognome, trovata.data_di_nascita, trovata.via, trovata.citta, trovata.cap);
            }
            else
                printf("\nlista vuota\n");
            break;

        case 3:
             if(*hp!=NULL)
            {
                printf("\ninserire codice da estrarre: ");
                scanf("%s", codice_utente);
                estratto=estrai_nodo(hp, codice_utente);
                printf("\n%s %s %s %s %s %s %d\n", estratto.codice, estratto.nome, estratto.cognome, estratto.data_di_nascita, estratto.via, estratto.citta, estratto.cap);
            }
            else
                printf("\nlista vuota\n");
            break;

        case 4:
            if(*hp!=NULL)
            {
                printf("\ninserire data inizio: ");
                scanf("%s", data_inizio);
                printf("\ninserire data fine: ");
                scanf("%s", data_fine);
                if(confronta_date(data_inizio, data_fine)>0)
                {
                    strcpy(temp, data_fine);
                    strcpy(data_fine, data_inizio);
                    strcpy(data_inizio, temp);
                    printf("ordine date invertito");
                }
                for( ; *hp!=NULL && confronta_date((*hp)->val.data_di_nascita, data_fine)>0; hp=&((*hp)->next));
                while(*hp!=NULL && confronta_date((*hp)->val.data_di_nascita, data_inizio)>0)
                {
                    estratto=estrai_intervallo(hp, data_fine);
                    if(estratto.cap!=0);
                        printf("\n%s %s %s %s %s %s %d\n", estratto.codice, estratto.nome, estratto.cognome, estratto.data_di_nascita, estratto.via, estratto.citta, estratto.cap);
                }
            }
            else
                printf("\nlista vuota\n");
            break;

        case 5:
            if(*hp!=NULL)
                stampa_lista(hp);
            else
                printf("\nlista vuota\n");
            break;

        case 6:

            break;
        default:
            printf("comando non valido");
            break;
    }
}

link nuovo_nodo(anagrafica val, link next)
{
    link x=malloc(sizeof *x);
    x->val=val;
    x->next=next;
    return x;
}

void inserimento_ordinato(link *hp, anagrafica lettura)
{
    link x, t;
    if (*hp==NULL || confronta_date(lettura.data_di_nascita, (*hp)->val.data_di_nascita)>0)
        *hp=nuovo_nodo(lettura, *hp);
    else
    {
        for(x=(*hp)->next, t=*hp; x!=NULL && confronta_date(x->val.data_di_nascita, lettura.data_di_nascita)>0; t=x, x=x->next);
                t->next=nuovo_nodo(lettura, x);
    }
}

anagrafica ricerca_codice(link *hp, char *codice_utente)
{
    link x;

    for(x=*hp; x!=NULL; x=x->next)
    {
        if(strcmp(codice_utente, x->val.codice)==0)
            return x->val;
    }
    return nulla();
}

anagrafica estrai_nodo(link *hp, char *codice_utente)
{
    link t;
    anagrafica temp;

    for( ; (*hp)!=NULL; hp=&((*hp)->next))
    {
        if(strcmp(codice_utente, (*hp)->val.codice)==0)
        {
            t=*hp;
            *hp=(*hp)->next;
            temp=t->val;
            free(t);
            printf("\nelemento rimosso\n");
            return temp;
        }
    }
        printf("elemento non trovato\n");
        return nulla();
}

anagrafica estrai_intervallo(link *hp, char *data_fine)
{
    link t;
    anagrafica temp;

    t=*hp;
    *hp=(*hp)->next;
    temp=t->val;
    free(t);
    printf("\nelemento rimosso\n");
    return temp;
}

void stampa_lista(link *hp)
{
    FILE *fp;
    char nome_file[50+1];
    link x;

    printf("\ninserire nome file: ");
    scanf("%s", nome_file);
    fp=fopen(nome_file, "w");
    for(x=*hp; x!=NULL; x=x->next)
        fprintf(fp, "%s %s %s %s %s %s %d\n", x->val.codice, x->val.nome, x->val.cognome, x->val.data_di_nascita, x->val.via, x->val.citta, x->val.cap);
        fclose(fp);
}

anagrafica nulla(void)
{
    anagrafica vuota;
    strcpy(vuota.codice, "/");
    strcpy(vuota.nome, "/");
    strcpy(vuota.cognome, "/");
    strcpy(vuota.data_di_nascita, "/");
    strcpy(vuota.via, "/");
    strcpy(vuota.citta, "/");
    vuota.cap=0;
    return vuota;
}

int confronta_date(char *data1, char *data2)
{
    int giorno1, mese1, anno1;
    int giorno2, mese2, anno2;

    sscanf(data1, "%d/%d/%d", &giorno1, &mese1, &anno1);
    sscanf(data2, "%d/%d/%d", &giorno2, &mese2, &anno2);

    if(anno1>anno2 || (anno1==anno2 && mese1>mese2) || (anno1==anno2 && mese1==mese2 && giorno1>giorno2))
        return 1;
    else
        return -1;
}
