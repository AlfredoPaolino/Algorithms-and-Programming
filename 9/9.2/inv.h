#ifndef INV_H_INCLUDED
#define INV_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MIN_STAT 1

typedef struct stat_s {
  int hp, mp, atk, def, mag, spr;
} stat_t;

typedef struct inv_s {
  char nome[50+1];
  char tipo[50+1];
  stat_t stat;
} inv_t;

void stat_print(FILE *fp, stat_t stat);

stat_t stat_setVoid();

stat_t inv_getStat(inv_t equip);

stat_t stat_sumStat(stat_t somma, stat_t temp);

#endif // INV_H_INCLUDED
