#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"

#define MAX_EQ 8

typedef struct
{
    char codice[6+1];
    char nome[50+1];
    char classe[50+1];
    equipArray_t equip;
    stat_t stat_b;
} pg_t;

int pg_read(FILE *fp, pg_t *pg_ptr);//

void pg_clean(pg_t *pg_ptr);//

void pg_print(FILE *fp, pg_t *pg_ptr);//

void pg_addEquip(pg_t *pg_ptr, int indice);//

void pg_removeEquip(pg_t *pg_ptr, int indice);//

void pg_printStat(pg_t *pg_ptr, invArray_t invArray);

#endif // PG_H_INCLUDED
