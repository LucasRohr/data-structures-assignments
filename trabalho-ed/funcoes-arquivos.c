#include <stdio.h>
#include <string.h>
#include <ctype.h>

int abrirArquivo(FILE *arq, char nome[]) {
    arq = fopen(nome, "r+");

    if(arq) {
        return 1;
    } else {
        printf("Erro ao abrir arquivo txt");
        return 0;
    }
}

int gravarLinha(char texto[], FILE *arq) {
    int abriu_arquivo;

    abriu_arquivo = abrirArquivo(arq);

    if (abriu_arquivo) {
        fputs(texto, arq);
        fclose(arq);

        return 1;
    }

    fclose(arq);
    return 0;
}

char[] lerLinha(char texto[], int tamString, FILE *arq) {
    int abriu_arquivo;

    abriu_arquivo = abrirArquivo(arq);

    if (abriu_arquivo) {
        return fgets(texto, tamString, arq);
    }

    fclose(arq);
}



