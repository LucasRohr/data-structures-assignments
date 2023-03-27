#include "tad.h"
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    int i,j;
    int grafo[max+1][max+1];
    int vis[max+1];
    int cores[max+1];


    //para inicializar o gráfo com 0
    for(i=1;i<=max;i++)
        for(j=1;j<=max;j++)
            grafo[i][j]=0;

    for (i=1;i<=max;i++)
        vis[i]=false; //inicializando vetor de vertices visitados

    for (i=1;i<=max;i++)
        cores[i]=0; //inicializando vetor de vertices visitados

    grafo[1][2]=1;
    grafo[2][1]=1;

    grafo[1][6]=1;
    grafo[6][1]=1;

    grafo[2][3]=1;
    grafo[3][2]=1;

    grafo[2][4]=1;
    grafo[4][2]=1;

    grafo[6][5]=1;
    grafo[5][6]=1;

    grafo[6][4]=1;
    grafo[4][6]=1;

    grafo[3][5]=1;
    grafo[5][3]=1;

    grafo[3][4]=1;
    grafo[4][3]=1;

    grafo[5][4]=1;
    grafo[4][5]=1;

    i = 4;

    puts("DFS\n\n");
    coloracaoDFS(grafo,i, vis, cores);


    for (i=1;i<=max;i++)
        vis[i]=false; //inicializando vetor de vertices visitados

    for (i=1;i<=max;i++)
        cores[i]=0; //inicializando vetor de vertices visitados

    puts("\n\nBFS\n\n");
    i = 4;

    coloracaoBFS(grafo, i, vis, cores);
}
