int fois_deux (int);

int fois_deux (int x)
{
    return 2*x;
}

void appliquer_tableau (int f(int), int t[], int size)
{
    for (int i = 0; i < size; i++)
    {
        t[i] = f(t[i]);
    }
}

int main ()
{
    int tab[] = {1,2,3,4};
    appliquer_tableau(fois_deux, tab, 4);

    return 0;
}