#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventario.h"

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

int ricerca_oggetto(tab_inv_t *tab_inv_ptr)
{
    int i;
    char nome_oggetto[50+1];

    printf("\ninserisci il nome dell'oggetto da ricercare: ");
    scanf("%s", nome_oggetto);

    for(i=0; i<tab_inv_ptr->numero_inventario; i++)
    {
        if(strcmp(tab_inv_ptr->vettore_inventario[i].nome, nome_oggetto)==0)
            {
                printf("\noggetto trovato\n");
                return i;
            }
    }
    printf("\noggetto non presente\n");
    return -1;
}

void stampa_oggetto(tab_inv_t *tab_inv_ptr, int pos)
{
    printf("\n%s %s %d %d %d %d %d %d\n", tab_inv_ptr->vettore_inventario[pos].nome, tab_inv_ptr->vettore_inventario[pos].tipo, tab_inv_ptr->vettore_inventario[pos].statistiche.hp, tab_inv_ptr->vettore_inventario[pos].statistiche.mp, tab_inv_ptr->vettore_inventario[pos].statistiche.atk, tab_inv_ptr->vettore_inventario[pos].statistiche.def, tab_inv_ptr->vettore_inventario[pos].statistiche.mag, tab_inv_ptr->vettore_inventario[pos].statistiche.spr);
}
