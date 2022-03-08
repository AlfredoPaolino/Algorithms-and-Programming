#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define S 30
#define N 200
#define L 12

typedef struct
{
    char codifica[L+1];
    char originale[N+1];
} dizionario;

int salva_dizionario(FILE *fp_diz, dizionario diz[]);

void confronta_e_stampa(FILE *fp_sor, dizionario diz[], FILE *fp_ric, int ricodifiche);

void strshift(int indice, char riga[], char confronto[], dizionario diz[]);

int main()
{
    int ricodifiche;
    FILE *fp_sor, *fp_diz, *fp_ric;
    dizionario diz[S];
    fp_sor=fopen("sorgente.txt", "r");
    fp_diz=fopen("dizionario.txt", "r");
    fp_ric=fopen("ricodificato.txt", "w");

    ricodifiche=salva_dizionario(fp_diz, diz);
    fclose(fp_diz);

    confronta_e_stampa(fp_sor, diz, fp_ric, ricodifiche);
    fclose(fp_sor);
    fclose(fp_ric);

    return 0;
}

int salva_dizionario(FILE *fp_diz, dizionario diz[])
{
    int ricodifiche, i;

    fscanf(fp_diz, "%d", &ricodifiche);
    for (i=0;i<ricodifiche;i++)
        fscanf(fp_diz, "%s %s", diz[i].codifica, diz[i].originale);

    return ricodifiche;
}

void confronta_e_stampa(FILE *fp_sor, dizionario diz[], FILE *fp_ric, int ricodifiche)
{
    int i;
    char riga[N*L+1];
    char *confronto;
    while ((fgets(riga, N+1, fp_sor))!=NULL)
    {
        for (i=0;i<ricodifiche;i++)
        {
            if ((confronto=strstr(riga, diz[i].originale))!=NULL)
            {
                strshift(i, riga, confronto, diz);
                i=-1;
            }
        }
        fprintf(fp_ric, "%s", riga);
    }

}

void strshift(int indice, char riga[], char confronto[], dizionario diz[])
{
    int j;

    if (strlen(diz[indice].codifica)>strlen(diz[indice].originale))
    {
        for (j=strlen(riga)+1; j>strlen(riga)-strlen(confronto); j--)
            riga[j+strlen(diz[indice].codifica)-strlen(diz[indice].originale)]=riga[j];
        for (j=strlen(riga)-strlen(confronto); j<strlen(riga)-strlen(confronto)+strlen(diz[indice].codifica); j++)
            riga[j]=diz[indice].codifica[j-strlen(riga)+strlen(confronto)];
    }

     else if (strlen(diz[indice].codifica)<strlen(diz[indice].originale))
    {
        for (j=strlen(riga)-strlen(confronto)+strlen(diz[indice].codifica); j<strlen(riga); j++)
            riga[j]=riga[j+strlen(diz[indice].originale)-strlen(diz[indice].codifica)];
        for (j=strlen(riga)-strlen(confronto); j<strlen(riga)-strlen(confronto)+strlen(diz[indice].codifica); j++)
            riga[j]=diz[indice].codifica[j-strlen(riga)+strlen(confronto)];
    }

    else if (strlen(diz[indice].codifica)==strlen(diz[indice].originale))
    {
        for (j=strlen(riga)-strlen(confronto); j<strlen(riga)-strlen(confronto)+strlen(diz[indice].originale); j++)
            riga[j]=diz[indice].codifica[j-strlen(riga)+strlen(confronto)];
    }
}

