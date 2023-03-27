#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

// Funcao que dado grafo, vertice, vetor de visitados e cores, atribui cor para vertice e printa ela
void coloreVertice(int grafo[max+1][max+1], int v, int vis[max+1], int cores[max + 1]) {
    int w, cor = 1;

    for(w = 1; w <= max ; w++) {
        if ((grafo[v][w] == 1) && (vis[w] == true) && cores[w] == cor) {
            cor = cor + 1;
            w = 1;
        }
    }

    cores[v] = cor;

    printf("%d - cor %d\n", v, cores[v]);
}

void coloracaoDFS(int grafo[max+1][max+1], int v, int vis[max+1], int cores[max + 1]) {
    int w;

    vis[v]= true;

    coloreVertice(grafo, v, vis, cores);

    for(w = 1; w <= max ; w++)    //percorre os vértices adjacentes a v
      if ((grafo[v][w] == 1) && (vis[w] == false))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
         coloracaoDFS(grafo, w, vis, cores); //chamada recursiva para o vértice adjacente a v
}



void coloracaoBFS(int grafo[max+1][max+1], int v, int vis[max+1], int cores[max + 1]) {
    int w;
    TipoFila *FV;

    FV = cria_fila();
    FV = insere(FV,v);
    vis[v]= true;

    while (!vazia(FV)) {
       v = removeFila(&FV);

       coloreVertice(grafo, v, vis, cores);

       for(w = 1; w<=max ; w++)    //percorre os vértices adjacentes a v
          if ((grafo[v][w]== 1) && (vis[w]==false))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
          {
              FV = insere(FV,w);
              vis[w]= true;
           }

    }
}



