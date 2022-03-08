#include "inv.h"

stat_t inv_getStat(inv_t equip)
{
    return equip.stat;
}

stat_t stat_sumStat(stat_t somma, stat_t temp)
{
    stat_t totale;
    totale=stat_setVoid();
    totale.hp=somma.hp+temp.hp;
    totale.mp=somma.mp+temp.mp;
    totale.atk=somma.atk+temp.atk;
    totale.def=somma.def+temp.def;
    totale.mag=somma.mag+temp.mag;
    totale.spr=somma.spr+temp.spr;
    return totale;
}

stat_t stat_setVoid()
{
    stat_t temp;

    temp.hp=temp.mp=temp.atk=temp.def=temp.mag=temp.spr=0;
    return temp;
}

void stat_print(FILE *fp, stat_t stat)
{
    if(stat.hp>0)
        fprintf(fp, "hp: %d\n", stat.hp);
    else
        fprintf(fp, "hp: %d\n", MIN_STAT);
        if(stat.mp>0)
        fprintf(fp, "mp: %d\n", stat.mp);
    else
        fprintf(fp, "mp: %d\n", MIN_STAT);
            if(stat.atk>0)
        fprintf(fp, "atk: %d\n", stat.atk);
    else
        fprintf(fp, "atk: %d\n", MIN_STAT);
            if(stat.def>0)
        fprintf(fp, "def: %d\n", stat.def);
    else
        fprintf(fp, "def: %d\n", MIN_STAT);
            if(stat.mag>0)
        fprintf(fp, "mag: %d\n", stat.mag);
    else
        fprintf(fp, "mag: %d\n", MIN_STAT);
            if(stat.spr>0)
        fprintf(fp, "spr: %d\n", stat.spr);
    else
        fprintf(fp, "spr: %d\n", MIN_STAT);
}
