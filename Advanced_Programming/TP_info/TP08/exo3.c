/*
Q10: les void * sont les pointeurs vers une fonction void, ainsi on peut renvoyer l'adresse d'une fonction afin d'y accéder
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*int superieur (int a, int b)
{
    if (a == b) return 0;
    else return a > b ? 1 : -1;
}

int inferieur (int a, int b)
{
    if (a == b) return 0;
    else return a < b ? 1 : -1;
}*/

int compare (const void *pa, const void *pb)
{
    int a = *(int *)pa;
    int b = *(int *)pb;
    if (a == b) return 0;
    else return a > b ? 1 : -1;
}

int strcomp (const void *pa, const void *pb)
{
    char const *a = (char const *) pa;
    char const *b = (char const *) pb;
    return strcmp(a,b);
}

void aff (int t[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n",t[i]);
    }
    printf("\n");
}

int main()
{
    int t[] = {3,1,4,2,5};
    size_t size = 5;

    qsort(t,size,sizeof(int),compare);
    aff(t,size);

    //char s[9] = {'B','o','n','j','o','u','r','!','\0'};
    char s[] = "Bonjour!";
    size_t size_s = 8;

    qsort(s,size_s,sizeof(char),strcomp);
    for (int i=0;i<(int) size_s;i++)
    {
        printf("%c",s[i]);
    }
    printf("\n");

    return 0;
}