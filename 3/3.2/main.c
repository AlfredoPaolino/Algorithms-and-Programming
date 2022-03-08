#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BIT 8

typedef enum {FALSO, VERO} boolean;

int controllo_endianness();

void stampa_dimensione(float af, double al, long double ald);

void codifica_binaria (void *p, int dimensione, int big_endian);

void stampa_codifica(int dimensione, int codifica[]);

int main()
{
    float af, valore;
    double al;
    long double ald;
    boolean big_endian;

    big_endian=controllo_endianness();

    stampa_dimensione(af, al, ald);

    printf("inserire valore da codificare: ");
    scanf("%f", &valore);

    af=valore;
    al=valore;
    ald=valore;

    printf("\ncodifica in formato float:\n");
    codifica_binaria((void *)&af, sizeof(af), big_endian);

    printf("\ncodifica in formato double:\n");
    codifica_binaria((void *)&al, sizeof(al), big_endian);

    printf("\ncodifica in formato long double:\n");
    codifica_binaria((void *)&ald, sizeof(ald), big_endian);

    return 0;
}

int controllo_endianness()
{
    int n=1;
    void *p=&n;
    unsigned char *pcar=p;

    if (*pcar==1)
        return FALSO;
    else
        return VERO;
}

void stampa_dimensione(float af, double al, long double ald)
{
    printf("dimensione float: %d byte=%d bit\n", sizeof(af), BIT*sizeof(af));
    printf("dimensione double: %d byte=%d bit\n", sizeof(al), BIT*sizeof(al));
    printf("dimensione long double: %d byte=%d bit\n\n", sizeof(ald), BIT*sizeof(ald));
}

void codifica_binaria (void *p, int dimensione, int big_endian)
{
    int codifica[BIT*dimensione];
    int i, j, byte;
    unsigned char *pcar=p;

    if(big_endian==0)
    {
        for(i=0; i<dimensione; i++)
        {
            byte=*(pcar+dimensione-i-1);
            for(j=BIT*i+BIT-1; j>=BIT*i; j--)
                {
                     if(byte!=0)
                        codifica[j]=byte%2;
                        else
                            codifica[j]=0;
                     byte/=2;
                }
        }
    }

    else if(big_endian==1)
    {
        for(i=0; i<dimensione; i++)
        {
            byte=*(pcar+i);
            for(j=BIT*i+BIT-1; j>=BIT*i; j--)
                {
                     if(byte!=0)
                        codifica[j]=byte%2;
                        else
                            codifica[j]=0;
                     byte/=2;
                }
        }
    }
    stampa_codifica(dimensione, codifica);
}

void stampa_codifica(int dimensione, int codifica[])
{
    int i;

    if(dimensione==4)
    {
        printf("bit di segno: ");
        for(i=0; i<1; i++)
            printf("%d", codifica[i]);

        printf("\nbit di esponente: ");
        for(i=i; i<9; i++)
            printf("%d", codifica[i]);

        printf("\nbit di mantissa: ");
        for(i=i; i<32; i++)
            printf("%d", codifica[i]);
    }

    else if(dimensione==8)
    {
        printf("bit di segno: ");
        for(i=0; i<1; i++)
            printf("%d", codifica[i]);

        printf("\nbit di esponente: ");
        for(i=i; i<12; i++)
            printf("%d", codifica[i]);

        printf("\nbit di mantissa: ");
        for(i=i; i<64; i++)
            printf("%d", codifica[i]);
    }

    else if(dimensione==12)
    {
        printf("bit di padding: ");
        for(i=0; i<16; i++)
            printf("%d", codifica[i]);

        printf("\nbit di segno: ");
        for(i=i; i<17; i++)
            printf("%d", codifica[i]);

        printf("\nbit di esponente: ");
        for(i=i; i<32; i++)
            printf("%d", codifica[i]);

        printf("\nbit di parte intera: ");
        for(i=i; i<33; i++)
            printf("%d", codifica[i]);

        printf("\nbit di mantissa: ");
        for(i=i; i<96; i++)
            printf("%d", codifica[i]);
    }
    printf("\n");
}
