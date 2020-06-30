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

Complexidade temporal é ~ O(n^2).

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

```c++
algorithm(G, s) {
    for each v in V do
        dist(v) = DBL_MAX
        path(v) = NULL
        gas(v) = 0
        custo(v) = DBL_MAX
    
    custo(s) = s.preco * 10;
    gas(s) = 10;
    dist(s) = 0;
    Q = empty // min priority queue
    Q.insert(s)
    while(!Q.empty()) {
        v = Q.extractMin() // extracts the one with the least cost
        for each w in Adj(v) do
            if (gas(v) < weight(v, w) && custo(w) > custo(v) + v.preco * 10) {
                custo(w) = custo(v) + v.preco * 10
                gas(w) = gas(v) + 10 - weight(v, w)
                dist(w) = dist(v) + weight(v, w)
                path(w) = v
            } else if (gas(v) > weight(v, w) && custo(w) > custo(v)) {
                custo(w) = custo(v)
                gas(w) = gas(v) - weight(v, w)
                dist(w) = dist(v) + weight(v, w)
                path(w) = v
            } else if (gas(v) >= weight(v, w) && gas(v) - weight(v, w) >= gas(w) &&  custo(w) == custo(v) && dist(w) > dist(v) + weight(v, w))) {
                dist(w) = dist(v) + weight(v, w)
                path(w) = v
            }
    }
}
```
|        |  A | B(2) |  C | D(2) |  E |  F  |  G  |   -   |
|:------:|:--:|:----:|:--:|:----:|:--:|:---:|:---:|:-----:|
| proc A | 10 |  inf | 10 |  inf | 10 | inf | inf | custo |
|        | 10 |   0  |  2 |   0  |  3 |  0  |  0  |  gas  |
| proc C | 10 |  20  | 10 |  10  | 10 | inf | inf |       |
|        | 10 |   8  |  2 |   1  |  3 |  0  |  0  |       |
| proc D | 10 |  20  | 10 |  10  | 10 |  30 |  30 |       |
|        | 10 |   8  |  2 |   1  |  3 |  7  |  2  |       |
| proc E | 10 |  20  | 10 |  10  | 10 |  20 |  30 |       |
|        | 10 |   8  |  2 |   1  |  3 |  3  |  2  |       |
| proc B | 10 |  20  | 10 |  10  | 10 |  20 |  30 |       |
|        | 10 |   8  |  2 |   1  |  3 |  3  |  2  |       |
| proc F | 10 |  20  | 10 |  10  | 10 |  20 |  20 |       |
|        | 10 |   8  |  2 |   1  |  3 |  3  |  0  |       |
| proc G | 10 |  20  | 10 |  10  | 10 |  20 |  20 |       |
|        | 10 |   8  |  2 |   1  |  3 |  3  |  0  |       |

O caminho com menor custo será A -> C -> D -> F ->G

## c

Sim, A -> C -> D -> G -> C -> B -> D -> B -> A -> E -> F -> E -> D -> F -> G

# Exercício 3

## a

<img src="3a.png" width="300"/>
 
## b

?

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



