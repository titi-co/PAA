#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

// Essa funcao assume que as sequencias X e Y estao ordenadas
int _medianaA(int X[], int Y[], int m, int n)
{
    // Indexadores
    // i é o index de X
    // j é o index de Y
    int i = 0;
    int j = 0;

    // Variavel auxiliar contador
    int c;
    int mA = -1, mB = -1;

    // Existem M + n elementos, a soma dos dois vetores
    // Se n + m é impar ou é par
    // Para o caso impar, a mediana esta no meio (m+n) / 2
    // Para o caso par.  a mediana será a media entre os elementos do index (m+n)/2 - 1 e (m+n) / 2

    // Mantenho 2 ponteiros, i e j
    // Comparo eles e incremento o index do menor elemento nessa instancia da iteracao

    // Caso impar
    if ((m + n) % 2 == 1)
    {

        // Sendo impar, ao terminar o laço, retorno o elemento
        for (c = 0; c <= (m + n) / 2; c++)
        {
            if (i != m && j != n)
                mA = (X[i] > Y[j]) ? Y[j++] : X[i++];

            else if (i < m)
                mA = X[i++];

            else
                mA = Y[j++];
        }

        // Mediana é o unico elemento central
        return mA;
    }

    // Caso par
    else
    {
        // No caso par, guardo em MB a iteracao anterior a ultima para tirar a meedia entre os elementos centrais
        for (c = 0; c <= (m + n) / 2; c++)
        {
            mB = mA;
            if (i != m && j != n)
                mA = (X[i] > Y[j]) ? Y[j++] : X[i++];

            else if (i < m)
                mA = X[i++];

            else
                mA = Y[j++];
        }

        // Mediana é a media dos elementos centrais
        return (mA + mB) / 2;
    }
}

// Calcula mediana de 2 elementos
int _m2(int x, int y)
{
    return (x + y) / 2;
}

// Calcula mediana de 3 elementos
int _m3(int x, int y, int z)
{
    return x + y + z - max(x, max(y, z)) - min(x, (min(y, z)));
}

// Calcula mediana de 4 elementos
int _m4(int x, int y, int z, int z1)
{
    int _max = max(x, max(y, max(z, z1)));
    int _min = min(x, min(y, min(z, z1)));

    return (x + y + z + z1 - _max - _min) / 2;
}

// Calcula mediana de 1 vetor
int _m0(int X[], int m)
{
    if (m == 0)
        return -1;
    if (m % 2 == 0)
        return (X[m / 2] + X[m / 2 - 1]) / 2;
    return X[m / 2];
}

// Assume que m é menor ou igual a n
// retorna -1 com ambos os vetores vazios
int _encontraMedianaB(int X[], int Y[], int m, int n)
{
    // Se o vetor X é vazio, retorna a mediana de Y
    if (m == 0)
        return _m0(Y, n);

    // Se X possui um unico elemento
    if (m == 1)
    {
        // Se Y tambem so possui um elemento, pego a mediana de X[0] e Y[0]
        // Unicos elementos do vetor
        if (n == 1)
            return _m2(X[0], Y[0]);

        // Se o vetor Y é impar
        // Aqui, X ainda possui so um elemento
        // Pego a mediana entre os tres elementos centrais de Y e po unico elemento de X
        if (n & 1)
            return _m2(Y[n / 2], _m3(X[0], Y[n / 2 - 1], Y[n / 2 + 1]));

        // Se vetor Y é par
        // A mediana vai ser ou elementos centrais de Y ou o unico de X
        return _m3(Y[n / 2], Y[n / 2 - 1], X[0]);
    }

    // se X possui 2 elemtnos
    else if (m == 2)
    {

        // Se Y tambem possui 2 elementos, faco a mediana desses 4
        if (n == 2)
            return _m4(X[0], X[1], Y[0], Y[1]);

        // Se Y é impar
        // A mediana sera o elemento do meio de Y
        // Ou sera o maior elemento dentre o primeiro de X, e anterior ao meio de Y
        // Ou sera o menor elemento dentre o segundo de X, e proximo ao meio de Y
        else if (n & 1)
            return _m3(Y[n / 2], max(X[0], Y[n / 2 - 1]), min(X[1], Y[m / 2 + 1]));

        // Se Y é par
        // A mediana sera os elementos do meio de Y
        // Ou sera o maior elemento dentre o primeiro de X, e anterior ao meio de Y
        // Ou sera o menor elemento dentre o segundo de X, e proximo ao meio de Y
        return _m4(Y[n / 2], Y[n / 2 - 1], max(X[0], Y[n / 2 - 2]), min(X[0], Y[n / 2 + 1]));
    }

    int iX = (m - 1) / 2;
    int iY = (n - 1) / 2;

    // Se o meio de X é menor que meio de Y
    // Mediana deve exister depois do meio de X e antes o meio de Y

    if (X[iX] <= Y[iY])
        return _encontraMedianaB(X + iX, Y, m / 2 + 1, n - iX);

    // Senao, ela existe antes do meio de X e depois do meio de Y
    return _encontraMedianaB(X, Y + iX, m / 2 + 1, n - iX);
}

int _medianaB(int X[], int Y[], int m, int n)
{
    // Essa funcao manda sempre o menor array como argumento correto na funcao
    if (m > n)
        return _encontraMedianaB(Y, X, n, m);

    return _encontraMedianaB(X, Y, m, n);
}

int main()
{

    // Sequencias ordenadas
    int X[] = {19};
    int Y[] = {15, 20, 25, 30};

    int m = sizeof(X) / sizeof(X[0]);
    int n = sizeof(Y) / sizeof(Y[0]);

    cout << "Mediana de complexidade O(M+N): " << _medianaA(X, Y, m, n) << endl;
    cout << "Mediana de complexidade O(log(max(m,n))): " << _medianaB(X, Y, m, n) << endl;
}