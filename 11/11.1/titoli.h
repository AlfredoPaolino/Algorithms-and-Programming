#ifndef TITOLI_H_INCLUDED
#define TITOLI_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tempo.h"
#include "quotazioni.h"

typedef struct titolo_s *titolo_t;
typedef struct LISTtitoli_s *LISTtitoli_t;

int TITOLOnumTransazioni(titolo_t titolo);
char* TITOLOgetCodice(titolo_t titolo);
LISTtitoli_t LISTinit();
titolo_t TITOLOinit();
void LISTinsert(LISTtitoli_t lista_titoli, titolo_t titolo);
titolo_t TITOLOread(FILE *fin, int *flag);
void LISTread(FILE *fin, LISTtitoli_t lista_titoli);
BSTquotazioni_t LISTsearchBSTByCode(LISTtitoli_t lista_titoli, char *buffer);
void LISTbstFill(LISTtitoli_t lista_titoli);
void TITOLOprint(titolo_t titolo);

#endif // TITOLI_H_INCLUDED
