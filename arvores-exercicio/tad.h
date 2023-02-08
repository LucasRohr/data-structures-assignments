
// == TAD com estrutura e funcoes ==

// Estruturas:

struct TNodoA{
 char info;
 struct TNodoA *esq;
 struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;


// Funcoes:

/*
 Recebe endereço da raiz e chave procurada. Se encontrar, devolve nodo encontrado,
 caso contrário devolve nulo
*/
pNodoA* consultaABP(pNodoA *a, char chave);

/*
 Recebe endereço da raiz e chave a ser inserida, percorrendo a arvore
 e inserindo como folha a informacao passada e retornando o ponteiro atualizado
*/
pNodoA* insereArvore(pNodoA *a, int ch);

/*
 Recebe endereço da raiz e chave procurada. Se encontrar, remove e devolve nodo encontrado
 caso contrário devolve null
*/
pnodoA* removeABP(pnodoA *a, int chave);
