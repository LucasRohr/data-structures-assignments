#include "tad.h"
#include "tad-arquivos.h"

#define TAM_STOPWORD 30
#define TAM_LINHA_STOPWORD 200
#define TAM_LINHA_TXT 150

#define ARQUIVO_STOPWORDS "stopwords.txt"

// == Funcoes de LSE ==

// Retorna valor default NULL como inicializador de um No
TipoPtNo* inicializaLista(void) {
    return NULL;
}

// Adiciona um novo No no comeco da lista e aponta o proximo No
// como o primeiro anterior
TipoPtNoLista* insereInicio(TipoPtNoLista* ptLista, char texto[]) {
    TipoPtNoLista *novo;

    novo = (TipoPtNoLista*) malloc(sizeof(TipoPtNoLista));

    novo->palavra = texto;
    novo->prox = ptLista;

    ptLista = novo;

    return novo;
}


// Adiciona um novo No no final da lista e aponta o proximo No
// como vazio, vai percorrendo os Nos para isso
TipoPtNoLista* insereFim(TipoPtNoLista* ptLista, char texto[]) {
    TipoPtNoLista *novo, *ptaux = ptLista;

    novo = (TipoPtNoLista*) malloc(sizeof(TipoPtNoLista));

    novo->palavra = texto;
    novo->prox = NULL;

    if(ptaux) {
        for(ptaux = ptLista; ptaux->prox; ptaux = ptaux->prox) {
            ptaux->prox = novo;
        }
    } else {
        ptLista = novo;
    }

    return ptLista;
}


// Busca em uma lista de Nos um dado a ser pesquisado, retornando o mesmo
// se achar ou NULL caso nao
TipoPtNoLista* consultaLista(TipoPtNoLista* ptLista, char palavra[]) {
    TipoPtNoLista *ptaux = ptLista; //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux !=NULL && (strcmp(ptaux->palavra, palavra))) {
        ptaux = ptaux->prox;
    }

    // Pode retornar NULL ou o valor encontrado
    return ptaux;
}



// == Funcoes para manipulacao de linhas de string ==



TipoPtNoLista* separaStringPorSeparadores(TipoPtNoLista* ptLista, char texto[]) {
  char textoSaida[];
  char separadores[] = " 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_";

  textoSaida = strtok(texto, separadores);

  ptLista = insereInicio(ptLista, textoSaida);

  while (textoSaida != NULL) {
    ptLista = insereFim(ptLista, textoSaida);

    pch = strtok (NULL, " ,.-");
  }

  return ptLista;
}


void tornaTextoLowerCase(char texto[]) {
    int i;

    for(i = 0; texto[i]; i++){
      texto[i] = tolower(texto[i]);
    }
}


TipoPtNoLista* lerStopWords(char nomeArquivo[]) {
    int abriuArquivo;
    char linha_arquivo[TAM_LINHA_STOPWORD];

    TipoPtNoLista* listaStopwords = inicializaLista();

    abriuArquivo = abrirArquivo(arq);

    if (abriuArquivo) {
        linha_arquivo = lerLinha(linha_arquivo, TAM_STOPWORD, arq);

        listaStopwords = insereInicio(listaStopwords, linha_arquivo);

        while(!feof(arq)) {
            linha_arquivo = lerLinha(linha_arquivo, TAM_STOPWORD, arq);
            listaStopwords = insereFim(listaStopwords, linha_arquivo);
        }
    }

    fclose(arq);

    return listaStopwords;
}


//  == Funcoes base para AVL

// Retorna maior altura
int maior(int a, int b){
    return (a > b) ? a : b;
}


// Dado um no de arvore, retorna sua altura
int alturaNo(pNodoA *a){
    if(a == NULL)
        return -1;
    else
        return a->altura;
}


// Retorna o fator de balanceamento de um nodo
int fatorNo(pNodoA *a){
    if(no) {
        return abs(alturaNo(a->esq) - alturaNo(a->dir));
    }

    return 0;
}


