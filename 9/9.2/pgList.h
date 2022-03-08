#ifndef PGLIST_H_INCLUDED
#define PGLIST_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pg.h"

typedef struct pgList_s *pgList_t;//

pgList_t pgList_init();//

void pgList_free(pgList_t pgList);//

void pgList_read(pgList_t pgList);//

void pgList_print(FILE *fp, pgList_t pgList);//

void pgList_insert(pgList_t pgList, pg_t lettura);//

void pgList_remove(pgList_t pgList, char* codice);//

pg_t* pgList_searchByCode(pgList_t pgList, char* codice);//

#endif // PGLIST_H_INCLUDED
