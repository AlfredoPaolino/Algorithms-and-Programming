#include "tempo.h"

int DATAcmp(data_t x, data_t y)
{
    if(x.anno!=y.anno)
        return x.anno-y.anno;
    if(x.mese!=y.mese)
        return x.mese-y.mese;
    if(x.giorno!=y.giorno)
        return x.giorno-y.giorno;
    return 0;
}

data_t DATSstringToData(char *buffer)
{
    data_t x;
    sscanf(buffer, "%d/%d/%d", &x.anno, &x.mese, &x.giorno);
    return x;
}

data_t DATAsetNull()
{
    data_t x;
    x.anno=0;
    x.mese=0;
    x.giorno=0;
    return x;
}

data_t DATAsetInf()
{
    data_t x;
    x.anno=INT_MAX;
    x.mese=INT_MAX;
    x.giorno=INT_MAX;
    return x;
}

int DATAbetween(data_t myData, data_t dataDown, data_t dataUp)
{
    if(DATAcmp(myData, dataUp)>0)
        return 1;
    if(DATAcmp(myData, dataDown)<0)
        return -1;
    return 0;
}

void DATAprint(data_t data)
{
    printf("\ndata: %.4d/%.2d/%.2d\t", data.anno, data.mese, data.giorno);
}

void ORAprint(ora_t ora)
{
    printf("ora: %.2d:%.2d\t", ora.ore, ora.minuti);
}
