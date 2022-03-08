#include "quotazioni.h"

typedef struct BSTnode *link2;

struct BSTnode
{
    quotazione_t quotazione;
    link2 l;
    link2 r;
    int N;
};

struct BSTquotazioni_s
{
    link2 root;
    link2 z;
};

typedef data_t key;

static link2 NEWnode(quotazione_t quotazione, link2 l, link2 r, int N)
{
    link2 x=malloc(sizeof *x);
    x->quotazione=quotazione;
    x->l=l;
    x->r=r;
    x->N=N;
    return x;
}

static quotazione_t ITEMsetNull()
{
    quotazione_t x;
    x.scambiati=0;
    return x;
}

BSTquotazioni_t BSTinit()
{
    BSTquotazioni_t bst=malloc(sizeof *bst);
    bst->root=(bst->z=NEWnode(ITEMsetNull(), NULL, NULL, 0));
    return bst;
}

int KEYcmp(data_t x, data_t y)
{
    return DATAcmp(x, y);
}

data_t KEYget(quotazione_t x)
{
    return x.data;
}

static link2 QUOTAZIONEupdate(link2 h, quotazione_t x)
{
    h->quotazione.scambiati+=x.scambiati;
    h->quotazione.totale+=x.totale;
    h->quotazione.valore=(float)h->quotazione.totale/(float)h->quotazione.scambiati;
    return h;

}

static link2 BSTinsert(link2 h, quotazione_t quotazione, link2 z)
{
    if(h==z)
        return NEWnode(quotazione, z, z, 1);
    if(KEYcmp(KEYget(quotazione), KEYget(h->quotazione))<0)
    {
        h->l=BSTinsert(h->l, quotazione, z);
        (h->N)++;
    }
    if(KEYcmp(KEYget(quotazione), KEYget(h->quotazione))>0)
    {
        h->r=BSTinsert(h->r, quotazione, z);
        (h->N)++;
    }
    if(KEYcmp(KEYget(quotazione), KEYget(h->quotazione))==0)
        h=QUOTAZIONEupdate(h, quotazione);
        return h;
}

void BSTfill(BSTquotazioni_t bst, quotazione_t quotazione)
{

    bst->root=BSTinsert(bst->root, quotazione, bst->z);
}

static void BSTprintR(link2 h, link2 z)
{
    if(h!=z)
    {
        BSTprintR(h->l, z);
        printf("%f\n", h->quotazione.valore);
        BSTprintR(h->r, z);
    }
}

void BSTprint(BSTquotazioni_t bst)
{
    BSTprintR(bst->root, bst->z);
}

static float BSTsearchR(link2 h, data_t data, link2 z)
{
    int cmp;
    if(h==z)
        return 0;
    cmp=DATAcmp(data, h->quotazione.data);
    if(cmp==0)
        return h->quotazione.valore;
    if(cmp<0)
        return BSTsearchR(h->l, data, z);
    return BSTsearchR(h->r, data, z);
}

float BSTsearchQuotazioneByData(BSTquotazioni_t bst, data_t data)
{
    return BSTsearchR(bst->root, data, bst->z);
}
static void BSTsearchBetweenData(link2 h, link2 z, float *quotazioneMin, float *quotazioneMax, data_t dataDown, data_t dataUp)
{
    int cmp;
    if(h==z)
        return;
    cmp=DATAbetween(h->quotazione.data, dataDown, dataUp);
    if(cmp>0)
        BSTsearchBetweenData(h->l, z, quotazioneMin, quotazioneMax, dataDown, dataUp);
    else if(cmp==0)
    {
        BSTsearchBetweenData(h->l, z, quotazioneMin, quotazioneMax, dataDown, dataUp);
        if(h->quotazione.valore<*quotazioneMin)
            *quotazioneMin=h->quotazione.valore;
        if(h->quotazione.valore>*quotazioneMax)
            *quotazioneMax=h->quotazione.valore;
        BSTsearchBetweenData(h->r, z, quotazioneMin, quotazioneMax, dataDown, dataUp);
    }
    else if(cmp<0)
        BSTsearchBetweenData(h->r, z, quotazioneMin, quotazioneMax, dataDown, dataUp);
}

void BSTquotazioneMinMax(BSTquotazioni_t bst, float *quotazioneMin, float *quotazioneMax, data_t dataDown, data_t dataUp)
{
    return BSTsearchBetweenData(bst->root, bst->z, quotazioneMin, quotazioneMax, dataDown, dataUp);
}

static link2 BSTrotR(link2 h)
{
    link2 x=h->l;
    h->l=x->r;
    x->r=h;
    x->N=h->N;
    h->N=1;
    h->N+=(h->l) ? h->l->N : 0;
    h->N+=(h->r) ? h->r->N : 0;
    return x;
}

static link2 BSTrotL(link2 h)
{
    link2 x=h->r;
    h->r=x->l;
    x->l=h;
    x->N=h->N;
    h->N=1;
    h->N+=(h->l) ? h->l->N : 0;
    h->N+=(h->r) ? h->r->N : 0;
    return x;
}

static link2 BSTpartR(link2 h, int r)
{
    int t=h->l->N;
    if(t>r)
    {
        h->l=BSTpartR(h->l, r);
        h=BSTrotR(h);
    }
    if(t<r)
    {
        h->r=BSTpartR(h->r, r-t-1);
        h=BSTrotL(h);
    }
    return h;
}

static link2 BSTbalanceR(link2 h, link2 z)
{
    int r;
    if(h==z)
        return z;
    r=(h->N+1)/2-1;
    h=BSTpartR(h, r);
    h->l=BSTbalanceR(h->l, z);
    h->r=BSTbalanceR(h->r, z);
    return h;
}

void BSTbalance(BSTquotazioni_t bst)
{
    bst->root=BSTbalanceR(bst->root, bst->z);
}

static void BSTsearchHeight(link2 h, link2 z, int *altezzaMin, int *altezzaMax, int height)
{
    if(h->l==z && h->r==z)
    {
        if(height>*altezzaMax)
            *altezzaMax=height;
        if(height<*altezzaMin)
            *altezzaMin=height;
        return;
    }
    height++;
    if(h->l!=z)
        BSTsearchHeight(h->l, z, altezzaMin, altezzaMax, height);
    if(h->r!=z)
    BSTsearchHeight(h->r, z, altezzaMin, altezzaMax, height);
    height--;
}

void BSTaltezzaMinMax(BSTquotazioni_t bst, int *altezzaMin, int *altezzaMax)
{
    int height=0;
    return BSTsearchHeight(bst->root, bst->z, altezzaMin, altezzaMax, height);
}
