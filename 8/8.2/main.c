#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char colore1;
    int valore1;
    char colore2;
    int valore2;
    int flag_partenza;
} tessera_t;

typedef struct
{
    tessera_t *tessere;
    int numero_tessere;
} tab_tessere_t;

void leggi_tiles(tab_tessere_t *tabella_tessere_ptr);

typedef struct
{
    int numero_tessera;
    int rotazione;
    int flag_partenza;
} board_t;

typedef struct
{
    board_t **board;
    int righe;
    int colonne;
} tab_board_t;

void leggi_board(tab_board_t *tabella_board_ptr);

void disposizioni_con_rotazione(tab_tessere_t tabella_tessere, tab_board_t tabella_board, int pos , int *mark, board_t **finale, int *punteggio_attuale, int *punteggio_massimo);

int calcola_punteggio(tab_tessere_t tabella_tessere, board_t **finale, int righe, int colonne);

void free_all(board_t **finale, int righe, int *mark, tab_tessere_t tabella_tessere);

int main()
{
    tab_tessere_t tabella_tessere;
    tab_board_t tabella_board;
    board_t **finale;
    int *mark;
    int i, j, punteggio_massimo=0, punteggio_attuale=0;

    leggi_tiles(&tabella_tessere);
    leggi_board(&tabella_board);

    for(i=0; i<tabella_board.righe; i++)
    {
        for( j=0; j<tabella_board.colonne; j++)
        {
            if(tabella_board.board[i][j].numero_tessera!=-1)
                {
                    tabella_board.board[i][j].flag_partenza=1;
                    tabella_tessere.tessere[tabella_board.board[i][j].numero_tessera].flag_partenza=1;
                }
        }
    }
    mark=calloc(tabella_tessere.numero_tessere, sizeof(int));
    finale=malloc(tabella_board.righe*sizeof(board_t*));
    for(i=0; i<tabella_board.righe; i++)
            finale[i]=malloc(tabella_board.colonne*sizeof(board_t));
    disposizioni_con_rotazione(tabella_tessere, tabella_board, 0, mark, finale, &punteggio_attuale, &punteggio_massimo);
    printf("il punteggio massimo conseguibile e': %d\n", punteggio_massimo);
    free_all(finale, tabella_board.righe, mark, tabella_tessere);
    return 0;
}

void leggi_tiles(tab_tessere_t *tabella_tessere_ptr)
{
    int i;
    FILE *fp;

    fp=fopen("tiles.txt", "r");
    fscanf(fp, "%d", &tabella_tessere_ptr->numero_tessere);
    tabella_tessere_ptr->tessere=malloc(tabella_tessere_ptr->numero_tessere*sizeof(tessera_t));
    for(i=0; i<tabella_tessere_ptr->numero_tessere; i++)
        {
            fgetc(fp);
            fscanf(fp, "%c %d %c %d", &tabella_tessere_ptr->tessere[i].colore1, &tabella_tessere_ptr->tessere[i].valore1, &tabella_tessere_ptr->tessere[i].colore2, &tabella_tessere_ptr->tessere[i].valore2);
            tabella_tessere_ptr->tessere[i].flag_partenza=0;
        }
}

void leggi_board(tab_board_t *tabella_board_ptr)
{
    int i, j;
    FILE *fp;

    fp=fopen("board.txt", "r");
    fscanf(fp, "%d %d", &tabella_board_ptr->righe, &tabella_board_ptr->colonne);
    tabella_board_ptr->board=malloc(tabella_board_ptr->righe*sizeof(board_t*));
    for(i=0; i<tabella_board_ptr->righe; i++)
        tabella_board_ptr->board[i]=malloc(tabella_board_ptr->colonne*sizeof(board_t));
    for(i=0; i<tabella_board_ptr->righe; i++)
    {
        for(j=0; j<tabella_board_ptr->colonne; j++)
            fscanf(fp, "%d/%d", &tabella_board_ptr->board[i][j].numero_tessera, &tabella_board_ptr->board[i][j].rotazione);
    }
}

