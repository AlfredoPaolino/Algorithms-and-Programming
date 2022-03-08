#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EQ 8

typedef enum {r_lista, r_inv, r_aggpg, r_elpg, r_aggogg, r_elogg, r_stat, r_fine} indice;

typedef struct nodo_pg* link;

typedef struct
{
    link head_pg;
    link tail_pg;
    int numero_pg;
}tab_pg_t;

typedef struct
{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct
{
    char nome[50+1];
    char tipo[50+1];
    stat_t statistiche;
} inv_t;

typedef struct
{
    inv_t *vettore_inventario;
    int numero_inventario;
    int massimo_inventario;
} tab_inv_t;

typedef struct
{
    int numero_equipaggiato;
    inv_t *equipaggiamento[MAX_EQ];
} tab_equip_t;

typedef struct
{
    char codice[6+1];
    char nome[50+1];
    char classe[50+1];
    tab_equip_t *equip;
    stat_t statistiche;
} pg_t;

struct nodo_pg
{
    pg_t dati;
    link next;
};


void apertura_menu(void);

int leggi_comando(void);

void smista(int scelta, tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr);

link nuovo_nodo(pg_t dati, link next);

void compila_tab_pg(tab_pg_t *tab_pg_ptr);

void inserimento_coda(link *hp, link *tp, pg_t dati);

void compila_tab_inv(tab_inv_t *tab_inv_ptr);

void aggiungi_pg(tab_pg_t *tab_pg_ptr);

void elimina_pg(tab_pg_t *tab_pg_ptr);

void equipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr);

void disequipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr);

void calcola_statistiche(tab_pg_t *tab_pg_ptr);

void somma_statistiche(inv_t *equip_ptr, stat_t *statistiche_bonus_malus_ptr, int indice);

void stampa_statistiche(stat_t stampa);

int main()
{
    tab_pg_t tab_pg;
    tab_inv_t tab_inv;
    int scelta;
    char menu[10+1];

    tab_pg.head_pg=NULL;
    tab_pg.tail_pg=NULL;
    tab_pg.numero_pg=0;

    do
    {
        printf("\ninserire \"menu\" per: aprire il menu\n\n");
        printf("\ninserire \"fine\" per: terminare il programma\n\n");
        scanf("%s", menu);
        if(strcmp(menu, "menu")==0)
            apertura_menu();
        else if(strcmp(menu, "fine")==0)
            return 0;

        scelta=leggi_comando();

        smista(scelta, &tab_pg, &tab_inv);

    }
    while(scelta!=r_fine);

    return 0;
}
void apertura_menu(void)
{
    printf("\ninserire \"lista_personaggi\" per: caricare una lista di personaggi\n\n");
    printf("\ninserire \"inventario\" per: caricare l'inventario\n\n");
    printf("\ninserire \"aggiungi/elimina_personaggio\" per: aggiungere/rimuovere manualmente un\nnuovo personaggio\n\n");
    printf("\ninserire \"aggiungi/rimuovi_oggetto\" per: aggiungere/rimuovere un oggetto\ndall'equipaggiamento di un personaggio\n\n");
    printf("\ninserire \"calcola_statistiche\" per: calcolare le statistiche di un personaggio\n\n");
    printf("\ninserire \"fine\" per: terminare il programma\n\n");
}

