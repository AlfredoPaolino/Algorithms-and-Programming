#ifndef QUOTAZIONI_H_INCLUDED
#define QUOTAZIONI_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tempo.h"

typedef struct
{
    data_t data;
    float valore;
    int scambiati;
    int totale;
} quotazione_t;

typedef struct BSTquotazioni_s *BSTquotazioni_t;

BSTquotazioni_t BSTinit();
void BSTfill(BSTquotazioni_t bst, quotazione_t quotazione);
void BSTprint(BSTquotazioni_t bst);
float BSTsearchQuotazioneByData(BSTquotazioni_t bst, data_t data);
void BSTquotazioneMinMax(BSTquotazioni_t bst, float *quotazioneMin, float *quotazioneMax, data_t dataDown, data_t dataUp);
void BSTbalance(BSTquotazioni_t bst);
void BSTaltezzaMinMax(BSTquotazioni_t bst, int *altezzaMin, int *altezzaMax);

#endif // QUOTAZIONI_H_INCLUDED
