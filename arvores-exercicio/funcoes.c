#include "tad.h"
#include <string.h>

/*
 Recebe endereo da raiz e chave procurada. Se encontrar, devolve nodo encontrado,
 caso contr‡rio devolve nulo
*/
pNodoA* consultaABP(pNodoA *a, char chave) {
    while (a!=NULL){
        if (a->info == chave ) {
            return a; //achou retorna o ponteiro para o nodo
        } else {
            if (a->info > chave)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return NULL; //n‹o achou, retorna null
}

/*
 Recebe endereo da raiz e chave a ser inserida, percorrendo a arvore
 e inserindo como folha a informacao passada e retornando o ponteiro atualizado
*/
pNodoA* insereArvore(pNodoA *a, int ch) {
    if (a == NULL) {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = ch;
        a->esq = NULL;
        a->dir = NULL;
    } else {
        if (ch < a->info)
            a->esq = InsereArvore(a->esq,ch);
        else
            a->dir = InsereArvore(a->dir,ch);
    }

    return a;
}

pnodoA* encontraMaiorNodo(pnodoA* a) {
    if(a->esq && a->dir) {
        return encontraMaiorNodo(a->dir);
    }

    return a;
}


/*
 Recebe endereo da raiz e chave procurada. Se encontrar, remove e devolve nodo encontrado
 caso contr‡rio devolve null
*/
pnodoA* removeABP(pnodoA *a, int chave) {
    pnodoA nodo = consultaABP(a, chave);

    if(nodo) {
        // caso 01
        if(!nodo->esq && !nodo->dir) {
            nodo = NULL;
        // caso 03
        } else if(nodo->esq && nodo->dir) {
            nodo = encontraMaiorNodo(nodo->esq);
        // caso 02
        } else {
            if(nodo->esq && !nodo->dir)
                nodo = nodo->esq;
            else
                nodo = nodo->dir;
        }

        free(nodo);
    }

    return nodo;
}


