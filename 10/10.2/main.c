#include <stdio.h>
#include <stdlib.h>

#define MAX_DIAG 5
#define DIAG 3
#define DD 10
#define DP
#define DIFF 8
#define MOLT 1.5

typedef struct
{
    char nome[50+1];
    int tipologia;
    int direzione_ingresso;
    int direzione_uscita;
    int precedenza;
    int finale;
    float valore;
    int difficolta;
} elemento_t;

typedef struct
{
    elemento_t* tabella;
    int numero_elementi;
} tab_elemento_t;

tab_elemento_t leggi_elementi();

void ultima_diagonale(tab_elemento_t tabella_elementi);

void disp_rip(tab_elemento_t tabella_elementi, int pos, int *difficolta, float *punteggio_massimo, int *soluzione_attuale, int *soluzione_finale);

int check_difficolta(tab_elemento_t tabella_elementi, int precedente, int difficolta);

int confronta_punteggio(tab_elemento_t tabella_elementi, int pos, int *soluzione_attuale, float *punteggio_massimo);

int check_acrobatico(tab_elemento_t tabella_elementi, int pos, int *soluzione_attuale);

int main()
{
    tab_elemento_t tabella_elementi;

    tabella_elementi=leggi_elementi();

    ultima_diagonale(tabella_elementi);

    return 0;
}

tab_elemento_t leggi_elementi()
{
    FILE *fp;
    tab_elemento_t temp;
    int i;

    fp=fopen("elementi.txt", "r");
    fscanf(fp, "%d", &(temp.numero_elementi));
    temp.tabella=malloc(temp.numero_elementi*sizeof(elemento_t));
    for(i=0; i<temp.numero_elementi; i++)
        fscanf(fp, "%s %d %d %d %d %d %f %d", temp.tabella[i].nome, &(temp.tabella[i].tipologia), &(temp.tabella[i].direzione_ingresso), &(temp.tabella[i].direzione_uscita), &(temp.tabella[i].precedenza), &(temp.tabella[i].finale), &(temp.tabella[i].valore), &(temp.tabella[i].difficolta));

    return temp;
}

void ultima_diagonale(tab_elemento_t tabella_elementi)
{
    int soluzione_attuale[MAX_DIAG], soluzione_finale[MAX_DIAG];
    float punteggio_massimo=0;
    int difficolta=0;

    disp_rip(tabella_elementi, 0, &difficolta, &punteggio_massimo, soluzione_attuale, soluzione_finale);
 //   for(int i=0; i<MAX_DIAG; i++)
      //  printf("\n%s \n", tabella_elementi.tabella[soluzione_finale[i]].nome);
}

void disp_rip(tab_elemento_t tabella_elementi, int pos, int *difficolta, float *punteggio_massimo, int *soluzione_attuale, int *soluzione_finale)
{
    int i, j;



        if(pos>0 && *difficolta<=DD && check_acrobatico(tabella_elementi, pos, soluzione_attuale) && confronta_punteggio(tabella_elementi, pos-1, soluzione_attuale, punteggio_massimo))
            {
                for(j=0; j<pos; j++)
                    soluzione_finale[j]=soluzione_attuale[j];
            }
    if(pos>=MAX_DIAG || (pos>0&&tabella_elementi.tabella[soluzione_attuale[pos-1]].finale==1) || (pos>0&&check_difficolta(tabella_elementi, soluzione_attuale[pos-1], *difficolta)))
    {
            return;
    }
    for(i=0; i<tabella_elementi.numero_elementi; i++)
    {
        if(pos==0)
        {
            if(tabella_elementi.tabella[i].direzione_ingresso==1 && tabella_elementi.tabella[i].precedenza==0)
            {
                soluzione_attuale[pos]=i;
                *difficolta+=tabella_elementi.tabella[i].difficolta;
                disp_rip(tabella_elementi, pos+1, difficolta, punteggio_massimo, soluzione_attuale, soluzione_finale);
                *difficolta-=tabella_elementi.tabella[i].difficolta;
            }
        }
        else
        {
            if(tabella_elementi.tabella[i].direzione_ingresso==tabella_elementi.tabella[soluzione_attuale[pos-1]].direzione_uscita)
            {
                soluzione_attuale[pos]=i;
                *difficolta+=tabella_elementi.tabella[i].difficolta;
                disp_rip(tabella_elementi, pos+1, difficolta, punteggio_massimo, soluzione_attuale, soluzione_finale);
                *difficolta-=tabella_elementi.tabella[i].difficolta;
            }
        }
    }
}

int check_difficolta(tab_elemento_t tabella_elementi, int precendente, int difficolta)
{
    int i;

    for(i=0; i<tabella_elementi.numero_elementi; i++)
    {
        if(difficolta+tabella_elementi.tabella[i].difficolta<DD && tabella_elementi.tabella[i].direzione_ingresso==tabella_elementi.tabella[precendente].direzione_uscita)
            return 0;
    }
    return 1;
}

int confronta_punteggio(tab_elemento_t tabella_elementi, int pos, int *soluzione_attuale, float *punteggio_massimo)
{
    float temp_punteggio=0;
    int i;

    for(i=0; i<=pos; i++)
        temp_punteggio+=tabella_elementi.tabella[soluzione_attuale[i]].valore;
    if(tabella_elementi.tabella[soluzione_attuale[pos]].difficolta>=8)
        temp_punteggio*=1.5;
    if(temp_punteggio>*punteggio_massimo)
    {
        *punteggio_massimo=temp_punteggio;

        return 1;
    }
    return 0;
}

int check_acrobatico(tab_elemento_t tabella_elementi, int pos, int *soluzione_attuale)
{
    int i;

    for(i=0; i<pos; i++)
    {
        if(tabella_elementi.tabella[soluzione_attuale[i]].tipologia!=0)
            return 1;
    }
    return 0;
}