// Realiza um rotacao a esquerda dado o nodo da arvore
pNodoA* rotacaoEsquerda(pNodoA *a){
    pNodoA *y, *f;

    y = a->dir; // y aponta para a subárvore direita da raiz a
    f = y->esq; // f aponta para o filho esquerdo de y

    y->esq = a; // o filho esquerdo de y passa a ser a raiz a
    a->dir = f; // o filho direito de a passa a ser f

    // recalcula a altura dos nós que foram movimentados
    a->altura = maior(alturaNo(a->esq), alturaNo(a->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}



// Realiza um rotacao a direita dado o nodo da arvore
pNodoA* rotacaoDireita(pNodoA *a){
    pNodoA *y, *f;

    y = a->esq; // y aponta para a subárvore esquerda da raiz a
    f = y->dir; // f aponta para o filho direito de y

    y->dir = a; // o filho direito de y passa a ser a raiz a
    r->esq = f; // o filho esquerdo de a passa a ser f

    // recalcula a altura dos nós que foram movimentados
    a->altura = maior(alturaNo(a->esq), alturaNo(a->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}


// Efetua a rotacao dupla direita fazendo primeiro rotacao simples esquerda e depois direita
pNodoA* rotacaoDuplaDireita(pNodoA *a){
    a->esq = rotacaoEsquerda(a->esq);

    return rotacaoDireita(a);
}

// Efetua a rotacao dupla esquerda fazendo primeiro rotacao simples direita e depois esquerda
pNodoA* rotacaoDuplaEsquerda(pNodoA *a){
    a->dir = rotacaoDireita(a->dir);

    return rotacaoEsquerda(a);
}


// Funcao que usa das rotacoes para balencear a AVL apos uma insercao ou remoca na mesma
pNodoA* balancear(pNodoA *a){
    int fator = fatorNo(a);

    // Rotação à esquerda
    if(fator < -1 && fatorNo(a->dir) <= 0)
        a = rotacaoEsquerda(a);

    // Rotação à direita
    else if(fator > 1 && fatorNo(a->esq) >= 0)
        a = rotacaoDireita(a);

    // Rotação dupla à esquerda
    else if(fator > 1 && fatorNo(a->esq) < 0)
        a = rotacaoDuplaDireita(a);

    // Rotação dupla à direita
    else if(fator < -1 && fatorNo(a->dir) > 0)
        a = rotacaoDuplaEsquerda(a);

    return a;
}

// Recebe ponteiro da arvore e encontra palavra passado na mesma
pNodoA* consultaAVL(pNodoA *arvore, char palavra[]) {
    while (arvore!=NULL){
        if (arvore->palavra == palavra) {
            return arvore;
        } else {
            if (arvore->palavra > palavra)
                arvore = arvore->esq;
            else
                arvore = arvore->dir;
        }
    }

    return NULL;
}

// Cria um novo no da AVL e retorna o mesmo
pNodoA* criaNo(char palavra[]){
    pNodoA *novo = malloc(sizeof(pNodoA));

    if(novo){
        novo->palavra = palavra;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    }

    return novo;
}


// Recebe ponteiro da arvore e palavra, inserindo a palavra na mesma usando do balanceamento em AVL
void insereNodoAVL(pNodoA *arvore, char palavra[]) {
    if(arvore == NULL) // árvore vazia
        return criaNo(palavra);
    else{ // inserção será à esquerda ou à direita
        if(strcmp(palavra, a->palavra) < 0)
            arvore->esq = insereNodoAVL(arvore->esq, palavra);
        else if(strcmp(palavra, a->palavra) > 0)
            arvore->dir = insereNodoAVL(arvore->dir, palavra);
        else
            printf("\nErro de insercao\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    arvore->altura = maior(alturaNo(arvore->esq), alturaNo(arvore->dir)) + 1;

    // verifica a necessidade de rebalancear a árvore
    arvore = balancear(arvore);

    return arvore;
}


// == Funcoes especificas para a resolucao do problema do trabalho ==


// Dado ponteiro de AVL e uma palavra, verifica se a mesma ainda nao foi inserida
// e nao eh uma stopword para inserir a palavra na AVL
void inserePalavraAVL(pNodoA *arvore, char palavra[]) {
    TipoPtNoLista *listaStopwords = lerStopWords(ARQUIVO_STOPWORDS);

    TipoPtNoLista *palavraStopword = consultaLista(listaStopwords, palavra);
    pNodoA *nodoExistente = consultaAVL(arvore, palavra);

    if(!palavraStopword && !nodoExistente) {
        insereNodoAVL(arvore, palavra);
    }
}


// Dado nome de arquivo e ponteiro de arvore, percorre cada linha do arquivo de texto
// tornando cada caractere minusculo e sem separadores, inserindo cada palavra na AVL
// conforme regras da funcao auxiliar chamada
pNodoA* lerArquivoTexto(char nomeArquivo[], pNodoA *arvore) {
    int abriuArquivo;
    char linha_arquivo[TAM_LINHA_STOPWORD];
    TipoPtNoLista* listaPalavrasAtual = InicializaLista();

    abriuArquivo = abrirArquivo(arq);

    if (abriuArquivo) {
        while(!feof(arq)) {
            linha_arquivo = lerLinha(linha_arquivo, TAM_LINHA_TXT, arq);

            tornaTextoLowerCase(linha_arquivo);
            listaPalavrasAtual = separaStringPorSeparadores(listaPalavrasAtual, linha_arquivo);

            while(listaPalavrasAtual->prox) {
                inserePalavraAVL(arvore, listaPalavrasAtual->palavra);
            }
        }
    }

    fclose(arq);
}





