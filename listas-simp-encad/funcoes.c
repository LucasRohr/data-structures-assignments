/* Funcoes para manipular listas de Nos */

// Retorna valor default NULL como inicializador de um No
TipoPtNo* inicializa(void) {
    return NULL;
}


// Percorre uma lista de Nos de imprime que esta vazia ou os dados de cada No
void imprime(TipoPtNo* ptLista) {
    TipoPtNo* ptaux;
    if (ptLista == NULL) {
        puts("lista vazia");
    } else {
        for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->prox) {
            printf("Titulo = %s Distribuidor = %s Diretor = %s\n",
            ptaux->info.titulo,
            ptaux->info.distr,
            ptaux->info.diretor);
        }
    }
}

// Busca em uma lista de Nos um dado a ser pesquisado, retornando o mesmo
// se achar ou NULL caso nao
TipoPtNo* consulta(TipoPtNo* ptLista, TipoInfoNo dadoBusca) {
    TipoPtNo *ptaux = ptLista; //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux !=NULL && (strcmp(ptaux->info.titulo, dadoBusca.titulo))) {
        ptaux = ptaux->prox;
    }

    // Pode retornar NULL ou o valor encontrado
    return ptaux;
}


// Adiciona um novo No no comeco da lista e aponta o proximo No
// como o primeiro anterior
TipoPtNo* insereInicio(TipoPtNo* ptLista, TipoInfoNo dados) {
    TipoPtNo *novo;

    novo = (TipoPtNo*) malloc(sizeof(TipoPtNo));

    novo->info = dados;
    novo->prox = ptLista;

    ptLista = novo;

    return novo;
}


// Adiciona um novo No no final da lista e aponta o proximo No
// como vazio, vai percorrendo os Nos para isso
TipoPtNo* insereFim(TipoPtNo* ptLista, TipoInfoNo dados) {
    TipoPtNo *novo, *ptaux = ptLista;

    novo = (TipoPtNo*) malloc(sizeof(TipoPtNo));

    novo->info = dados;
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


// Remove um elemento da lista de Nos e realoca as posicoes
// dos elementos por conta da remocao
TipoPtNo* remover(TipoPtNo* ptLista, char titulo[]) {
    TipoPtNo *ant = NULL; //ponteiro auxiliar para a posi‹o anterior
    TipoPtNo *ptaux = ptLista; //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux !=NULL && (strcmp(ptaux->info.titulo, titulo))) {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*verifica se achou*/
    if (ptaux == NULL) {
        return ptLista; /*retorna a lista original*/
    }

    /*vai remover o primeiro elemento*/
    if (ant == NULL) {
        ptLista = ptaux->prox;
    /*vai remover do meio ou do final*/
    } else {
        ant->prox = ptaux->prox;
    }

    free(ptaux); /*libera a mem—ria alocada*/

    return ptLista;
}


// Descarta os Nos de uma lista um por mum liberando
// os espacos alocados de memoria
TipoPtNo* destroi(TipoPtNo* ptLista) {
    TipoPtNo *ptaux; //ponteiro auxiliar para percorrer a lista

    while (ptLista != NULL) {
        ptaux = ptLista;
        ptLista = ptLista->prox;
        free(ptaux);
    }

    free(ptLista);

    return NULL;
}
