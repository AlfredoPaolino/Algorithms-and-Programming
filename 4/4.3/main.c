#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N 20

char* trova_espressione(char *src, char *regexp);

int primo_carattere(char *src, char *regexp, int *flag_valido);

int resto_espressione(char *src, char *regexp, int count_primo, int *flag_valido);

int main()
{
    char src[N+1]="scivolarevo" , regexp[N+1]="[ov][^s]\\a.r", *prima_ricorrenza;

    prima_ricorrenza=trova_espressione(src, regexp);

    printf("%s", prima_ricorrenza);
    return 0;
}

char* trova_espressione(char *src, char *regexp)
{
    int i, prima_ricorrenza, count_primo, flag_valido[strlen(src)];

    for(i=0; i<strlen(src); i++)
        flag_valido[i]=0;

    count_primo=primo_carattere(src, regexp, flag_valido);

    prima_ricorrenza=resto_espressione(src, regexp, count_primo, flag_valido);

    if(prima_ricorrenza!=-1)
        return src+prima_ricorrenza;

    return NULL;
}

int primo_carattere(char *src, char *regexp, int *flag_valido)
{
    int count_primo=0, j, k;

    if(isalpha(regexp[count_primo]))
    {
        for(j=0; j<strlen(src); j++)
        {
            if(src[j]==regexp[count_primo])
                flag_valido[j]=1;
        }
        count_primo++;
    }
    else
    {
        switch(regexp[count_primo])
        {
            case '[':
                count_primo++;
                if(regexp[count_primo]=='^')
                {
                    count_primo++;
                    for(j=0; j<strlen(src); j++)
                        flag_valido[j]=1;
                    k=count_primo;
                    while(regexp[k]!=']')
                    {
                        for(j=0; j<strlen(src); j++)
                        {
                            if(src[j]==regexp[k])
                                flag_valido[j]=0;
                        }
                        k++;
                        count_primo++;
                    }
                }

                else if(isalpha(regexp[count_primo]))
                {
                    k=count_primo;
                    while(regexp[k]!=']')
                    {
                        for(j=0; j<strlen(src); j++)
                        {
                            if(src[j]==regexp[k])
                                flag_valido[j]=1;
                        }
                        k++;
                        count_primo++;
                    }
                }
                count_primo++;
                break;

            case '.':
                for(j=0; j<strlen(src); j++)
                    flag_valido[j]=1;
                count_primo++;
                    break;
            case '\\':
                count_primo++;
                if(isupper(regexp[count_primo]))
                {
                    for(j=0; j<strlen(src); j++)
                    {
                        if(isupper(src[j]))
                            flag_valido[j]=1;
                    }
                }
                else if(islower(regexp[count_primo]))
                {
                    for(j=0; j<strlen(src); j++)
                    {
                        if(islower(src[j]))
                            flag_valido[j]=1;
                    }
                }
                count_primo++;
                break;
        }
    }
    return count_primo;
}

int resto_espressione(char *src, char *regexp, int count_primo, int *flag_valido)
{
    int i, j, k, flag_passa, count_resto;

    for(j=0; j<=strlen(src); j++)
    {
        count_resto=count_primo;
        if(flag_valido[j]==1)
        {
            i=j;
            while(flag_valido[j]==1 && count_resto!=strlen(regexp))
            {
                i++;
                if(isalpha(regexp[count_resto]))
                {
                    if(src[i]!=regexp[count_resto])
                        flag_valido[j]=0;
                    count_resto++;
                }
                else
                {
                    switch(regexp[count_resto])
                    {
                        case '[':
                            count_resto++;
                            if(regexp[count_resto]=='^')
                            {
                                count_resto++;
                                k=count_resto;
                                while(regexp[k]!=']')
                                {
                                    if(src[i]==regexp[k])
                                        flag_valido[j]=0;
                                    k++;
                                    count_resto++;
                                }
                            }
                            else if(isalpha(regexp[count_resto]))
                            {
                                k=count_resto;
                                flag_passa=0;
                                while(regexp[k]!=']')
                                {
                                    if(src[i]==regexp[k])
                                        flag_passa=1;
                                    k++;
                                    count_resto++;
                                }
                                if(flag_passa==0)
                                    flag_valido[j]=0;
                            }
                            count_resto++;
                            break;

                        case '.':
                            count_resto++;
                                break;

                        case '\\':
                            count_resto++;
                            if(isupper(regexp[count_resto]))
                            {
                                if(!isupper(src[i]))
                                    flag_valido[j]=0;
                            }
                            else if(islower(regexp[count_resto]))
                            {
                                if(!islower(src[i]))
                                    flag_valido[j]=0;
                            }
                            count_resto++;
                            break;
                    }
                }
            }
        }
        if(flag_valido[j]==1)
            return j;
    }
    return -1;
}
