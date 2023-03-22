
/* TAD para estruturas e funcoes */

// TAD Lista Simplesmente Encadeada


// Tipo de dado para representa o conteudo do no
// junto do ponteiro para o proximo No
struct s_PtNo{
    char palavra[30];
    struct s_PtNo * prox;
};

typedef struct s_PtNo TipoPtNoLista;


// Tipo de dado para nodos da AVL
struct TNodoA{
 char palavra[50];
 int altura;
 struct TNodoA *esq;
 struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;


// == Funcoes de LSE ==

// Retorna valor default NULL como inicializador de um No
TipoPtNoLista* inicializaLista(void);

// Adiciona um novo No no comeco da lista e aponta o proximo No
// como o primeiro anterior
TipoPtNoLista* insereInicio(TipoPtNoLista* ptLista, char texto[]);

// Adiciona um novo No no final da lista e aponta o proximo No
// como vazio, vai percorrendo os Nos para isso
TipoPtNoLista* insereFim(TipoPtNoLista* ptLista, char texto[]);

// Busca em uma lista de Nos um dado a ser pesquisado, retornando o mesmo
// se achar ou NULL caso nao
TipoPtNoLista* consultaLista(TipoPtNoLista* ptLista, char palavra[]);



// == Funcoes para manipulacao de linhas de string ==

// Funcao que dado ponteiro de LSE e um texto, separa o texto em palavras na LSE
// atraves dos separadores informados para o trabalho
TipoPtNoLista* separaStringPorSeparadores(TipoPtNoLista* ptLista, char texto[]);

// Dado um texto, torna todo caractere lower case
void tornaTextoLowerCase(char texto[]);

// Dado um nome de arquivo de stopwords, le o arquivo e adiciona cada palavra
// em uma LSE para uso na insercao de palavras na AVL
TipoPtNoLista* lerStopWords(FILE *arq, char nomeArquivo[]);



//  == Funcoes base para AVL ==

// Retorna maior altura entre duas de um nodo
int maior(int a, int b);

// Dado um no de arvore, retorna sua altura, armazenada no nodo
int alturaNo(pNodoA *a);

// Retorna o fator de balanceamento de um nodo, podendo ser valor negativo
int fatorNo(pNodoA *a);

// Realiza um rotacao a esquerda dado o nodo da AVL
pNodoA* rotacaoEsquerda(pNodoA *a);

// Realiza um rotacao a direita dado o nodo da AVL
pNodoA* rotacaoDireita(pNodoA *a);

// Efetua a rotacao dupla direita fazendo primeiro rotacao simples esquerda e depois direita
pNodoA* rotacaoDuplaDireita(pNodoA *a);

// Efetua a rotacao dupla esquerda fazendo primeiro rotacao simples direita e depois esquerda
pNodoA* rotacaoDuplaEsquerda(pNodoA *a);

// Funcao que usa das rotacoes para balencear a AVL apos uma insercao ou remoca na mesma
pNodoA* balancear(pNodoA *a);

// Recebe ponteiro da arvore e encontra palavra passado na mesma
pNodoA* consultaAVL(pNodoA *arvore, char palavra[]);

// Cria um novo no da AVL e retorna o mesmo
pNodoA* criaNo(char palavra[]);

// Recebe ponteiro da arvore e palavra, inserindo a palavra na mesma usando do balanceamento em AVL
pNodoA* insereNodoAVL(pNodoA *arvore, char palavra[]);



// == Funcoes especificas para a resolucao do problema do trabalho ==

// Dado ponteiro de AVL e uma palavra, verifica se a mesma ainda nao foi inserida
// e nao Ž uma stopword para inserir a palavra na AVL
void inserePalavraAVL(pNodoA *arvore, char palavra[]);

// Dado ponteiro de arquivo e ponteiro de arvore, percorre cada linha do arquivo de texto
// tornando cada caractere minusculo e sem separadores, inserindo cada palavra na AVL
// conforme regras da funcao auxiliar chamada
pNodoA* converterArquivoTextoParaAVL(FILE *arq, char nomeArq[], pNodoA *arvore);

// Funcao que recebe um ponteiro de arvore e percorre a mesma contando
// quantos nodos existem de forma recursiva (conta palavras distintas pois nao sao inseridas palavras repetidas)
int contaPalavrasDistintas(pNodoA *a);

// Dado ponteiros para duas AVLs, compara quantas palavras em comum existem entre ambas arvores
int contaPalavrasDistintasInterseccao(pNodoA *a1, pNodoA *a2);

// Dadas duas AVLs e nomes de dois arquivos, calcula a similaridade de Jaccard para elas
void calculaJaccard(pNodoA *a1, char nomeArq1[], pNodoA *a2, char nomeArq2[]);

// Dados dois ponteiro de arquivos texto e seus nomes, transforma
// o conteudo de ambos em AVLs e calcula a similaridade de Jaccard para elas
void imprimeJaccardTextos(FILE *arq1, char nomeArq1[], FILE *arq2, char nomeArq2[]);


