#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

#define MAXC 30

typedef struct symboltable *ST;

ST    STinit(int maxN);
ST    STload(FILE *fin);
void  STfree(ST st);
int   STsize(ST st);
void  STprint(FILE *fout, ST st);
ST    STsortByName(ST st);
void  STcopy(ST st1, ST st2);
void  STinsert(ST st, char *elaboratore, char *rete);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);

#endif // ST_H_INCLUDED
