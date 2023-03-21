
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


// Funcoes LSE:

// Retorna valor default NULL como inicializador de um No
TipoPtNoLista* inicializaLista(void);

// Adiciona um novo No no comeco da lista e aponta o proximo No
// como o primeiro anterior
TipoPtNoLista* insereInicio(TipoPtNoLista* ptLista, char texto[]);

// Adiciona um novo No no final da lista e aponta o proximo No
// como vazio, vai percorrendo os Nos para isso
TipoPtNoLista* insereFim(TipoPtNoLista* ptLista, char texto[]);



