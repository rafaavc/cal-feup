/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
    if (n == 0)
        return 1;
	return n*factorialRecurs(n-1);
}

int factorialDinam(int n)
{
    unsigned factorials[n+1];
    factorials[0] = 1;

    for (unsigned i = 1; i <= n; i++) {
        factorials[i] = i*factorials[i-1];
    }
	return factorials[n];
}

/*
 * C)
 * A solução recursiva implica menos gasto temporal pois evita-se a repetição de trabalho,
 * sendo memorizadas as soluções parciais dos problemas.
 * A nível de gastos de memória, penso que tanto uma como a outra tenham os mesmos gastos (armazenam o mesmo número de números).
 */
