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

int checa_limites(int row, int col)
{
    if (row < 0 || row > MAX || col < 0 || col > MAX)
        return 0;
    return 1;
}

void calcula_bloco(int *m, int row, int col)
{
    int num_bombas = 0;

    if (*(m + row * MAX + col) == 9)
        return;

    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (checa_limites(i, j) < 1)
                continue;

            if (*(m + i * MAX + j) == 9)
                num_bombas++;
        }
    }

    *(m + row * MAX + col) = num_bombas;
}

void calcula_blocos(int *m)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
            calcula_bloco(m, i, j);
    }
}

int main()
{
    int *p_matriz = cria_matriz();

    system("clear");
    insere_bombas(p_matriz);
    calcula_blocos(p_matriz);
    imprime_matriz(p_matriz);
    return 0;
}