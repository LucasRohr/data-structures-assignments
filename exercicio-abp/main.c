#include <stdio.h>
#include "tad.h"

int main() {
    pNodoA *arvore = NULL;
    int total_nodos = 0;

    arvore = insereArvore(arvore, 8);
    arvore = insereArvore(arvore, 4);
    arvore = insereArvore(arvore, 9);
    arvore = insereArvore(arvore, 2);
    arvore = insereArvore(arvore, 6);
    arvore = insereArvore(arvore, 1);

    printf("Impressao do caminhamento pre-fixado a esquerda:\n\n");
    preFixadoEsquerda(arvore);
    printf("\n\n");

    total_nodos = contaNodosArvore(arvore);

    printf("Total de nodos eh: %d\n\n", total_nodos);

    printf("Impressao com niveis do caminhamento pre-fixado a esquerda:\n\n");
    imprimeArvoreTracos(arvore);

    return 0;
}
