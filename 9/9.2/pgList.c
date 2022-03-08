#include "pgList.h"

typedef struct node *link;

struct node
{
    pg_t pg;
    link next;
};

link new_node(pg_t lettura, link next);

struct pgList_s
{
    link head;
    link tail;
    int numero_pg;
};

pgList_t pgList_init()
{
    pgList_t temp;

    temp=malloc(sizeof *temp);
    temp->head=NULL;
    temp->tail=NULL;
    temp->numero_pg=0;
    return temp;
}

void pgList_read(pgList_t pgList)
{
    FILE *fp;
    pg_t lettura;

    fp=fopen("pg.txt", "r");
    while (pg_read(fp, &lettura)==0)
    {
        pgList_insert(pgList, lettura);
        pgList->numero_pg++;
    }
    fclose(fp);
}

link new_node(pg_t lettura, link next)
{
    link x=(link)malloc(sizeof *x);

    x->pg=lettura;
    x->pg.equip=equipArray_init();
    x->next=next;
    return x;
}
void pgList_insert(pgList_t pgList, pg_t lettura)
{
    if(pgList->head==NULL)
        pgList->head=pgList->tail=new_node(lettura, NULL);

    else
    {
        pgList->tail->next=new_node(lettura, NULL);
        pgList->tail=pgList->tail->next;
    }
}

void pgList_print(FILE *fp, pgList_t pgList)
{
    link x;

    for(x=pgList->head; x!=NULL; x=x->next)
        pg_print(stdout, &(x->pg));
}

void pgList_remove(pgList_t pgList, char* codice)
{
    link x, p=NULL;

    for(x=pgList->head; x!=NULL && strcmp(x->pg.codice, codice)!=0; p=x, x=x->next);
    if(x==NULL)
        printf("\npersonaggio non presente\n\n");
    else if(p==NULL)
    {
        p=x;
        pgList->head=x->next;
        pg_clean(&(p->pg));
        free(p);
    }
    else
    {
        p->next=x->next;
        free(x);
    }

}

pg_t* pgList_searchByCode(pgList_t pgList, char* codice)
{
    link x;

    for(x=pgList->head; x!=NULL && strcmp(x->pg.codice, codice)!=0; x=x->next);
    if(x!=NULL)
        return &(x->pg);
    else
    {
        printf("\npersonaggio non presente\n\n");
        return NULL;
    }
}

void pgList_free(pgList_t pgList)
{
    link x, p;
    for(x=pgList->head; x!=NULL; x=x->next)
    {
        p=x;
        pgList->head=x->next;
        free(p);
    }
}
