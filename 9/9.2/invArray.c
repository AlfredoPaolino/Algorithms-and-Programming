#include "invArray.h"

struct invArray_s
{
    int numero_oggetti;
    inv_t *oggetti;
};

invArray_t invArray_init()
{
    invArray_t temp;

    temp=malloc(sizeof *temp);
    temp->numero_oggetti=0;
    return temp;
}

void invArray_read(invArray_t invArray)
{
    int i;
    FILE *fp;

    fp=fopen("inventario.txt", "r");
    fscanf(fp, "%d", &(invArray->numero_oggetti));
    invArray->oggetti=malloc(invArray->numero_oggetti*sizeof(inv_t));
    for(i=0; i<invArray->numero_oggetti; i++)
        fscanf(fp, "%s %s %d %d %d %d %d %d", invArray->oggetti[i].nome, invArray->oggetti[i].tipo, &(invArray->oggetti[i].stat.hp), &(invArray->oggetti[i].stat.mp), &(invArray->oggetti[i].stat.atk), &(invArray->oggetti[i].stat.def), &(invArray->oggetti[i].stat.mag), &(invArray->oggetti[i].stat.spr));

}

void invArray_print(FILE *fp, invArray_t invArray)
{
    int i;

    for(i=0; i<invArray->numero_oggetti; i++)
        fprintf(fp,"%s %s %d %d %d %d %d %d\n", invArray->oggetti[i].nome, invArray->oggetti[i].tipo, invArray->oggetti[i].stat.hp, invArray->oggetti[i].stat.mp, invArray->oggetti[i].stat.atk, invArray->oggetti[i].stat.def, invArray->oggetti[i].stat.mag, invArray->oggetti[i].stat.spr);
}

int invArray_searchByName(invArray_t invArray, char *nome)
{
    int i;
    for(i=0; i<invArray->numero_oggetti; i++)
    {
        if(strcmp(invArray->oggetti[i].nome, nome)==0)
            return i;
    }
    printf("\noggetto non presente\n\n");
    return -1;
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int indice)
{
    fprintf(fp,"%s %s %d %d %d %d %d %d\n", invArray->oggetti[indice].nome, invArray->oggetti[indice].tipo, invArray->oggetti[indice].stat.hp, invArray->oggetti[indice].stat.mp, invArray->oggetti[indice].stat.atk, invArray->oggetti[indice].stat.def, invArray->oggetti[indice].stat.mag, invArray->oggetti[indice].stat.spr);
}

void invArray_free(invArray_t invArray)
{
    free(invArray->oggetti);
}

inv_t invArray_getByIndex(invArray_t invArray, int indice)
{
    return invArray->oggetti[indice];
}
