#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *drt;
} No;

No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esq = NULL;
    novoNo->drt = NULL;
    return novoNo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else {
        raiz->drt = inserir(raiz->drt, valor);
    }
    return raiz;
}

int contarNosNaoFolhas(No* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    // Se o nó tem filhos, conta como nó não-folha
    int conta = 0;
    if (raiz->esq != NULL || raiz->drt != NULL) {
        conta = 1;
    }
    // Soma a contagem dos filhos
    conta += contarNosNaoFolhas(raiz->esq);
    conta += contarNosNaoFolhas(raiz->drt);
    return conta;
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->drt);
        free(raiz);
    }
}

int main() {
    // Teste 1: árvore vazia
    No* raiz1 = NULL;
    printf("Teste 1 (árvore vazia): %d\n", contarNosNaoFolhas(raiz1));

    // Teste 2: árvore com raiz e duas folhas
    No* raiz2 = criarNo(20);
    inserir(raiz2, 5);
    inserir(raiz2, 15);
    printf("Teste 2 (raiz e duas folhas): %d\n", contarNosNaoFolhas(raiz2));

    // Teste 3: árvore binária completa com profundidade 3
    No* raiz3 = criarNo(20);
    inserir(raiz3, 5);
    inserir(raiz3, 15);
    inserir(raiz3, 3);
    inserir(raiz3, 7);
    inserir(raiz3, 13);
    inserir(raiz3, 17);
    printf("Teste 3 (árvore completa com profundidade 3): %d\n", contarNosNaoFolhas(raiz3));

    // Libera a memória alocada para as árvores
    liberarArvore(raiz1);
    liberarArvore(raiz2);
    liberarArvore(raiz3);

    return 0;
}