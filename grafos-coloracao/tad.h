#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#define max 8
#define true 1
#define false 0

void coloracaoDFS(int grafo[max+1][max+1], int v,   int vis[max+1], int cores[max + 1]);
void coloracaoBFS(int grafo[max+1][max+1], int v,   int vis[max+1], int cores[max + 1]);
void coloreVertice(int grafo[max+1][max+1], int v, int vis[max+1], int cores[max + 1]);
