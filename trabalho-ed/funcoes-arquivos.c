#include <stdio.h>
#include <string.h>

int abrirArquivo(FILE *arq, char nome[]) {
    arq = fopen(nome, "r+");

    if(arq) {
        return 1;
    } else {
        printf("Erro ao abrir arquivo txt");
        return 0;
    }
}

char* lerLinha(char texto[], int tamString, FILE *arq, char nomeArq[]) {
    int abriu_arquivo;

    abriu_arquivo = abrirArquivo(arq, nomeArq);

    if (abriu_arquivo) {
        return fgets(texto, tamString, arq);
    }

    fclose(arq);
}



