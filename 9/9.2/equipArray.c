#include "equipArray.h"

struct equipArray_s
{
    int numero_equip;
    int indici[EQUIP_SLOT];
};

equipArray_t equipArray_init()
{
    int i;
    equipArray_t x;
    x=malloc(sizeof *x);
    x->numero_equip=0;
    for(i=0; i<EQUIP_SLOT; i++)
        x->indici[i]=-1;
    return x;
}

void equipArray_add(equipArray_t *equipArray, int indice)
{
    int i;

    for(i=0; i<EQUIP_SLOT && (*equipArray)->indici[i]!=-1; i++);
    if(i<EQUIP_SLOT)
    {
        (*equipArray)->indici[i]=indice;
        (*equipArray)->numero_equip++;
    }
    else
        printf("\nroses are red\ngaming is fun\nyou are carrying too much to be able to run\n\n");
}

void equipArray_remove(equipArray_t *equipArray, int indice)
{
    int i, j;

    for(i=0; i<EQUIP_SLOT && (*equipArray)->indici[i]!=indice; i++);
    if(i<EQUIP_SLOT)
    {
        for(j=i; j<EQUIP_SLOT-1; j++)
            (*equipArray)->indici[j]=(*equipArray)->indici[j+1];
        (*equipArray)->indici[EQUIP_SLOT-1]=-1;
        (*equipArray)->numero_equip--;
        printf("\noggetto rimosso\n");
    }
    else
        printf("\noggetto non equipaggiato\n");
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray)
{
    int i;

    for(i=0; i<equipArray->numero_equip; i++)
        invArray_printByIndex(fp, invArray, equipArray->indici[i]);
}

void equipArray_free(equipArray_t equipArray)
{
    free(equipArray);
}

void equipArray_printStat(equipArray_t equipArray, invArray_t invArray, stat_t somma)
{
    int i;
    stat_t temp;

    for(i=0; i<equipArray->numero_equip; i++)
    {
        temp=inv_getStat(invArray_getByIndex(invArray, equipArray->indici[i]));
        somma=stat_sumStat(somma, temp);
    }
    stat_print(stdout, somma);
}
