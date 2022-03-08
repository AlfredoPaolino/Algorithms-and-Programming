#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main()
{
    int a, b, valore;
    printf("inserisci a e b: ");
    scanf("%d %d", &a, &b);
    valore=gcd(a, b);
    printf("il massimo comune divisore tra %d e %d e': %d", a, b, valore);
    return 0;
}

int gcd(int a, int b)
{
    int valore;
    if(a<b)
    {
        a=a*b;
        b=a/b;
        a=a/b;
    }
    if(a!=b)
    {
        if(a%2==0 && b%2==0)
            valore=2*gcd(a/2, b/2);
        if(a%2==1 && b%2==0)
            valore=gcd(a, b/2);
        if(a%2==0 && b%2==1)
            valore=gcd(a/2, b);
        if(a%2==1 && b%2==1)
            valore=gcd((a-b)/2, b);
    }
    else
        valore=a;
    return valore;
}
