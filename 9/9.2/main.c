#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgList.h"
#include "invArray.h"
#include "pg.h"

typedef enum {r_lista, r_inv, r_aggpg, r_elpg, r_ricpg, r_aggogg, r_elogg, r_ricogg, r_stat, r_fine} indice;

void apertura_menu(void);

int leggi_comando(void);

void smista(int scelta, pgList_t pgList, invArray_t invArray);

int main()
{

    int scelta;
    char menu[10+1];
    pgList_t pgList=pgList_init();
    invArray_t invArray=invArray_init();
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

        smista(scelta, pgList, invArray);

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

    else if (strcmp(comando, "calcola_statistiche")==0)
        return r_stat;

    else if (strcmp(comando, "fine")==0)
        return r_fine;

    else
        return -1;
}

void smista(int scelta, pgList_t pgList, invArray_t invArray)
{
    int indice;
    pg_t lettura, *ricerca_pg;
    char codice[50+1], nome[50+1];

    switch(scelta)
    {
        case 0:
            pgList_read(pgList);
            printf("\nlista personaggi:\n");
            pgList_print(stdout, pgList);
            break;

        case 1:
            invArray_read(invArray);
            invArray_print(stdout, invArray);
            break;

        case 2:
            printf("inserire personaggio nella forma:\n<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>\n");
            pg_read(stdin, &lettura);
            pgList_insert(pgList, lettura);
            getc(stdin);
            printf("\nlista personaggi:\n");
            pgList_print(stdout, pgList);
            break;

        case 3:
            printf("\ninserire codice del personaggio da eliminare:\n");
            scanf("%s", codice);
            pgList_remove(pgList, codice);
            printf("\nlista personaggi:\n");
            pgList_print(stdout, pgList);
            break;

        case 4:
            printf("\ninserire codice del personaggio da ricercare:\n");
            scanf("%s", codice);
            ricerca_pg=pgList_searchByCode(pgList, codice);
            if(ricerca_pg!=NULL)
            {
                pg_print(stdout, ricerca_pg);
                printf("equipaggiamento:\n");
                equipArray_print(stdout, ricerca_pg->equip, invArray);
            }
            break;

        case 5:
            printf("\ninserire codice del personaggio a cui aggiungere l'oggetto:\n");
            scanf("%s", codice);
            ricerca_pg=pgList_searchByCode(pgList, codice);
            if(ricerca_pg!=NULL)
            {
                printf("\ninserire nome dell'oggetto da equipaggiare:\n");
                scanf("%s", codice);
                indice=invArray_searchByName(invArray, codice);
                if(indice!=-1)
                    pg_addEquip(ricerca_pg, indice);
            }
            break;

        case 6:
            printf("\ninserire codice del personaggio a cui eliminare l'oggetto:\n");
            scanf("%s", codice);
            ricerca_pg=pgList_searchByCode(pgList, codice);
            if(ricerca_pg!=NULL)
            {
                printf("\ninserire nome dell'oggetto da disequipaggiare:\n");
                scanf("%s", codice);
                indice=invArray_searchByName(invArray, codice);
                if(indice!=-1)
                    pg_removeEquip(ricerca_pg, indice);
            }
            break;

        case 7:
            printf("\ninserire il nome dell'oggetto da ricercare:\n");
            scanf("%s", nome);
            indice=invArray_searchByName(invArray, nome);
            invArray_printByIndex(stdout, invArray, indice);
            break;

        case 8:
            printf("\ninserire codice del personaggio di cui stampare le statistiche:\n");
            scanf("%s", codice);
            ricerca_pg=pgList_searchByCode(pgList, codice);
            if(ricerca_pg!=NULL)
            {
                pg_printStat(ricerca_pg, invArray);
            }
            break;

        case 9:

            break;

        default:
            printf("\ncomando non valido\n\n");
            break;

    }
}
