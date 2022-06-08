#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> toArraySequence;

// Usando o quicksort para ordenacao consigo um custo de Θ(nlog(n)) e depois so faco o acesso a ultima posicao
// Achei essa forma mais eficiente, considerando que pesquisar um por um pelo maior não seria bom

// Inverte duas posicoes do vetor
void swap(int i, int j)
{
  int k = toArraySequence[i];
  toArraySequence[i] = toArraySequence[j];
  toArraySequence[j] = k;
}

// Particiona o vetor com a estrategia divide and conquer
int particiona(int begin, int end)
{
  int i = begin;

  for (int j = begin; j < end; j++)
  {

    // elemento menor ou igual ao pivo
    if (toArraySequence[j] <= toArraySequence[end])
    {
      swap(i++, j);
    }
  }
  swap(i, end);

  return i;
}

// Faz a recursao do quick sort
void quicksort(int begin, int end)
{

  if (begin >= end)
    return;

  int pivo = particiona(begin, end);

  quicksort(begin, pivo - 1);
  quicksort(pivo + 1, end);
}

int main()
{

  // Crio a sequencia
  string sequence = "10/5/100/60/90/1";

  // Preparo a sequencia para a stream, substituindo a / pelo espaco
  replace(sequence.begin(), sequence.end(), '/', ' ');

  stringstream ss(sequence);
  int aux;

  // Adiciono no meu vetor de inteiro todos os numeros em string ja separados
  while (ss >> aux)
  {
    toArraySequence.push_back(aux);
  }

  // Para encontrar o maior valor, ordeno o vetor com o quicksort
  // Dessa forma, evito a busca sequencial por esse valor ja que no vetor ordenado ele estaria na ultima posicao
  quicksort(0, toArraySequence.size() - 1);

  cout << "Maior elemento é: " << toArraySequence[toArraySequence.size() - 1];
}