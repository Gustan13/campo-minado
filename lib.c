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
            *(m + i * MAX + j) = rand() % 3 == 0? (9) : (0);
        }
    }
}

void imprime_matriz(int *m)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", *(m + i * MAX + j));
        }
        printf("\n");
    } 
}

int main()
{
    int *p_matriz = cria_matriz();

    system("clear");
    insere_bombas(p_matriz);
    imprime_matriz(p_matriz);
    return 0;
}