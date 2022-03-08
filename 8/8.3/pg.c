#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pg.h"


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

link ricerca_pg(tab_pg_t *tab_pg_ptr)
{
    char codice_pg[50+1];
    link x;

    printf("\ninserisci codice personaggio: ");
    scanf("%s", codice_pg);
    for(x=tab_pg_ptr->head_pg; x!=NULL && strcmp(x->dati.codice, codice_pg)!=0;x=x->next);
    if(x!=NULL)
    {
        printf("\npersonaggio trovato\n");
        return x;
    }
    printf("\npersonaggio non esistente\n");
    return x;
}

void equipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr, link x, int i)
{
    x->dati.equip->equipaggiamento[x->dati.equip->numero_equipaggiato]=&(tab_inv_ptr->vettore_inventario[i]);
    x->dati.equip->numero_equipaggiato++;
    printf("\n%s aggiunto all'equipaggiamento del personaggio %s\n\n", tab_inv_ptr->vettore_inventario[i].nome, x->dati.codice);
}

void disequipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr, link x, int i)
{
    int j;

    for(j=i; j<x->dati.equip->numero_equipaggiato; j++)
        x->dati.equip->equipaggiamento[j]=x->dati.equip->equipaggiamento[j+1];
    x->dati.equip->numero_equipaggiato--;
    printf("\n%s rimosso dall'equipaggiamento del personaggio %s\n\n", tab_inv_ptr->vettore_inventario[i].nome, x->dati.codice);
}

void calcola_statistiche(tab_pg_t *tab_pg_ptr, link x)
{
    int i;
    stat_t statische_bonus_malus;

    printf("\nstatistiche del personaggio %s:\n", x->dati.codice);
    printf("\nbase:\n");
    stampa_statistiche(x->dati.statistiche);
    if(x->dati.equip->numero_equipaggiato==0)
    {
        printf("\nnessun oggetto equipaggiato\n\n");
        return;
    }
    statische_bonus_malus=x->dati.statistiche;
    for(i=0; i<x->dati.equip->numero_equipaggiato; i++)
        somma_statistiche(x->dati.equip->equipaggiamento[i], &statische_bonus_malus, i);
    printf("\nattuali:\n");
    stampa_statistiche(statische_bonus_malus);
    printf("\noggetti equipaggiati:\n");
    for(i=0; i<x->dati.equip->numero_equipaggiato; i++)
        printf("\n%s %s %d %d %d %d %d %d", x->dati.equip->equipaggiamento[i]->nome, x->dati.equip->equipaggiamento[i]->tipo, x->dati.equip->equipaggiamento[i]->statistiche.hp, x->dati.equip->equipaggiamento[i]->statistiche.mp, x->dati.equip->equipaggiamento[i]->statistiche.atk, x->dati.equip->equipaggiamento[i]->statistiche.def, x->dati.equip->equipaggiamento[i]->statistiche.mag, x->dati.equip->equipaggiamento[i]->statistiche.spr);
    printf("\n");
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
    printf("\nhp: %d", stampa.hp);
    printf("\nmp: %d", stampa.mp);
    printf("\natk: %d", stampa.atk);
    printf("\ndef: %d", stampa.def);
    printf("\nmag: %d", stampa.mag);
    printf("\nspr: %d\n", stampa.spr);
}
