#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pg.h"
#include "inventario.h"

typedef enum {r_lista, r_inv, r_aggpg, r_elpg, r_ricpg, r_aggogg, r_elogg, r_ricogg, r_stampaogg, r_stat, r_fine} indice;

void apertura_menu(void);

int leggi_comando(void);

void smista(int scelta, tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr);

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
    printf("\ninserire \"ricerca_personaggio\" per: ricercare un personaggio\n\n");
    printf("\ninserire \"aggiungi/rimuovi_oggetto\" per: aggiungere/rimuovere un oggetto\ndall'equipaggiamento di un personaggio\n\n");
    printf("\ninserire \"ricerca_oggetto\" per: ricercare un oggetto\n\n");
    printf("\ninserire \"stampa_oggetto\" per: stampare i dettagli di un oggetto\n\n");
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

    else if (strcmp(comando, "ricerca_personaggio")==0)
        return r_ricpg;

    else if (strcmp(comando, "aggiungi_oggetto")==0)
        return r_aggogg;

    else if (strcmp(comando, "rimuovi_oggetto")==0)
        return r_elogg;

    else if (strcmp(comando, "ricerca_oggetto")==0)
        return r_ricogg;

    else if (strcmp(comando, "stampa_oggetto")==0)
        return r_stampaogg;

    else if (strcmp(comando, "calcola_statistiche")==0)
        return r_stat;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void smista(int scelta, tab_pg_t *tab_pg_ptr, tab_inv_t *tab_inv_ptr)
{
    int i;
    link x;

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
            x=ricerca_pg(tab_pg_ptr);
            break;

        case 5:
            x=ricerca_pg(tab_pg_ptr);
            if(x==NULL)
                break;
            i=ricerca_oggetto(tab_inv_ptr);
            if(i==-1)
                break;
            equipaggia(tab_pg_ptr, tab_inv_ptr, x, i);
            break;

        case 6:
            x=ricerca_pg(tab_pg_ptr);
            if(x==NULL)
                break;
            i=ricerca_oggetto(tab_inv_ptr);
            if(i==-1)
                break;
            disequipaggia(tab_pg_ptr, tab_inv_ptr, x, i);
            break;

        case 7:
            i=ricerca_oggetto(tab_inv_ptr);
            break;

        case 8:
            i=ricerca_oggetto(tab_inv_ptr);
            stampa_oggetto(tab_inv_ptr, i);
            break;

        case 9:
            x=ricerca_pg(tab_pg_ptr);
            calcola_statistiche(tab_pg_ptr, x);
            break;

        case 10:

            break;

        default:
            printf("\ncomando non valido\n\n");
            break;

    }
}
