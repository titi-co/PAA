#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap(char *s, int a, int b)
{
    char aux = s[a];
    s[a] = s[b];
    s[b] = aux;
}

void permute(char *s, int b, int e)
{
    // Caso base
    if (b == e)
        printf("%s\n", s);
    else
    {
        // Sao feitas "e" permutações
        for (int i = b; i <= e; i++)
        {
            swap(s, b, i);

            permute(s, b + 1, e);

            // backtracking
            swap(s, b, i);
        }
    }
}

int main()
{
    char dataSet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int n;
    do
    {
        printf("Digite até qual n letra do alfabeto deseja combinar: ");
        scanf("%d", &n);

        if (n <= 0 || n > 26)
            printf("Digite um tamanho valido, ou seja, de 1 até 26!\n\n");
    } while (n <= 0 || n > 26);

    char *strSet = (char *)malloc(n * sizeof(char));
    strncpy(strSet, dataSet, n);

    int size = strlen(strSet);
    printf("Combinações: \n");
    permute(strSet, 0, size - 1);
}