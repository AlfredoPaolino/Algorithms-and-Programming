#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED

#include "inventario.h"

#define MAX_EQ 8

typedef struct nodo_pg* link;

typedef struct
{
    link head_pg;
    link tail_pg;
    int numero_pg;
}tab_pg_t;

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

link nuovo_nodo(pg_t dati, link next);

void compila_tab_pg(tab_pg_t *tab_pg_ptr);

void inserimento_coda(link *hp, link *tp, pg_t dati);

void aggiungi_pg(tab_pg_t *tab_pg_ptr);

void elimina_pg(tab_pg_t *tab_pg_ptr);

link ricerca_pg(tab_pg_t *tab_pg_ptr);

void equipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr, link x, int i);

void disequipaggia(tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr, link x, int i);

void calcola_statistiche(tab_pg_t *tab_pg_ptr, link x);

void somma_statistiche(inv_t *equip_ptr, stat_t *statistiche_bonus_malus_ptr, int indice);

void stampa_statistiche(stat_t stampa);

#endif // PG_H_INCLUDED
