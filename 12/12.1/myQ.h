#ifndef MYQ_H_INCLUDED
#define MYQ_H_INCLUDED

typedef struct myQ_s *myQ;

typedef struct edge { int v; int w; int wt; int analizzato; } Edge;
myQ myQinit();
void myQinsert(myQ Qu, Edge e);
void myQfreeFromHead(myQ Qu);
Edge myQextractFromHead(myQ Qu);
void myQprint(myQ Qu);
int myQsize(myQ Qu);
Edge  EDGEcreate(int v, int w, int wt, int analizzato);

#endif // MYQ_H_INCLUDED
