#include <stdio.h>
#include "tad.h"

int main() {
    pNodoA *arvoreA = NULL;
    pNodoA *arvoreB = NULL;

    int fatorArvoreA;
    int fatorArvoreB;

    arvoreA = insereArvore(arvoreA, 42);
    arvoreA = insereArvore(arvoreA, 15);
    arvoreA = insereArvore(arvoreA, 88);
    arvoreA = insereArvore(arvoreA, 6);
    arvoreA = insereArvore(arvoreA, 27);
    arvoreA = insereArvore(arvoreA, 20);
    arvoreA = insereArvore(arvoreA, 63);
    arvoreA = insereArvore(arvoreA, 94);
    arvoreA = insereArvore(arvoreA, 57);
    arvoreA = insereArvore(arvoreA, 71);

    arvoreB = insereArvore(arvoreB, 42);
    arvoreB = insereArvore(arvoreB, 15);
    arvoreB = insereArvore(arvoreB, 27);
    arvoreB = insereArvore(arvoreB, 20);

    printf("Arvore A:\n\n");
    Desenha(arvoreA, Altura(arvoreA));

    printf("\n\nArvore B:\n\n");
    Desenha(arvoreB, Altura(arvoreB));

    fatorArvoreA = FatorArvore(arvoreA);
    fatorArvoreB = FatorArvore(arvoreB);

    printf("\n\nFator da arvore A: %d", fatorArvoreA);
    printf("\n\nFator da arvore B: %d", fatorArvoreB);

    return 0;
}
