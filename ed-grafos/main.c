#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

void main() {
    int grafo[TAM_MATRIZ][TAM_MATRIZ] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0}
    };

    int visitados[TAM_MATRIZ] = {0, 0, 0, 0, 0, 0, 0, 0};

    TipoDFila *fila;

    fila = InicializaFila(fila);

    // DFS

    printf("== Depth First Search ==\n\n");

    printf("* Inicio no vertice 1: \n\n");

    dfs(grafo, 0, visitados);
    memset(visitados, 0, TAM_MATRIZ * sizeof(int));

    printf("\n\n* Inicio no vertice 3: \n\n");

    dfs(grafo, 2, visitados);
    memset(visitados, 0, TAM_MATRIZ * sizeof(int));

    printf("\n\n* Inicio no vertice 5 \n\n");

    dfs(grafo, 4, visitados);
    memset(visitados, 0, TAM_MATRIZ * sizeof(int));

    // BFS

    printf("\n\n\n== Breadth First Search ==\n\n");

    printf("* Inicio no vertice 1: \n\n");

    bfs(grafo, 0, visitados, fila);
    memset(visitados, 0, TAM_MATRIZ * sizeof(int));
    fila = InicializaFila(fila);

    printf("\n\n* Inicio no vertice 3: \n\n");

    bfs(grafo, 2, visitados, fila);
    memset(visitados, 0, TAM_MATRIZ * sizeof(int));
    fila = InicializaFila(fila);

    printf("\n\n* Inicio no vertice 5: \n\n");

    bfs(grafo, 4, visitados, fila);
    memset(visitados, 0, TAM_MATRIZ * sizeof(int));
    fila = InicializaFila(fila);
}
