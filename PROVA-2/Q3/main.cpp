#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

// Sendo uma solucao em dinamic programming, salvo os resultados dos subproblemas para evitar computar resultados repetidos
// Essa solucao alcança entao uma complexidade de O(m* n) sendo m e n o tamanho das strings
//

int MSCDP(char *X, char *Y, int sizeX, int sizeY)
{
    int res[sizeX + 1][sizeY + 1];

    // Preenche a tabela de resultados utilizando bottom up
    // Dessa forma, calculamos os subproblemas do menor ao maior, tendo assim os subproblemas menores ja computados

    for (int i = 0; i <= sizeX; i++)
    {
        for (int j = 0; j <= sizeY; j++)
        {
            if (!i)
                res[i][j] = j;

            else if (!j)
                res[i][j] = i;

            else if (X[i - 1] == Y[j - 1])
                res[i][j] = 1 + res[i - 1][j - 1];

            else
                res[i][j] = 1 + min(res[i - 1][j], res[i][j - 1]);
        }
    }
    // res[sizeX][sizeY] tem o tamanho da lcs
    return res[sizeX][sizeY];
}

int main()
{
    // String de entrada X e Y
    char X[] = "abca";
    char Y[] = "bad";

    int sizeX = strlen(X), sizeY = strlen(Y);

    cout << MSCDP(X, Y, sizeX, sizeY) << endl;
}