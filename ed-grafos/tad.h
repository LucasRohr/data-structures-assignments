#define TAM_MATRIZ 8

typedef int TipoInfo;

struct TPtFila {
    TipoInfo dado;
    struct TPtFila *elo;
};
typedef struct TPtFila TipoFila;


struct s_TipoDFila {
    struct TPtFila *prim;
    struct TPtFila *ult;
};
typedef struct s_TipoDFila TipoDFila;

TipoDFila* InicializaFila (TipoDFila *PtDFila);
TipoInfo ConsultaFila (TipoDFila *PtDFila);
void ImprimirFila (TipoDFila *PtDFila);
int InserirFila(TipoDFila **PtDFila, TipoInfo Dado);
int RemoverFila(TipoDFila **PtDFila, TipoInfo *Dado);
void DestroiFila (TipoDFila **PtDFila);
int VaziaFila(TipoDFila *PtDFila);
void dfs(int grafo[][TAM_MATRIZ], int vertice, int* visitados);
void bfs(int grafo[][TAM_MATRIZ], int vertice, int* visitados, TipoDFila *PtDFila);