void disposizioni_con_rotazione(tab_tessere_t tabella_tessere, tab_board_t tabella_board, int pos , int *mark, board_t **finale, int *punteggio_attuale, int *punteggio_massimo)
{
    int i;

    if(pos>=tabella_board.colonne*tabella_board.colonne)
    {
        *punteggio_attuale=calcola_punteggio(tabella_tessere, finale, tabella_board.righe, tabella_board.colonne);
        if(*punteggio_attuale>*punteggio_massimo)
            *punteggio_massimo=*punteggio_attuale;
        return;
    }

    if(tabella_board.board[pos/tabella_board.colonne][pos%tabella_board.colonne].flag_partenza==1)
    {
        mark[tabella_board.board[pos/tabella_board.colonne][pos%tabella_board.colonne].numero_tessera]=1;
        finale[pos/tabella_board.colonne][pos%tabella_board.colonne]=tabella_board.board[pos/tabella_board.colonne][pos%tabella_board.colonne];
        disposizioni_con_rotazione(tabella_tessere, tabella_board, pos+1, mark, finale, punteggio_attuale, punteggio_massimo);
    }
    else
    {
        for(i=0; i<tabella_tessere.numero_tessere; i++)
        {
            if(mark[i]==0 && tabella_tessere.tessere[i].flag_partenza==0)
            {
                mark[i]=1;
                finale[pos/tabella_board.colonne][pos%tabella_board.colonne].numero_tessera=i;
                finale[pos/tabella_board.colonne][pos%tabella_board.colonne].rotazione=0;
                disposizioni_con_rotazione(tabella_tessere, tabella_board, pos+1, mark, finale, punteggio_attuale, punteggio_massimo);
                finale[pos/tabella_board.colonne][pos%tabella_board.colonne].rotazione=1;
                disposizioni_con_rotazione(tabella_tessere, tabella_board, pos+1, mark, finale, punteggio_attuale, punteggio_massimo);
                mark[i]=0;
            }
        }
    }
    return;
}

int calcola_punteggio(tab_tessere_t tabella_tessere, board_t **finale, int righe, int colonne)
{
    int i, j, totale=0, punteggio_linea;

    for(i=0; i<righe; i++)
    {
        punteggio_linea=0;
        for(j=0; j<colonne; j++)
        {
            if(finale[i][j].rotazione==0 && finale[i][0].rotazione==0)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore1==tabella_tessere.tessere[finale[i][0].numero_tessera].colore1)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore1;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
            else if(finale[i][j].rotazione==0 && finale[i][0].rotazione==1)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore1==tabella_tessere.tessere[finale[i][0].numero_tessera].colore2)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore1;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
            else if(finale[i][j].rotazione==1 && finale[i][0].rotazione==0)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore2==tabella_tessere.tessere[finale[i][0].numero_tessera].colore1)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore2;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
            else if(finale[i][j].rotazione==1 && finale[i][0].rotazione==1)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore2==tabella_tessere.tessere[finale[i][0].numero_tessera].colore2)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore2;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
        }
        totale+=punteggio_linea;
    }
    for(j=0; j<colonne; j++)
    {
        punteggio_linea=0;
        for(i=0; i<righe; i++)
        {
            if(finale[i][j].rotazione==0 && finale[0][j].rotazione==0)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore2==tabella_tessere.tessere[finale[0][j].numero_tessera].colore2)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore2;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
            else if(finale[i][j].rotazione==0 && finale[0][j].rotazione==1)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore2==tabella_tessere.tessere[finale[0][j].numero_tessera].colore1)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore2;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
            else if(finale[i][j].rotazione==1 && finale[0][j].rotazione==0)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore1==tabella_tessere.tessere[finale[0][j].numero_tessera].colore2)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore1;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
            else if(finale[i][j].rotazione==1 && finale[0][j].rotazione==1)
            {
                if(tabella_tessere.tessere[finale[i][j].numero_tessera].colore1==tabella_tessere.tessere[finale[0][j].numero_tessera].colore1)
                    punteggio_linea+=tabella_tessere.tessere[finale[i][j].numero_tessera].valore2;
                else
                {
                    punteggio_linea=0;
                    break;
                }
            }
        }
        totale+=punteggio_linea;
    }

    return totale;
}

void free_all(board_t **finale, int righe, int *mark, tab_tessere_t tabella_tessere)
{
    int i;

    free(mark);
    free(tabella_tessere.tessere);
    for(i=0; i<righe; i++)
        free(finale[i]);
    free(finale);
}
