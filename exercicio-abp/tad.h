// == TAD com estrutura e funcoes ==

// Estruturas:

struct TNodoA{
 int info;
 struct TNodoA *esq;
 struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;


// Funcoes:

/*
 Recebe endereco da raiz e chave a ser inserida, percorrendo a arvore
 e inserindo como folha a informacao passada e retornando o ponteiro atualizado
*/
pNodoA* insereArvore(pNodoA *a, int chave);

// Recebe ponteiro da arvore e percorre a mesma de forma pre-fixada a esquerda imprimindo infos
void preFixadoEsquerda(pNodoA *a);

// Funcao que recebe um ponteiro de arvore e percorre a mesma contando
// quantos nodos existem de forma recursiva
int contaNodosArvore(pNodoA *a);

// Recebe um ponteiro de arvore e sua info de nodo, bem como um nivel
// e percorre a arvore para dizer qual o nivel do nodo com a info passada
int retornaNivelNodo(pNodoA *a, int info, int nivel);

// Recebe ponteiro da arvore e percorre a mesma de forma pre-fixada a esquerda imprimindo
// chaves com tracos representando nivel dos nodos
void imprimeArvoreTracos(pNodoA *a);


