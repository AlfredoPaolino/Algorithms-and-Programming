#include <stdio.h>
#include <stdlib.h>
#include "myQ.h"

typedef struct myNode* myLink;

struct myNode {Edge arco; myLink next; } ;

struct myQ_s{myLink head; int N; } ;

Edge EDGEcreate(int v, int w, int wt, int analizzato) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  e.analizzato=analizzato;
  return e;
}

static myLink myNEW(Edge e, myLink next) {
  myLink x = malloc(sizeof *x) ;
  x->arco = e; x->next = next;
  return x;
}

myQ myQinit()
{
    myQ x;
    x=malloc(sizeof *x);
    x->head=NULL;
    x->N=0;
    return x;
}
void myQinsert(myQ Qu, Edge e) {
  Qu->head=myNEW(e, Qu->head);
  Qu->N++;
}

void myQfreeFromHead(myQ Qu) {
  myLink x;
  x=Qu->head;
  Qu->head=Qu->head->next;
  free(x);
  Qu->N--;
}

Edge myQextractFromHead(myQ Qu) {
  myLink x;
  Edge e;
  x=Qu->head;
  Qu->head=Qu->head->next;
  e=x->arco;
  Qu->N--;
  free(x);
  return e;
}

void myQprint(myQ Qu)
{
    myLink t;
    for(t=Qu->head; t->next==NULL; t=t->next)
        printf("%d %d %d", t->arco.v, t->arco.w, t->arco.wt);
}

int myQsize(myQ Qu)
{
    return Qu->N;
}
