# Exercício 1

## a

```c++
valorMaximo = 0;
lastPos = -1;

for (i = 0; pos[i] > 0; i++) {
    if (abs(pos[i] - lastPos) >= 5 || lastPos == -1) {
        lastPos = pos[i]
        valorMaximo += valor[i]
    }
}

return valorMaximo
```

O algoritmo tem complexidade O(n), corre uma vez para cada posição.

Não é óptimo pois, por exemplo, para: 

- pos[1] = 94, pos[2] = 95, pos[3] = 100
- custo[1] = 1, custo[2] = 6, custo[3] = 4

este algoritmo obtém a solução 5, (pos[1] e pos[3]), enquanto que a solução óptima seria 10.


## b

Considerando e[j] como sendo um vetor que guarda o local mais próximo, no sentido sul, de j, tal que pos[e[j]] <= pos[j] - 5 (como é no sentido sul pos[e[j]] será < pos[j]).

Considerando valorTotal[i], sendo i o local a considerar (valorTotal[0] = valor[0]):
- valorTotal[i] = valor[i], se i == 0
- valorTotal[i] = max(valor[0], ..., valor[i]), se pos[i] - pos[0] < 5
- valorTotal[i] = max(valor[i] + valorTotal[e[i]], ..., valor[e[i] -1] + valorTotal[e[e[i]-1]]), se pos[i] - pos[0] >= 5

seja **n** o tamanho do vetor pos[]

```c++
for (i = 0; i < n; i++) {
    if (i == 0) {
        valorTotal[i] = valor[i]
    } else if (pos[i] - pos[0] < 5) {
        valorTotal[i] = 0
        for (j = 0; j <= i; j++) {
            valorTotal[i] = max(valorTotal[i], valor[j])
        }
    } else {
        valorTotal[i] = 0
        for (j = i; j < e[i]; j++) {
            valorTotal[i] = max(valorTotal[i], valor[j] + valorTotal[e[j]])
        }
    }
}

return valorTotal[n-1]
```

# Exercício 2

## a

Dijkstra:

|        | A | B | C | D   | E   | F   | G   |
|:------:|:-:|:-:|:---:|:---:|:---:|:---:|:---:|
| init   | 0 | inf | inf | inf | inf | inf  | inf |
| proc A | 0 | inf | 8 | inf | 7 | inf  | inf |
| proc E | 0 | inf | 8 |  10  | 7   | 17 | inf   |
| proc C | 0 | 12 | 8 | 9   | 7   | 17  | inf   |
| proc D | 0 | 10 | 8 | 9   | 7   |  13  |  18  |
| proc B | 0 | 10 | 8 |  9 |  7  |  13  | 18   |
| proc F | 0 | 10 | 8 | 9   | 7   | 13   |  16  |
| proc G | 0 | 10 | 8 | 9   | 7   | 13   | 16   |

Caminho mais curto de A a G: A -> C -> D -> F -> G

## b


## c


# Exercício 3

## a


## b


# Exercício 4

## a

## b

## c


# Exercício 5

## a

## b

## c


# Exercício 6

## a

## b



