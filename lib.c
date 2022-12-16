#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int *cria_matriz()
{
    return malloc(sizeof(int) * MAX * MAX);
}

void insere_bombas(int *m)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            *(m + i * MAX + j) = rand() % 2 == 0? (-1) : (0);
        }
    }
}

int main()
{
    int *p_matriz = cria_matriz();
    return 0;
}