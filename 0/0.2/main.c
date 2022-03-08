#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N 20

//dichiarazione funzione

int conta (char S[N+1], int n);

int main()
{
    int n, i, righe, sottostringhe;
    FILE *fp;
    char nome_file[N+1], parola[N+1];

    //apertura file

    printf("inserire nome file: ");
    scanf("%s", nome_file);
    fp=fopen(nome_file, "r");

    //lunghezza sottostringhe

    printf("inserire lunghezza sottostringhe: ");
    scanf("%d", &n);

    //lettura file

    fscanf(fp, "%d", &righe);
    for (i=0;i<righe;i++)
    {
        fscanf(fp, "%s", parola);
        sottostringhe=conta(parola, n);
        printf("%d\n", sottostringhe);
    }
    return 0;
}

int conta (char S[N+1], int n)
{
    int x, i, j, count;
    x=0;
    for (i=0;i<strlen(S)-n+1;i++)
    {
        count=0;
        for (j=i;j<i+n;j++)
        {
            if (isalpha(S[j])==1)
                S[j]=tolower(S[j]);
            if (S[j]=='a' || S[j]=='e' || S[j]=='i' || S[j]=='o' || S[j]=='u')
                count++;
        }
        if (count==2)
            x++;
    }
    return x;
}
