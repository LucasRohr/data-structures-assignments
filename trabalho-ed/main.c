#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "tad.h"
#include "tad-arquivos.h"

#define TAM_ARGS 3

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"");

    FILE *texto1 = NULL;
    FILE *texto2 = NULL;

    if (argc != TAM_ARGS) {
        printf("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <arq_texto1> <arq_texto2>\n");
        return 1;
    } else {
        imprimeJaccardTextos(texto1, argv[1], texto2, argv[2]);
    }
}
