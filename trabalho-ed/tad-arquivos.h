
// Funcoes para manipulacao de arquivos

// Dado ponteiro do arquivo e seu nome, tenta abrir o mesmo
int abrirArquivo(FILE *arq, char nome[]);

// Dada string e ponteiro do arquivo, grava linha no arquivo
int gravarLinha(char texto[], FILE *arq);

// Dada linha de string e arquivo, retorna o texto de linha do arquivo para a string
char[] lerLinha(char texto[], int tamString, FILE *arq);
