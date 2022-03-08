#ifndef INVARRAY_H_INCLUDED
#define INVARRAY_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

typedef struct invArray_s *invArray_t;//

invArray_t invArray_init();//

void invArray_free(invArray_t invArray);//

void invArray_read(invArray_t invArray);//

void invArray_print(FILE *fp, invArray_t invArray);//

void invArray_printByIndex(FILE *fp, invArray_t invArray, int indice);//

int invArray_searchByName(invArray_t invArray, char *nome);//

inv_t invArray_getByIndex(invArray_t invArray, int indice);

#endif // INVARRAY_H_INCLUDED
