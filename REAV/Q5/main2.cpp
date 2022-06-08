#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> toArraySequence;

// Abordagem Gulosa
// Custo O(2n) sendo n o numero de elementos da expressao
int main()
{
    string expression = "10/5/100/10000/90/1";

    replace(expression.begin(), expression.end(), '/', ' ');

    stringstream ss(expression);
    int aux;
    // Adiciono no meu vetor de inteiro todos os numeros em string ja separados
    while (ss >> aux)
    {
        toArraySequence.push_back(aux);
    }

    int max = INT_MIN;
    int div;
    // Para cada posicao do vetor, faz a divisao com a proxima posicao
    // Caso a divisao seja maior, guardo
    for (int i = 0; i < toArraySequence.size() - 1; i++)
    {
        div = (toArraySequence[i] / toArraySequence[i + 1]);
        if (div > max)
            max = div;
    }

    cout << max;
}