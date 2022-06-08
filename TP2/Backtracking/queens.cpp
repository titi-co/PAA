#include <stdbool.h>
#include <stdio.h>

#define N 4

void showBoard(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", board[i][j]);
        printf("\n");
    }
}

bool isPositionSafe(int board[N][N], int row, int col)
{
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool queens_(int board[N][N], int col)
{
    // Caso base
    // Checa se todas as rainhas foram posicionadas
    if (col >= N)
        return true;

    // Em cada coluna, tenta colocar a rainha em todas as linhas, uma por uma
    for (int i = 0; i < N; i++)
    {
        // Checa se a posição é valida
        if (isPositionSafe(board, i, col))
        {
            // Coloca a rainha no tabuleiro
            board[i][col] = 1;

            // Avança Recursivamente para a proxima coluna
            if (queens_(board, col + 1))
                return true;

            // Backtracking
            board[i][col] = 0; // BACKTRACK
        }
    }

    return false;
}

bool queens()
{
    // Cria o tabuleiro
    int board[N][N] = {{0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}};

    if (queens_(board, 0) == false)
    {
        return false;
    }

    showBoard(board);
}

// driver program to test above function
int main()
{
    queens();
    return 0;
}