
// == TAD com estrutura e funcoes ==

// Estruturas:

struct TNodoA{
 int info;
 struct TNodoA *esq;
 struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;


// Funcoes:


// Recebe endereco da raiz e chave a ser inserida, percorrendo a arvore
// e inserindo como folha a informacao passada e retornando o ponteiro atualizado
pNodoA* insereArvore(pNodoA *a, int chave);

// Recebe ponteiro da arvore e percorre a mesma de forma pre-fixada a esquerda imprimindo
// chaves com tracos representando nivel dos nodos
void Desenha(pNodoA *a, int nivel);

// Recebe um ponteiro de nodo e percorre a subarvore dele para dizer qual a altura do nodo
int Altura(pNodoA *a);

// Recebe um ponteiro de nodo da arvore e retorna seu fator, ou seja, a diferenca das alturas de suas duas subarvores
int Fator(pNodoA *a);

// Recebe um ponteiro de nodo da arvore e percorre suas subarvorse retornando o fator da arvore
int FatorArvore(pNodoA *a);

