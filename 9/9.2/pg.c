#include "pg.h"

int pg_read(FILE *fp, pg_t *pg_ptr)
{
    if(fscanf(fp, "%s %s %s %d %d %d %d %d %d", pg_ptr->codice, pg_ptr->nome, pg_ptr->classe, &(pg_ptr->stat_b.hp), &(pg_ptr->stat_b.mp), &(pg_ptr->stat_b.atk), &(pg_ptr->stat_b.def), &(pg_ptr->stat_b.mag), &(pg_ptr->stat_b.spr))==9)
        return 0;
    return 1;
}

void pg_print(FILE *fp, pg_t *pg_ptr)
{
    fprintf(fp, "%s %s %s %d %d %d %d %d %d\n", pg_ptr->codice, pg_ptr->nome, pg_ptr->classe, pg_ptr->stat_b.hp, pg_ptr->stat_b.mp, pg_ptr->stat_b.atk, pg_ptr->stat_b.def, pg_ptr->stat_b.mag, pg_ptr->stat_b.spr);
}

void pg_addEquip(pg_t *pg_ptr, int indice)
{
    equipArray_add(&(pg_ptr->equip), indice);

}

void pg_removeEquip(pg_t *pg_ptr, int indice)
{
    equipArray_remove(&(pg_ptr->equip), indice);
}

void pg_clean(pg_t *pg_ptr)
{
    equipArray_free(pg_ptr->equip);
}

void pg_printStat(pg_t *pg_ptr, invArray_t invArray)
{
    stat_t somma=pg_ptr->stat_b;

    equipArray_printStat(pg_ptr->equip, invArray, somma);
}