int leggi_comando(void)
{
    char comando[50+1];

    scanf("%s", comando);

    if (strcmp(comando, "lista_personaggi")==0)
        return r_lista;

    else if (strcmp(comando, "inventario")==0)
        return r_inv;

    else if (strcmp(comando, "aggiungi_personaggio")==0)
        return r_aggpg;

    else if (strcmp(comando, "elimina_personaggio")==0)
        return r_elpg;

    else if (strcmp(comando, "aggiungi_oggetto")==0)
        return r_aggogg;

    else if (strcmp(comando, "rimuovi_oggetto")==0)
        return r_elogg;

    else if (strcmp(comando, "calcola_statistiche")==0)
        return r_stat;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void smista(int scelta, tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr)
{

    switch(scelta)
    {
        case 0:
            compila_tab_pg(tab_pg_ptr);
            break;

        case 1:
            compila_tab_inv(tab_inv_ptr);
            break;

        case 2:
            aggiungi_pg(tab_pg_ptr);
            break;

        case 3:
            elimina_pg(tab_pg_ptr);
            break;

        case 4:
            equipaggia(tab_pg_ptr, tab_inv_ptr);
            break;

        case 5:
            disequipaggia(tab_pg_ptr, tab_inv_ptr);
            break;

        case 6:
            calcola_statistiche(tab_pg_ptr);
            break;

        case 7:

            break;

        default:
            printf("\ncomando non valido\n\n");
            break;

    }
}

link nuovo_nodo(pg_t dati, link next)
{
    int i;
    link x=malloc(sizeof *x);
    tab_equip_t *equip_pg=malloc(sizeof *equip_pg);

    equip_pg->numero_equipaggiato=0;
    for(i=0; i<MAX_EQ; i++)
        equip_pg->equipaggiamento[i]=NULL;

    x->dati=dati;
    x->dati.equip=equip_pg;
    x->next=next;
    return x;
}

void compila_tab_pg( tab_pg_t *tab_pg_ptr)
{
    FILE *fp;
    pg_t lettura;

    fp=fopen("pg.txt", "r");
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d", lettura.codice, lettura.nome, lettura.classe, &lettura.statistiche.hp, &lettura.statistiche.mp, &lettura.statistiche.atk, &lettura.statistiche.def, &lettura.statistiche.mag, &lettura.statistiche.spr)!=EOF)
    {
        inserimento_coda(&(tab_pg_ptr->head_pg), &(tab_pg_ptr->tail_pg), lettura);
        tab_pg_ptr->numero_pg++;
    }
    fclose(fp);

}

void inserimento_coda(link *hp, link *tp, pg_t dati)
{
    if(*hp==NULL)
        *hp=*tp=nuovo_nodo(dati, NULL);

    else
    {
        (*tp)->next=nuovo_nodo(dati, NULL);
        (*tp)=(*tp)->next;
    }
}

void compila_tab_inv( tab_inv_t *tab_inv_ptr)
{
    FILE *fp;
    int i;

    fp=fopen("inventario.txt", "r");
    fscanf(fp, "%d", &(tab_inv_ptr->numero_inventario));
    tab_inv_ptr->vettore_inventario=malloc(tab_inv_ptr->numero_inventario*sizeof(inv_t));

    for(i=0; i<tab_inv_ptr->numero_inventario; i++)
        fscanf(fp, "%s %s %d %d %d %d %d %d", tab_inv_ptr->vettore_inventario[i].nome, tab_inv_ptr->vettore_inventario[i].tipo, &tab_inv_ptr->vettore_inventario[i].statistiche.hp, &tab_inv_ptr->vettore_inventario[i].statistiche.mp, &tab_inv_ptr->vettore_inventario[i].statistiche.atk, &tab_inv_ptr->vettore_inventario[i].statistiche.def, &tab_inv_ptr->vettore_inventario[i].statistiche.mag, &tab_inv_ptr->vettore_inventario[i].statistiche.spr);

    fclose(fp);
}

void aggiungi_pg(tab_pg_t *tab_pg_ptr)
{
    pg_t lettura;

    printf("\ninserire un nuovo personaggio nella forma:\n<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>\n\n");
    scanf("%s %s %s %d %d %d %d %d %d", lettura.codice, lettura.nome, lettura.classe, &lettura.statistiche.hp, &lettura.statistiche.mp, &lettura.statistiche.atk, &lettura.statistiche.def, &lettura.statistiche.mag, &lettura.statistiche.spr);
    inserimento_coda(&(tab_pg_ptr->head_pg), &(tab_pg_ptr->tail_pg), lettura);
    tab_pg_ptr->numero_pg++;
}

void elimina_pg(tab_pg_t *tab_pg_ptr)
{
    char eliminare[50+1];
    link x, p;
    printf("\ninserire il codice del personaggio da eliminare: ");
    scanf("%s", eliminare);

    for(x=tab_pg_ptr->head_pg; x!=NULL; p=x, x=x->next)
    {
        if(strcmp(eliminare, x->dati.codice)==0)
        {
            if(x==tab_pg_ptr->head_pg)
                tab_pg_ptr->head_pg=x->next;
            else
                p->next=x->next;
            free(x->dati.equip);
            free(x);
            printf("\n%s eliminato dalla lista dei personaggi\n\n", eliminare);
            return;
        }
    }
    printf("\npersonaggio non presente\n\n");
}

void equipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr)
{
    int i;
    link x;
    char codice_pg[50+1];
    char equipaggiamento[50+1];

    printf("\ninserisci codice personaggio: ");
    scanf("%s", codice_pg);
    for(x=tab_pg_ptr->head_pg; x!=NULL && strcmp(x->dati.codice, codice_pg)!=0;x=x->next);
    if(x==NULL)
    {
        printf("\npersonaggio non esistente\n\n");
        return;
    }

    printf("\ninserisci equipaggiamento: ");
    scanf("%s", equipaggiamento);
    for(i=0; i<tab_inv_ptr->numero_inventario && strcmp(tab_inv_ptr->vettore_inventario[i].nome, equipaggiamento)!=0; i++);
    if(i==tab_inv_ptr->numero_inventario)
    {
        printf("\nequipaggiamento non esistente");
        return;
    }
    x->dati.equip->equipaggiamento[x->dati.equip->numero_equipaggiato]=&(tab_inv_ptr->vettore_inventario[i]);
    x->dati.equip->numero_equipaggiato++;
    printf("\n%s aggiunto all'equipaggiamento del personaggio %s\n\n", equipaggiamento, x->dati.codice);
}

void disequipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr)
{
    int i, j;
    link x;
    char codice_pg[50+1];
    char equipaggiamento[50+1];

    printf("\ninserisci codice personaggio: ");
    scanf("%s", codice_pg);
    for(x=tab_pg_ptr->head_pg; x!=NULL && strcmp(x->dati.codice, codice_pg)!=0;x=x->next);
    if(x==NULL)
    {
        printf("\npersonaggio non esistente\n\n");
        return;
    }

    printf("\ninserisci equipaggiamento: ");
    scanf("%s", equipaggiamento);
    for(i=0; i<x->dati.equip->numero_equipaggiato && strcmp(x->dati.equip->equipaggiamento[i]->nome, equipaggiamento)!=0; i++);
    if(i==x->dati.equip->numero_equipaggiato)
    {
        printf("\n%s non e' presente nell'inventario del personaggio %s\n\n", equipaggiamento, x->dati.codice);
        return;
    }

    for(j=i; j<x->dati.equip->numero_equipaggiato; j++)
        x->dati.equip->equipaggiamento[j]=x->dati.equip->equipaggiamento[j+1];
    x->dati.equip->numero_equipaggiato--;
    printf("\n%s rimosso dall'equipaggiamento del personaggio %s\n\n", equipaggiamento, x->dati.codice);
}

void calcola_statistiche(tab_pg_t *tab_pg_ptr)
{
    int i;
    link x;
    char codice_pg[50+1];
    stat_t statische_bonus_malus;

    printf("\ninserisci codice personaggio: ");
    scanf("%s", codice_pg);
    for(x=tab_pg_ptr->head_pg; x!=NULL && strcmp(x->dati.codice, codice_pg)!=0;x=x->next);
    if(x==NULL)
    {
        printf("\npersonaggio non esistente\n\n");
        return;
    }

    statische_bonus_malus=x->dati.statistiche;
    for(i=0; i<x->dati.equip->numero_equipaggiato; i++)
        somma_statistiche(x->dati.equip->equipaggiamento[i], &statische_bonus_malus, i);

    printf("\nstatistiche del personaggio %s:\n\n", x->dati.codice);
    stampa_statistiche(statische_bonus_malus);

}

void somma_statistiche(inv_t *equip_ptr, stat_t *statistiche_bonus_malus_ptr, int indice)
{
    if((statistiche_bonus_malus_ptr->hp+=equip_ptr->statistiche.hp)<1)
        statistiche_bonus_malus_ptr->hp=1;
    if((statistiche_bonus_malus_ptr->mp+=equip_ptr->statistiche.mp)<1)
        statistiche_bonus_malus_ptr->mp=1;
    if((statistiche_bonus_malus_ptr->atk+=equip_ptr->statistiche.atk)<1)
        statistiche_bonus_malus_ptr->atk=1;
    if((statistiche_bonus_malus_ptr->def+=equip_ptr->statistiche.def)<1)
        statistiche_bonus_malus_ptr->def=1;
    if((statistiche_bonus_malus_ptr->mag+=equip_ptr->statistiche.mag)<1)
        statistiche_bonus_malus_ptr->mag=1;
    if((statistiche_bonus_malus_ptr->spr+=equip_ptr->statistiche.spr)<1)
        statistiche_bonus_malus_ptr->spr=1;

}

void stampa_statistiche(stat_t stampa)
{
    printf("\nhp: %d\n\n", stampa.hp);
    printf("\nmp: %d\n\n", stampa.mp);
    printf("\natk: %d\n\n", stampa.atk);
    printf("\ndef: %d\n\n", stampa.def);
    printf("\nmag: %d\n\n", stampa.mag);
    printf("\nspr: %d\n\n", stampa.spr);
}
