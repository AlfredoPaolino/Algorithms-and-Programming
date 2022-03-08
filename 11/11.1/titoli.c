#include "titoli.h"

typedef struct node *link1;

struct node
{
    titolo_t titolo;
    link1 next;
};

static link1 NEWnode(titolo_t titolo, link1 next);

typedef struct
{
    data_t data;
    ora_t ora;
    float valore;
    int quantita;
} info_t;

struct titolo_s
{
    char codice[20+1];
    int transazioni;
    info_t *v;
    BSTquotazioni_t BST;
};

typedef char key[20+1];

struct LISTtitoli_s
{
    link1 head;
    int numero_titoli;
};

int TITOLOnumTransazioni(titolo_t titolo)
{
    return titolo->transazioni;
}

char* TITOLOgetCodice(titolo_t titolo)
{
    return titolo->codice;
}

static link1 NEWnode(titolo_t titolo, link1 next)
{
    link1 x;
    x=malloc(sizeof *x);
    x->titolo=titolo;
    x->next=next;
    return x;
}

LISTtitoli_t LISTinit()
{
    LISTtitoli_t lista_titoli;
    lista_titoli=malloc(sizeof *lista_titoli);
    lista_titoli->numero_titoli=0;
    lista_titoli->head=NULL;
    return lista_titoli;
}

titolo_t TITOLOinit()
{
    titolo_t titolo;
    titolo=malloc(sizeof *titolo);
    titolo->BST=BSTinit();
    return titolo;
}
void LISTinsert(LISTtitoli_t lista_titoli, titolo_t titolo)
{
    link1 x, p;
    char confronto[20+1];
    strcpy(confronto, TITOLOgetCodice(titolo));
    if(lista_titoli->head==NULL || strcmp(TITOLOgetCodice(lista_titoli->head->titolo), confronto)>0)
    {
        lista_titoli->head=NEWnode(titolo, lista_titoli->head);
        return;
    }
    for(x=lista_titoli->head->next, p=lista_titoli->head; x!=NULL && strcmp(TITOLOgetCodice(x->titolo), confronto)<0; p=x, x=x->next);
        p->next=NEWnode(titolo, x);
}

titolo_t TITOLOread(FILE *fin, int *flag)
{
    int i;
    titolo_t titolo;

    titolo=TITOLOinit();
    if (fscanf(fin, "%s %d", titolo->codice, &(titolo->transazioni))!=2)
    {
        *flag=1;
        return titolo;
    }
    titolo->v=malloc(titolo->transazioni*sizeof(info_t));
    for(i=0; i<titolo->transazioni; i++)
        fscanf(fin, "%d/%d/%d %d:%d %f %d", &(titolo->v[i].data.anno), &(titolo->v[i].data.mese), &(titolo->v[i].data.giorno), &(titolo->v[i].ora.ore), &(titolo->v[i].ora.minuti), &(titolo->v[i].valore), &(titolo->v[i].quantita));
    return titolo;
}

void LISTread(FILE *fin, LISTtitoli_t lista_titoli)
{
    int flag=0;
    titolo_t titolo;
    do
    {
        titolo=TITOLOread(fin, &flag);
        if(flag==0)
            LISTinsert(lista_titoli, titolo);
    }
    while(flag==0);
}

void TITOLOprint(titolo_t titolo)
{
    int i;

    printf("\ncodice: %s", titolo->codice);
    printf("\nnumero transazioni: %d", titolo->transazioni);
    for(i=0; i<titolo->transazioni; i++)
    {
        DATAprint(titolo->v[i].data);
        ORAprint(titolo->v[i].ora);
        printf("valore: %f\t", titolo->v[i].valore);
        printf("quantita': %d\n", titolo->v[i].quantita);
    }
}
BSTquotazioni_t LISTsearchBSTByCode(LISTtitoli_t lista_titoli, char *buffer)
{
    link1 x;
    for(x=lista_titoli->head; x!=NULL; x=x->next)
    {
        if(strcmp(TITOLOgetCodice(x->titolo), buffer)==0)
        {
            printf("\ntitolo trovato\n");
            TITOLOprint(x->titolo);
            return x->titolo->BST;
        }
    }
    printf("\ntitolo non trovato\n");
    return NULL;
}

void LISTbstFill(LISTtitoli_t lista_titoli)
{
    link1 x;
    int i;
    quotazione_t y;
    for(x=lista_titoli->head; x!=NULL; x=x->next)
    {
        for(i=0; i<x->titolo->transazioni; i++)
        {
            y.data=x->titolo->v[i].data;
            y.scambiati=x->titolo->v[i].quantita;
            y.totale=x->titolo->v[i].quantita*x->titolo->v[i].valore;
            y.valore=x->titolo->v[i].valore;
            BSTfill(x->titolo->BST, y);
        }
    }
}
