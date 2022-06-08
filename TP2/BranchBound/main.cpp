#include <iostream>

using namespace std;

#define N 4

// Variaveis de controle e de resposta
int res[N + 1];
bool visited[N];
int weight = INT_MAX;

// Funcoes auxiliares para achar os limites, pegam os menor pesos
int firstMin(int g[N][N], int i)
{
    int min = INT_MAX;

    for (int j = 0; j < N; j++)
        if (g[i][j] < min && i != j)
            min = g[i][j];

    return min;
}

int secondMin(int g[N][N], int i)
{
    int f = INT_MAX;
    int s = INT_MAX;

    for (int j = 0; j < N; j++)
    {
        if (i == j)
            continue;
        if (g[i][j] <= f)
            s = f, f = g[i][j];
        else if (g[i][j] <= s && g[i][j] != f)
            s = g[i][j];
    }

    return s;
}

// Clona uma solucao para a final
void clone(int cPath[])
{
    for (int i = 0; i < N; i++)
        res[i] = cPath[i];
    res[N] = cPath[0];
}

// Recebe:
// o grafo
// O limite inferior
// o peso do caminho atual
// o nivel da pesquisa
// o caminho atual
void TSP_(int g[N][N], int cBound, int cWeight, int l, int cPath[])
{
    // Caso base
    // se o nivel for igual a N, percorremos todos os vertices uma vez
    if (l == N)
    {
        // Checa se no ultimo vertice do caminho, existe um vertice que volta para o primeiro
        // Permite a existencia do percurso
        if (g[cPath[l - 1]][cPath[0]] != 0)
        {
            // guarda o peso total da solucao
            int cRes = cWeight + g[cPath[l - 1]][cPath[0]];

            // atualiza o caminho final e o peso final
            if (cRes < weight)
            {
                clone(cPath);
                weight = cRes;
            }
        }
        return;
    }

    // Se ainda temos mais niveis, percorremos todos os vertices do nivel
    for (int i = 0; i < N; i++)
    {
        // Ver se o proximo vertice nao nao foi visitado e é valido
        if (g[cPath[l - 1]][i] != 0 && !visited[i])
        {
            int aux = cBound;
            cWeight += g[cPath[l - 1]][i];

            // Calcula os limites
            if (l == 1)
                cBound -= ((firstMin(g, cPath[l - 1]) + firstMin(g, i)) / 2);
            else
                cBound -= ((secondMin(g, cPath[l - 1]) + firstMin(g, i)) / 2);

            // Se o limite inferior for menor do que o peso, precisamos ir mais profundo

            if (cBound + cWeight < weight)
            {
                cPath[l] = i;
                visited[i] = true;

                // Percorre recursivo
                TSP_(g, cBound, cWeight, l + 1, cPath);
            }

            // Resetamos a iteracao atual e o vetor de visitados ate a posicao desejada
            cWeight -= g[cPath[l - 1]][i];
            cBound = aux;

            memset(visited, false, sizeof(visited));
            for (int j = 0; j <= l - 1; j++)
                visited[cPath[j]] = true;
        }
    }
}

void TSP(int g[N][N])
{
    // Calcula os limites para a raiz usando a formula da soma do primeiro menor + o segundo
    // Inicializa os vetores de visitados e o caminho
    int cPath[N + 1];
    int cBound = 0;
    memset(cPath, -1, sizeof(cPath));
    memset(visited, false, sizeof(visited));

    // Calculo dos limites
    for (int i = 0; i < N; i++)
        cBound += (firstMin(g, i) + secondMin(g, i));

    // arredonda o limite inferior para cima
    cBound = (cBound & 1) ? cBound / 2 + 1 : cBound / 2;

    // Marca o primeiro vertice como visitado e o vertex inicial
    visited[0] = true;
    cPath[0] = 0;

    // Chamada Recursiva
    TSP_(g, cBound, 0, 1, cPath);
}

int main()
{

    // O grafo em forma de uma matriz de adjascencias
    int graph[N][N] = {{0, 10, 15, 20},
                       {10, 0, 35, 25},
                       {15, 35, 0, 30},
                       {20, 25, 30, 0}};

    TSP(graph);

    cout << "TSP Branch and Bound: " << weight << endl;

    for (int i = 0; i <= N; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
}