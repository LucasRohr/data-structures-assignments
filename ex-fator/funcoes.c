#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

// Recebe endereco da raiz e chave a ser inserida, percorrendo a arvore
// e inserindo como folha a informacao passada e retornando o ponteiro atualizado
pNodoA* insereArvore(pNodoA *a, int chave) {
    if (a == NULL) {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = chave;
        a->esq = NULL;
        a->dir = NULL;
    } else {
        if (chave < a->info)
            a->esq = insereArvore(a->esq, chave);
        else
            a->dir = insereArvore(a->dir, chave);
    }

    return a;
}

// Recebe ponteiro da arvore e percorre a mesma de forma pre-fixada a esquerda imprimindo
// chaves com tracos representando nivel dos nodos
void Desenha(pNodoA *a , int nivel) {
    int x;

    if (a !=NULL) {
        for (x = 1; x<=nivel; x++)
            printf("=");

        printf("%d \n", a->info);

        if (a->esq != NULL) Desenha(a->esq, nivel + 1);
        if (a->dir != NULL) Desenha(a->dir, nivel + 1);
    }
}

// Recebe um ponteiro de nodo e percorre a subarvore dele para dizer qual a altura do nodo
int Altura (pNodoA *a) {
    int Alt_Esq, Alt_Dir;

    if (a == NULL) {
        return 0;
    } else {
        Alt_Esq = Altura (a->esq);
        Alt_Dir = Altura (a->dir);

        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

// Recebe um ponteiro de nodo da arvore e retorna seu fator, ou seja, a diferenca das alturas de suas duas subarvores
int Fator(pNodoA *a) {
    if(a) {
        return abs(Altura(a->esq) - Altura(a->dir));
    }

    return 0;
}

// Recebe um ponteiro de nodo da arvore e percorre suas subarvorse retornando o fator da arvore
int FatorArvore(pNodoA *a) {
    if(!a) {
        return 0;
    }

    if(Fator(a->esq) > Fator(a)) {
        return FatorArvore(a->esq);
    }

    if(Fator(a->dir) > Fator(a)) {
        return FatorArvore(a->dir);
    }

    return Fator(a);
}



