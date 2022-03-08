#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symboltable {char **elaboratore; int maxN; int N; char **rete;};


ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof (*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->elaboratore = calloc(maxN, sizeof(char *));
  st->rete = calloc(maxN, sizeof(char *));
  if (st->elaboratore == NULL || st->rete == NULL) {
    printf("Memory allocation error\n");
    free(st);
    return NULL;
  }
  st->maxN = maxN;
  st->N = 0;
  return st;
}

void STfree(ST st) {
  int i;
  if (st==NULL)
    return;
  for (i=0; i<st->N; i++) {
    if (st->elaboratore[i] != NULL)
      free(st->elaboratore[i]);
    if (st->rete[i] != NULL)
      free(st->rete[i]);
  }
  free(st->elaboratore);
  free(st);
}

int STsize(ST st) {
  return st->N;
}

ST STload(FILE *fin) {
  ST st;
  char elaboratore[MAXC+1], rete[MAXC+1];
  int flusso;

  st=STinit(1);
  while(fscanf(fin, "%s %s", elaboratore, rete)!=EOF) {
    STinsert(st, elaboratore, rete);
    fscanf(fin, "%s %s", elaboratore, rete);
    STinsert(st, elaboratore, rete);
    fscanf(fin, "%d", &flusso);
  }
  return st;
}

void STprint(FILE *fout, ST st) {
  int i;

  printf("%d\n", st->N);
  for(i=0; i<st->N; i++)
    fprintf(fout, "%s %s\n", st->elaboratore[i], st->rete[i]);
}

ST STsortByName(ST st) {
  int min, i, j;
  char temp_el[MAXC+1], temp_rete[MAXC+1];

  for(i=0; i<st->N; i++) {
    min=i;
    for(j=i+1; j<st->N; j++) {
      if(strcmp(st->elaboratore[j], st->elaboratore[min])<0)
        min=j;
    }
      strcpy(temp_el, st->elaboratore[min]);
      strcpy(temp_rete, st->rete[min]);
      strcpy(st->elaboratore[min], st->elaboratore[i]);
      strcpy(st->rete[min], st->rete[i]);
      strcpy(st->elaboratore[i], temp_el);
      strcpy(st->rete[i], temp_rete);
  }
  return st;
}

void  STcopy(ST st1, ST st2) {
  int i;

  st1->maxN=st2->maxN;
  st1->N=st2->N;
  for(i=0; i<st2->N; i++) {
    st1->elaboratore[i]=malloc((MAXC+1)*sizeof(char));
    strcpy(st1->elaboratore[i], st2->elaboratore[i]);
    st1->rete[i]=malloc((MAXC+1)*sizeof(char));
    strcpy(st1->rete[i], st2->rete[i]);
  }
}

void STinsert(ST st, char *elaboratore, char *rete) {
  int i;

  i=STsearch(st, elaboratore);
  if(i>=st->N) {
    if (i >= st->maxN) {
    st->elaboratore = realloc(st->elaboratore, (2*st->maxN)*sizeof(char *));
    if (st->elaboratore == NULL)
      return ;
    st->rete = realloc(st->rete, (2*st->maxN)*sizeof(char *));
    if (st->rete == NULL)
      return ;
    st->maxN = 2*st->maxN;
  }
  st->elaboratore[i] = malloc((MAXC+1)*sizeof(char));
  st->rete[i] = malloc((MAXC+1)*sizeof(char));
  strcpy(st->elaboratore[i], elaboratore);
  strcpy(st->rete[i], rete);
  st->N++;
  }
}

int STsearch(ST st, char *elaboratore) {
  int i;

  i=0;
  while(i<st->N && strcmp(elaboratore, st->elaboratore[i])!=0)
    i++;
  return i;
}

char *STsearchByIndex(ST st, int i){
  if (i < 0 || i >= st->N)
    return NULL;
  return (st->elaboratore[i]);
}
