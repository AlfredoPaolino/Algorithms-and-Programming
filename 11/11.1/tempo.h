#ifndef TEMPO_H_INCLUDED
#define TEMPO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct
{
    int anno;
    int mese;
    int giorno;
} data_t;

typedef struct
{
    int ore;
    int minuti;
} ora_t;

int DATAcmp(data_t x, data_t y);
data_t DATSstringToData(char *buffer);
data_t DATAsetNull();
data_t DATAsetInf();
int DATAbetween(data_t myData, data_t dataDown, data_t dataUp);
void DATAprint(data_t data);
void ORAprint(ora_t ora);

#endif // TEMPO_H_INCLUDED
