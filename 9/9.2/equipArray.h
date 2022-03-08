#ifndef EQUIPARRAY_H_INCLUDED
#define EQUIPARRAY_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EQUIP_SLOT 8

#include "invArray.h"

typedef struct equipArray_s *equipArray_t;//

equipArray_t equipArray_init();//

void equipArray_free(equipArray_t equipArray);//

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray);//

void equipArray_add(equipArray_t *equipArray, int indice);//

void equipArray_remove(equipArray_t *equipArray, int indice);//

void equipArray_printStat(equipArray_t equipArray, invArray_t invArray, stat_t somma);

#endif // EQUIPARRAY_H_INCLUDED
