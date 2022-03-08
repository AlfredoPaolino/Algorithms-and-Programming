#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

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

void compila_tab_inv(tab_inv_t *tab_inv_ptr);

int ricerca_oggetto(tab_inv_t *tab_inv_ptr);

void stampa_oggetto(tab_inv_t *tab_inv_ptr, int pos);

#endif // INVENTARIO_H_INCLUDED
