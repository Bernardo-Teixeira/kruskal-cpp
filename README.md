# Algoritmo de Kruskal em C++

Implementação do algoritmo de Kruskal para encontrar a **Árvore Geradora Mínima (AGM)**
de um grafo não direcionado e com pesos nas arestas.

Trabalho de Teoria dos Grafos, Ciência da Computação, Instituto Federal Goiano (Rio Verde - GO).
Autor: Bernardo Teixeira Cunha Silveira.

## Estruturas usadas (GrafoCC)

O código usa a lista de adjacência com pesos do `GrafoListaPeso.cpp` dos exemplos do GrafoCC,
com a mesma leitura e escrita do grafo:

```cpp
typedef vector<vector<pair<int,double>>> LP;
```

Como o Kruskal trabalha com grafos não direcionados, em `leituraGrafo` a aresta é guardada
nos dois sentidos (a linha que estava comentada no exemplo original).

Além disso foram acrescentados:

- uma lista de arestas `(peso, u, v)`, para ordenar as arestas por peso;
- uma estrutura **Union-Find** (conjuntos disjuntos) com compressão de caminho e união por
  altura (rank), usada para detectar ciclos (`raiz` e `altura`).

## Como funciona

1. Cada vértice começa em um conjunto próprio.
2. As arestas são ordenadas da menor para a maior.
3. Para cada aresta, se os dois vértices estão em conjuntos diferentes, a aresta entra na
   árvore e os conjuntos são unidos. Se estão no mesmo conjunto, a aresta formaria um ciclo
   e é descartada.
4. O algoritmo para quando tiver `n - 1` arestas. Se o grafo for desconexo, o resultado é uma
   floresta geradora mínima.

**Complexidade:** `O(E log E)`, que é equivalente a `O(E log V)`. A ordenação das arestas é
a parte que mais pesa.

## Como compilar e executar

```bash
g++ -std=c++11 -O2 -o kruskal kruskal.cpp
./kruskal < entrada.txt
```

## Formato da entrada

A primeira linha tem `n m` (número de vértices e de arestas). Depois vêm `m` linhas
`a b w`, com a aresta entre `a` e `b` e peso `w`. Os vértices são numerados de `0` a `n-1`.

Exemplo (salve como `entrada.txt`, que é o `inp.txt` do GrafoCC):

```
5 6
0 1 1.3
0 4 2.3
1 2 3.2
1 4 4.4
2 3 0.5
3 4 2.6
```

## Exemplo de saída

```
Arestas da Arvore Geradora Minima:
(2,3) w: 0.5
(0,1) w: 1.3
(0,4) w: 2.3
(3,4) w: 2.6
Custo total: 6.7
```

O programa imprime antes a lista de adjacência do grafo, e no final o total de vértices e de
arestas, como nos exemplos do GrafoCC.
