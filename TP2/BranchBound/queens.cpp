#include <iostream>
#include <string.h>
using namespace std;

#define N 8

// Percorre e mostra o tabuleiro
void showBoard(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << " " << board[i][j];
        cout << "\n";
    }
}

// Checa se uma posicao do tabuleiro é valida
bool isPositionSafe(int row, int col, int slashC[N][N],
                    int backslashC[N][N], bool rowL[],
                    bool slashCL[], bool backslashCL[])
{
    if (slashCL[slashC[row][col]] ||
        backslashCL[backslashC[row][col]] ||
        rowL[row])
        return false;

    return true;
}

bool queens_(int board[N][N], int col,
             int slashC[N][N], int backslashC[N][N],
             bool rowL[N],
             bool slashCL[],
             bool backslashCL[])
{
    // Caso base
    // Checa se todas as rainhas foram posicionadas
    if (col >= N)
        return true;

    // Em cada coluna, tenta colocar a rainha em todas as linhas, uma por uma
    for (int i = 0; i < N; i++)
    {
        // Testa se a posicao é valida
        if (isPositionSafe(i, col, slashC,
                           backslashC, rowL,
                           slashCL, backslashCL))
        {
            // Coloca a rainha no tabuleiro
            board[i][col] = 1;
            rowL[i] = true;
            slashCL[slashC[i][col]] = true;
            backslashCL[backslashC[i][col]] = true;

            //Recursao para a proxima coluna, para colocar a proxima rainha
            if (queens_(board, col + 1,
                        slashC, backslashC,
                        rowL, slashCL, backslashCL))
                return true;

            // Backtracking
            board[i][col] = 0;
            rowL[i] = false;
            slashCL[slashC[i][col]] = false;
            backslashCL[backslashC[i][col]] = false;
        }
    }

    return false;
}

bool queens()
{
    int board[N][N];
    memset(board, 0, sizeof board);

    // auxiliares
    int slashC[N][N];
    int backslashC[N][N];

    // array de linhas ocupadas
    bool rowL[N] = {false};

    // Controla quais diagonais estao ocupadas
    bool slashCL[2 * N - 1] = {false};
    bool backslashCL[2 * N - 1] = {false};

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
        {
            slashC[r][c] = r + c,
            backslashC[r][c] = r - c + 7;
        }

    if (queens_(board, 0,
                slashC, backslashC,
                rowL, slashCL, backslashCL) ==
        false)
    {
        cout << "Solution does not exist";
        return false;
    }

    showBoard(board);
    return true;
}

int main()
{
    queens();
}
