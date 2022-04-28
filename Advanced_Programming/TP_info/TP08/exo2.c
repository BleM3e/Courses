#include <stdio.h>

void tri (int t[], int size)
{
    int n_ranger = 1; //Vaut 1 lorsque l'annuaire n'est pas encore trié, 0 sinon
    while (n_ranger == 1)
    {
        n_ranger = 0;
        for (int i = 0; i < size; i++)
        {
            if (t[i] > t[i+1])  //Pour faire un tri décroissant, il faut changer la condition avec t[i] < t[i+1]
            {
                n_ranger = 1;
                int tmp = t[i];
                t[i] = t[i+1];
                t[i+1] = tmp;
            }
        }
    }
}

int superieur (int a, int b)
{
    if (a == b) return 0;
    else return a > b ? 1 : -1;
}

int inferieur (int a, int b)
{
    if (a == b) return 0;
    else return a < b ? 1 : -1;
}

void tri_gen (int compare(int, int), int t[], int size)
{
    for (int j = 0; j < size-1; j++)
    {
        for (int i = 0; i < size-j-1; i++)
        {
            if (compare(t[i],t[i+1]) == 1)
            {
                int tmp = t[i];
                t[i] = t[i+1];
                t[i+1] = tmp;
            }
        }
    }
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
    int t[] = {2,1,3,5,4};
    int size = 5;

    tri_gen(superieur,t,size);
    aff(t,size);
    tri_gen(inferieur,t,size);
    aff(t,size);

    return 0;
}