/* TAD para lista simplesmente encadeada */

// Tipo de dado para conteudo do No
struct s_InfoNo{
    char titulo[20];
    char distr[20];
    char diretor[20];
};

typedef struct s_InfoNo TipoInfoNo;


// Tipo de dado para representa o conteudo do no
// junto do ponteiro para o proximo No
struct s_PtNo{
    TipoInfoNo info;
    struct s_PtNo * prox;
};

typedef struct s_PtNo TipoPtNo;


/* Assinaturas de funcoes para No */

// Retorna valor default NULL como inicializador de um No
TipoPtNo* inicializa(void);

// Percorre uma lista de Nos de imprime que esta vazia ou os dados de cada No
void imprime(TipoPtNo* ptLista);

// Busca em uma lista de Nos um dado a ser pesquisado, retornando o mesmo
// se achar ou NULL caso nao
TipoPtNo* consulta(TipoPtNo* ptLista, TipoInfoNo dadoBusca);

// Adiciona um novo No no comeco da lista e aponta o proximo No
// como o primeiro anterior
TipoPtNo* insereInicio(TipoPtNo* ptLista, TipoInfoNo dados);

// Adiciona um novo No no final da lista e aponta o proximo No
// como vazio, vai percorrendo os Nos para isso
TipoPtNo* insereFim(TipoPtNo* ptLista, TipoInfoNo dados)

// Remove um elemento da lista de Nos e realoca as posicoes
// dos elementos por conta da remocao
TipoPtNo* remover(TipoPtNo* ptLista, char titulo[]);

// Descarta os Nos de uma lista um por mum liberando
// os espacos alocados de memoria
TipoPtNo* destroi(TipoPtNo* ptLista);

