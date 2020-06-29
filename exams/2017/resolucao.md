# Exercício 1

## a

```c++
alturaTotal = 0
larguraPrateleira = 0
alturaPrateleira = 0

for i in livros {
    larguraLivro = L[i]
    alturaLivro = A[i]

    if (larguraPrateleira + larguraLivro > LP) {
        // nova prateleira
        alturaTotal += alturaPrateleira
        larguraPrateleira = larguraLivro
        alturaPrateleira = alturaLivro
    } else if (i == livros[n-1]) {
        if (alturaLivro > alturaPrateleira) {
            alturaPrateleira = alturaLivro
        }
        alturaTotal += alturaPrateleira
    } else {
        larguraPrateleira += larguraLivro
        if (alturaLivro > alturaPrateleira) {
            alturaPrateleira = alturaLivro
        }
    }
}

return alturaTotal
```

A complexidade temporal do algoritmo é O(n), pois apenas existe um ciclo que percorre todos os livros.

Este algoritmo não é óptimo.

## b

Seguindo a sugestão:

- Começar pela colocação do último livro.

- Considerar Custo[i] o custo de colocação dos livros i...n, estando i no início de uma prateleira.

```c++
/*
Custo[i] = A[i], se i = n-1
Custo[i] = max(A[i], ..., A[n-1]), se L[i] + ... + L[n-1] <= LP e i < n
Custo[i] = max(A[i], ..., A[j-1]) + Custo[j], sendo j o livro que está no início da prateleira imediatamente abaixo da prateleira de i, se L[i] + ... + L[n-1] > LP e i < n
*/

somaL = 0
i = n-1; // contador global

for ( ; i > 0 && somaL + L[i] <= LP; i--) {
    if (i == n-1) {
        Custo[i] = A[i]
    } else {
        Custo[i] = max(A[i], Custo[i+1])
    }
    somaL += L[i]
}

for ( ; i > 0; i--) {
    j = i
    Custo[i] = A[i]
    somaL = L[i]
    for (j = i + 1; somaL + L[j] <= LP; i--) {
        Custo[i] = max(Custo[i], A[j])
        somaL += L[i]
    }
    Custo[i] = Custo[i] + Custo[j] // j terá o valor do livro que estará no início na prateleira imadiatamente abaixo de i
}
return Custo[0]
```

Complexidade de O(n^2).


# Exercício 2

## a

|        | A | B | C | D   | E   | F   | G   |
|:------:|:-:|:-:|---|-----|-----|-----|-----|
| init   | 0 | inf | inf | inf | inf | inf  | inf |
| proc A | 0 | 1 | 3 | inf | inf | 10  | inf |
| proc B | 0 | 1 | 2 | 8   | 6   | 10  | 3   |
| proc C | 0 | 1 | 2 | 8   | 5   | 10  | 3   |
| proc G | 0 | 1 | 2 | 8   | 5   | 10  | 3   |
| proc E | 0 | 1 | 2 | 7   | 5   | 7   | 3   |
| proc D | 0 | 1 | 2 | 7   | 5   | 7   | 3   |
| proc F | 0 | 1 | 2 | 7   | 5   | 7   | 3   |

Caminho mais curto de A a F: A -> B -> C -> E -> F

## b

```c++
// TODO
```

# Exercício 3

## a 

Pontos de articulação são os pontos que, quando removidos, tornam o grafo desconexo. Assim sendo, os pontos de articulação do grafo são:

- d - quando removido origina duas parted do grafo, sem caminho entre si (desconexas): a-c-f e b-e-g

## b



