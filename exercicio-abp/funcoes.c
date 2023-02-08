#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

/*
 Recebe endereco da raiz e chave a ser inserida, percorrendo a arvore
 e inserindo como folha a informacao passada e retornando o ponteiro atualizado
*/
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

// Recebe ponteiro da arvore e percorre a mesma de forma pre-fixada a esquerda imprimindo infos
void preFixadoEsquerda(pNodoA *a) {
    if (a!= NULL) {
        printf("%d\n",a->info);
        preFixadoEsquerda(a->esq);
        preFixadoEsquerda(a->dir);
    }
}

// Funcao que recebe um ponteiro de arvore e percorre a mesma contando
// quantos nodos existem de forma recursiva
int contaNodosArvore(pNodoA *a) {
    if(a) {
       return contaNodosArvore(a->esq) + contaNodosArvore(a->dir) + 1;
    }

    return 0;
}

// Recebe um ponteiro de arvore e sua info de nodo, bem como um nivel
// e percorre a arvore para dizer qual o nivel do nodo com a info passada
int retornaNivelNodo(pNodoA *a, int info, int nivel) {
    if (a == NULL) {
        return 1;
    } else {
        if (a->info == info) {
            return nivel;
        } else {
            if (a->info > info)
                return retornaNivelNodo(a->esq, info, nivel + 1);
            else
                return retornaNivelNodo(a->dir, info, nivel + 1);
        }
    }
}

// Recebe ponteiro da arvore e percorre a mesma de forma pre-fixada a esquerda imprimindo
// chaves com tracos representando nivel dos nodos
void imprimeArvoreTracosAux(pNodoA *a, pNodoA *raiz) {
    if (a!= NULL) {
        int i, nivel_nodo;

        nivel_nodo = retornaNivelNodo(raiz, a->info, 1);

        for(i = 0; i < nivel_nodo; i++) {
            printf("=");
        }

        printf("%d\n",a->info);

        imprimeArvoreTracosAux(a->esq, raiz);
        imprimeArvoreTracosAux(a->dir, raiz);
    }
}

// Chama a funcao auxiliar que recebe ponteiro da arvore e percorre
// a mesma de forma pre-fixada a esquerda imprimindo chaves com tracos representando nivel dos nodos
void imprimeArvoreTracos(pNodoA *a) {
    return imprimeArvoreTracosAux(a, a);
}
