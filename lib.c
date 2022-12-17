#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int *cria_matriz()
{
    return malloc(sizeof(int) * MAX * MAX);
}

void preenche_matriz_h(int *m)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            *(m + i * MAX + j) = 9;
        }
    }
}

void insere_bombas(int *m, int bombas)
{
    int num = 0;

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (rand() % 3 == 0)
            {
                *(m + i * MAX + j) = 0;
                if (num < bombas)
                {
                    num++;
                    *(m + i * MAX + j) = -1;
                }
            } else
                *(m + i * MAX + j) = 0;
        }
    }

    if (num < bombas)
        insere_bombas(m, bombas);
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
    if (row < 0 || row > MAX - 1|| col < 0 || col > MAX - 1)
        return 0;
    return 1;
}

void calcula_bloco(int *m, int row, int col)
{
    int num_bombas = 0;

    if (*(m + row * MAX + col) == -1)
        return;

    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (checa_limites(i, j) < 1)
                continue;

            if (*(m + i * MAX + j) == -1)
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
    int i = 0, j = 0;
    scanf("%d %d", &i, &j);
    *row = i - 1;
    *col = j - 1;
}

void libera_bloco(int* m, int* m_h, int row, int col)
{
    if (checa_limites(row, col) < 1)
        return;

    if (*(m + row * MAX + col) != 0)
    {
        *(m_h + row * MAX + col) = *(m + row * MAX + col);
        return;
    }

    if (*(m_h + row * MAX + col) == 9)
    {
        *(m_h + row * MAX + col) = *(m + row * MAX + col);

        for (int i = - 1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
                libera_bloco(m, m_h, row + i, col + j);
        }
    }
}

int numero_elemntos(int *m, int elemento)
{
    int n = 0;

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (*(m + i * MAX + j) == elemento)
                n++;
        }
    }
    
    return n;
}

int main()
{
    int *p_matriz = cria_matriz();
    int *p_matriz_h = cria_matriz();
    int row, col;
    int running = 1, bombas = 10;

    preenche_matriz_h(p_matriz_h);
    insere_bombas(p_matriz, bombas);
    calcula_blocos(p_matriz);

    system("cls");
    printf("Campo Minado do Binder\n\n");
    imprime_matriz(p_matriz_h);

    while (running)
    {
        recebe_comando(&row, &col);
        if (!checa_limites(row, col))
            continue;
        
        if (*(p_matriz + row * MAX + col) == -1)
            running--;

        libera_bloco(p_matriz, p_matriz_h, row, col);    

        system("cls");
        printf("Campo Minado do Binder\n\n");
        imprime_matriz(p_matriz_h);

        if (numero_elemntos(p_matriz_h, 9) == bombas)
            running = 0;
    }

    if (numero_elemntos(p_matriz_h, 9) == bombas)
    {
        printf("\nGANHASTE. CONFETTIS!!!\n\n");
    }
    else
        printf("\nBOOM! Perdeste.\n\n");

    free(p_matriz);
    free(p_matriz_h);
    p_matriz = NULL;
    p_matriz_h = NULL;
    
    return 0;
}