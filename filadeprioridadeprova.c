#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó na fila de prioridade
typedef struct No {
    int valor;
    int prioridade;
    struct No* prox;
} No;

// Estrutura da fila de prioridade
typedef struct {
    No* cabeca;
} FilaPrioridade;

// Função para criar uma fila de prioridade vazia
FilaPrioridade* criarFilaPrioridade() {
    FilaPrioridade* fila = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    fila->cabeca = NULL;
    return fila;
}

// Função para inserir um novo elemento na fila de prioridade
void inserir(FilaPrioridade* fila, int valor, int prioridade) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->prioridade = prioridade;
    novoNo->prox = NULL;
    
    // Se a fila está vazia ou o novo nó tem maior prioridade que a cabeça da fila
    if (fila->cabeca == NULL || novoNo->prioridade < fila->cabeca->prioridade) {
        novoNo->prox = fila->cabeca;
        fila->cabeca = novoNo;
    } else {
        // Procura a posição correta para inserir o novo nó
        No* atual = fila->cabeca;
        while (atual->prox != NULL && atual->prox->prioridade <= novoNo->prioridade) {
            atual = atual->prox;
        }
        // Insere o novo nó na posição correta
        novoNo->prox = atual->prox;
        atual->prox = novoNo;
    }
}

// Função para remover e retornar o elemento de mais alta prioridade
int remover(FilaPrioridade* fila) {
    if (fila->cabeca == NULL) {
        // Fila vazia
        printf("Erro: a fila está vazia.\n");
        exit(EXIT_FAILURE);
    }
    No* noRemover = fila->cabeca;
    int valorRemovido = noRemover->valor;
    fila->cabeca = noRemover->prox;
    free(noRemover);
    return valorRemovido;
}

// Função para liberar a memória alocada para a fila
void liberarFila(FilaPrioridade* fila) {
    No* atual = fila->cabeca;
    while (atual != NULL) {
        No* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(fila);
}

int main() {
    // Cria uma fila de prioridade vazia
    FilaPrioridade* fila = criarFilaPrioridade();

    // Insere alguns elementos na fila com suas prioridades
    inserir(fila, 10, 2);
    inserir(fila, 20, 1);
    inserir(fila, 30, 3);
    
    // Remove o elemento de mais alta prioridade e exibe
    printf("Elemento removido com maior prioridade: %d\n", remover(fila));

    // Remove outro elemento de mais alta prioridade e exibe
    printf("Elemento removido com maior prioridade: %d\n", remover(fila));

    // Libera a memória alocada para a fila
    liberarFila(fila);

    return 0;
}