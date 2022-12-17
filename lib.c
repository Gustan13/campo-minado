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
            *(m + i * MAX + j) = rand() % 2 == 0? (9) : (0);
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
    printf("\n");
}

int checa_limites(int row, int col)
{
    if (row < 0 || row > MAX - 1|| col < 0 || col > MAX - 1)
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

void recebe_comando(int *row, int *col)
{
    scanf("%d %d", row, col);
}

void libera_bloco(int *m, int *m_h, int row, int col)
{
    if (checa_limites(row, col) < 1)
        return;

    *(m_h + row * MAX + col) = *(m + row * MAX + col);

    if (*(m + row * MAX + col) != 0)
        return; 
}

int main()
{
    int *p_matriz = cria_matriz();
    int *p_matriz_h = cria_matriz();
    int row, col;
    int running = 1;

    insere_bombas(p_matriz);
    calcula_blocos(p_matriz);

    system("clear");
    printf("Campo Minado do Binder\n9 significa bomba.\n\n");
    imprime_matriz(p_matriz_h);

    while (running)
    {
        recebe_comando(&row, &col);
        if (!checa_limites(row, col))
            continue;
        
        if (*(p_matriz + row * MAX + col) == 9)
            running--;

        libera_bloco(p_matriz, p_matriz_h, row, col);    
        system("clear");
        printf("Campo Minado do Binder\n9 significa bomba.\n\n");
        imprime_matriz(p_matriz_h);
    }

    printf("\nBOOM! Perdeste.\n\n");
    
    return 0;
}