#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "tad.h"
#include "tad-arquivos.h"

#define TAM_STOPWORD 30
#define TAM_LINHA_STOPWORD 200
#define TAM_LINHA_TXT 150
#define TAM_SEPARADORES 40

#define ARQUIVO_STOPWORDS "stopwords.txt"


// == Funcoes de LSE ==

// Usadas para manipular listas com encadeamento simples


// Retorna valor default NULL como inicializador de um No
TipoPtNoLista* inicializaLista(void) {
    return NULL;
}

// Adiciona um novo No no comeco da lista e aponta o proximo No
// como o primeiro anterior
TipoPtNoLista* insereInicio(TipoPtNoLista* ptLista, char texto[]) {
    TipoPtNoLista *novo;

    novo = (TipoPtNoLista*) malloc(sizeof(TipoPtNoLista));

    strcpy(texto, novo->palavra);
    novo->prox = ptLista;

    ptLista = novo;

    return novo;
}


// Adiciona um novo No no final da lista e aponta o proximo No
// como vazio, vai percorrendo os Nos para isso
TipoPtNoLista* insereFim(TipoPtNoLista* ptLista, char texto[]) {
    TipoPtNoLista *novo, *ptaux = ptLista;

    novo = (TipoPtNoLista*) malloc(sizeof(TipoPtNoLista));

    strcpy(texto, novo->palavra);
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

// Usadas para manipular strings, no caso, linhas de texto provenientes de arquivos texto
// para preparar as palavras a serem inseridas em AVL


// Funcao que dado ponteiro de LSE e um texto, separa o texto em palavras na LSE
// atraves dos separadores informados para o trabalho
TipoPtNoLista* separaStringPorSeparadores(TipoPtNoLista* ptLista, char texto[]) {
  char *textoSaida;
  char separadores[TAM_SEPARADORES] = " 0123456789-.,&*%\?!;/'@\"$#=~><()][}{:\n\t_";

  // Primeiro split dado na string de texto
  textoSaida = strtok(texto, separadores);

  // Bota primeira palavra separada no comeco da LSE
  ptLista = insereInicio(ptLista, textoSaida);

  while (textoSaida != NULL) {
    // Insere proxima palavra no fim da lista
    ptLista = insereFim(ptLista, textoSaida);

    // Atualiza texto de saida com a proxima palavra separada
    textoSaida = strtok(NULL, separadores);
  }

  return ptLista;
}

// Dado um texto, torna todo caractere lower case
void tornaTextoLowerCase(char texto[]) {
    int i;

    for(i = 0; texto[i]; i++){
      texto[i] = tolower(texto[i]);
    }
}

// Dado um nome de arquivo de stopwords, le o arquivo e adiciona cada palavra
// em uma LSE para uso na insercao de palavras na AVL
TipoPtNoLista* lerStopWords(FILE *arq, char nomeArquivo[]) {
    int abriuArquivo;
    char linha_arquivo[TAM_LINHA_STOPWORD]; // linha a ser lida do arquivo

    TipoPtNoLista* listaStopwords = inicializaLista(); // inicializa a LSE

    abriuArquivo = abrirArquivo(arq, nomeArquivo); // abre arquivo

    if (abriuArquivo) {
        // Le a linha do arquivo e armazena
        fgets(linha_arquivo, TAM_STOPWORD, arq);

        // Insere a primeira stopword no comeco da LSE
        listaStopwords = insereInicio(listaStopwords, linha_arquivo);

        // Enquanto o arquivo nao acaba, le uma linha (stopword) e adiciona no fim da LSE
        while(!feof(arq)) {
            fgets(linha_arquivo, TAM_STOPWORD, arq);
            listaStopwords = insereFim(listaStopwords, linha_arquivo);
        }
    }

    fclose(arq);

    return listaStopwords;
}


//  == Funcoes base para AVL ==

// Usadas como auxiliares do processo de leitura e comparacao dos textos


// Retorna maior altura entre duas de um nodo
int maior(int a, int b) {
    return (a > b) ? a : b;
}


// Dado um no de arvore, retorna sua altura, armazenada no nodo
int alturaNo(pNodoA *a) {
    if(a == NULL)
        return -1;
    else
        return a->altura;
}


// Retorna o fator de balanceamento de um nodo, podendo ser valor negativo
int fatorNo(pNodoA *a) {
    if(a) {
        return alturaNo(a->esq) - alturaNo(a->dir);
    }

    return 0;
}


// Realiza um rotacao a esquerda dado o nodo da AVL
pNodoA* rotacaoEsquerda(pNodoA *a) {
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



// Realiza um rotacao a direita dado o nodo da AVL
pNodoA* rotacaoDireita(pNodoA *a) {
    pNodoA *y, *f;

    y = a->esq; // y aponta para a subárvore esquerda da raiz a
    f = y->dir; // f aponta para o filho direito de y

    y->dir = a; // o filho direito de y passa a ser a raiz a
    a->esq = f; // o filho esquerdo de a passa a ser f

    // recalcula a altura dos nós que foram movimentados
    a->altura = maior(alturaNo(a->esq), alturaNo(a->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}


// Efetua a rotacao dupla direita fazendo primeiro rotacao simples esquerda e depois direita
pNodoA* rotacaoDuplaDireita(pNodoA *a) {
    a->esq = rotacaoEsquerda(a->esq);

    return rotacaoDireita(a);
}

// Efetua a rotacao dupla esquerda fazendo primeiro rotacao simples direita e depois esquerda
pNodoA* rotacaoDuplaEsquerda(pNodoA *a) {
    a->dir = rotacaoDireita(a->dir);

    return rotacaoEsquerda(a);
}


// Funcao que usa das rotacoes para balencear a AVL apos uma insercao ou remoca na mesma
pNodoA* balancear(pNodoA *a) {
    int fator = fatorNo(a); // Busca fator do nodo

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
pNodoA* consultaAVL(pNodoA *a, char palavra[]) {
    if (a==NULL) {
        return NULL;
    } else {
        // Se encontrou a palavra, retorna o nodo
        if (strcmp(a->palavra, palavra) == 0) {
            return a;
        } else {
            // Se palavra do nodo atual for maior, vai para a esquerda procurar
            if (strcmp(a->palavra, palavra) > 0)
                return consultaAVL(a->esq, palavra);
            // Senao, vai para a direita
            else
                return consultaAVL(a->dir, palavra);
        }
    }
}

// Cria um novo no da AVL e retorna o mesmo
pNodoA* criaNo(char palavra[]) {
    pNodoA *novo = malloc(sizeof(pNodoA));

    if(novo){
        strcpy(palavra, novo->palavra);
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    }

    return novo;
}


// Recebe ponteiro da arvore e palavra, inserindo a palavra na mesma usando do balanceamento em AVL
pNodoA* insereNodoAVL(pNodoA *arvore, char palavra[]) {
    // Se arvore está vazia, cria um no
    if(arvore == NULL) {
        return criaNo(palavra);
    } else {
        // Se palavra menor que a do nodo atual, insere na esquerda
        if(strcmp(palavra, arvore->palavra) < 0)
            arvore->esq = insereNodoAVL(arvore->esq, palavra);
        // Se for maior, insere a direita
        else if(strcmp(palavra, arvore->palavra) > 0)
            arvore->dir = insereNodoAVL(arvore->dir, palavra);
        else
            printf("\nErro de insercao\n");
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    arvore->altura = maior(alturaNo(arvore->esq), alturaNo(arvore->dir)) + 1;

    // Verifica a necessidade de rebalancear a árvore e balanceia se preciso
    arvore = balancear(arvore);

    return arvore;
}


// == Funcoes especificas para a resolucao do problema do trabalho ==


// Dado ponteiro de AVL e uma palavra, verifica se a mesma ainda nao foi inserida
// e nao é uma stopword para inserir a palavra na AVL
void inserePalavraAVL(pNodoA *arvore, char palavra[]) {
    FILE *arqStopwords = NULL;

    TipoPtNoLista *listaStopwords = lerStopWords(arqStopwords, ARQUIVO_STOPWORDS); // busca stopwords

    TipoPtNoLista *palavraStopword = consultaLista(listaStopwords, palavra); // busca palavra na lista de stopwords
    pNodoA *nodoExistente = consultaAVL(arvore, palavra); // procura se palavra ja existe na AVL

    // Se a palavra nao é stopword e ainda nao foi inserida (é distinta), adiciona na AVL
    if(!palavraStopword && !nodoExistente) {
        insereNodoAVL(arvore, palavra);
    }
}


// Dado ponteiro de arquivo e ponteiro de arvore, percorre cada linha do arquivo de texto
// tornando cada caractere minusculo e sem separadores, inserindo cada palavra na AVL
// conforme regras da funcao auxiliar chamada
pNodoA* converterArquivoTextoParaAVL(FILE *arq, char nomeArq[], pNodoA *arvore) {
    int abriuArquivo;
    char linha_arquivo[TAM_LINHA_STOPWORD]; // linha do arquivo a ser lida
    TipoPtNoLista* listaPalavrasAtual = inicializaLista(); // LSE para armazenar as palavras da linha lida

    abriuArquivo = abrirArquivo(arq, nomeArq); // abre arquivo

    if (abriuArquivo) {
        // Enquanto o arquivo nao acabar
        while(!feof(arq)) {
            fgets(linha_arquivo, TAM_LINHA_TXT, arq); // le a linha

            tornaTextoLowerCase(linha_arquivo); // deixa todos os caracteres em caixa baixa
            listaPalavrasAtual = separaStringPorSeparadores(listaPalavrasAtual, linha_arquivo); // separa palavras por separadores

            // Enquanto houverem palavras da linha atual na LSE
            while(listaPalavrasAtual->prox) {
                // Verifica e insere palavra (se for o caso) na AVL
                inserePalavraAVL(arvore, listaPalavrasAtual->palavra);
            }
        }
    }

    fclose(arq);

    return arvore;
}


// Funcao que recebe um ponteiro de arvore e percorre a mesma contando
// quantos nodos existem de forma recursiva (conta palavras distintas pois nao sao inseridas palavras repetidas)
int contaPalavrasDistintas(pNodoA *a) {
    if(a) {
       return contaPalavrasDistintas(a->esq) + contaPalavrasDistintas(a->dir) + 1;
    }

    return 0;
}

// Dado ponteiros para duas AVLs, compara quantas palavras em comum existem entre ambas arvores
int contaPalavrasDistintasInterseccao(pNodoA *a1, pNodoA *a2) {
    pNodoA* nodoPalavraA2; // declaracao de nodo da palavra que pode ou nao existir na AVL 2

    // Se nao houver AVL 1, retorna 0
    if (!a1) {
        return 0;
    }

    // Se existe AVL 2, continua
    if(a2) {
        nodoPalavraA2 = consultaAVL(a2, a1->palavra); // busca palavra atual da AVL 1 na AVL 2

        // Se existe a palavra na AVL 2, soma 1 no total e conta as demais palavras de forma recursiva
        if(nodoPalavraA2) {
            return contaPalavrasDistintasInterseccao(a1->esq, a2) + contaPalavrasDistintasInterseccao(a1->dir, a2) + 1;
        // Senao, apenas conta as demais palavras de forma recursiva sem somar 1
        } else {
            return contaPalavrasDistintasInterseccao(a1->esq, a2) + contaPalavrasDistintasInterseccao(a1->dir, a2);
        }
    }

    // Retorna 0 como retorno base
    return 0;
}

// Dadas duas AVLs e nomes de dois arquivos, calcula a similaridade de Jaccard para elas
void calculaJaccard(pNodoA *a1, char nomeArq1[], pNodoA *a2, char nomeArq2[]) {
    int totalPalavrasDistintasA1 = contaPalavrasDistintas(a1); // total de palavras distintas na AVL 1
    int totalPalavrasDistintasA2 = contaPalavrasDistintas(a2); // total de palavras distintas na AVL 2

    int totalPalavrasInterseccao = contaPalavrasDistintasInterseccao(a1, a2); // total de palavras em comum

    // Calcula a similaridade conforme expressao da mesma
    int totalUniaoPalavras = (totalPalavrasDistintasA1 + totalPalavrasDistintasA2 - totalPalavrasInterseccao);
    float similaridade = (float)(totalPalavrasInterseccao / totalUniaoPalavras);

    printf("%s = %d palavras distintas\n", nomeArq1, totalPalavrasDistintasA1);
    printf("%s = %d palavras distintas\n", nomeArq2, totalPalavrasDistintasA2);

    printf("Intersecao = %d\n", totalPalavrasInterseccao);
    printf("Uniao = %d\n", totalUniaoPalavras);

    printf("Jaccard = %.2f\n", similaridade);
}


// Dados dois ponteiro de arquivos texto e seus nomes, transforma
// o conteudo de ambos em AVLs e calcula a similaridade de Jaccard para elas
void imprimeJaccardTextos(FILE *arq1, char nomeArq1[], FILE *arq2, char nomeArq2[]) {
    clock_t inicioTempo, fimTempo;

    inicioTempo = clock();

    // Declara AVLs
    pNodoA *arvore1 = NULL;
    pNodoA *arvore2 = NULL;

    // Atribui AVLs geradas a partir dos arquivos
    arvore1 = converterArquivoTextoParaAVL(arq1, nomeArq1, arvore1);
    arvore2 = converterArquivoTextoParaAVL(arq2, nomeArq2, arvore2);

    // Calcula a similaridade
    calculaJaccard(arvore1, nomeArq1, arvore2, nomeArq2);

    fimTempo = clock();

    double tempoExecucao = (double)(fimTempo - inicioTempo) / CLOCKS_PER_SEC;
    int constanteMilisegundo = 1000;

    printf("Tempo: .5%f ms", tempoExecucao * constanteMilisegundo);
}




