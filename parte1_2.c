/*
 * Parte 1: Inserção em Posição Específica
 * Parte 2: Busca por Valor
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

/* Cria um novo nó com o valor fornecido */
No *criarNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        exit(1);
    }
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

/* Exibe todos os elementos da lista */
void exibirLista(No *head) {
    No *atual = head;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

/* Libera toda a memória da lista */
void liberarLista(No **head) {
    No *atual = *head;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *head = NULL;
}

/*
 * Parte 1 — Inserção em Posição Específica
 * Insere um novo nó com 'valor' na posição indicada (base 0).
 * Funciona para: lista vazia, início (pos=0), meio e fim.
 * Exibe erro se a posição for inválida.
 */
void inserirPosicao(No **head, int valor, int posicao) {
    if (posicao < 0) {
        printf("Erro: posicao invalida (%d).\n", posicao);
        return;
    }

    No *novo = criarNo(valor);

    /* Inserção no início (posição 0) ou lista vazia */
    if (posicao == 0) {
        novo->prox = *head;
        *head = novo;
        return;
    }

    /* Percorre até o nó anterior à posição desejada */
    No *atual = *head;
    int i = 0;
    while (atual != NULL && i < posicao - 1) {
        atual = atual->prox;
        i++;
    }

    if (atual == NULL) {
        printf("Erro: posicao invalida (%d), lista tem %d elemento(s).\n",
               posicao, i + ((*head != NULL) ? 1 : 0));
        free(novo);
        return;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

/*
 * Parte 2 — Busca por Valor
 * Retorna a posição (base 0) da primeira ocorrência de 'valor'.
 * Retorna -1 se não encontrado.
 */
int buscarValor(No *head, int valor) {
    No *atual = head;
    int posicao = 0;

    while (atual != NULL) {
        if (atual->valor == valor) {
            return posicao;
        }
        atual = atual->prox;
        posicao++;
    }

    return -1;
}

/* ─── Testes ─────────────────────────────────────────── */

int main(void) {
    No *lista = NULL;

    printf("=== PARTE 1: Insercao em Posicao Especifica ===\n\n");

    /* Monta lista base: 10 -> 20 -> 30 */
    inserirPosicao(&lista, 10, 0);
    inserirPosicao(&lista, 20, 1);
    inserirPosicao(&lista, 30, 2);
    printf("Lista inicial:          ");
    exibirLista(lista);

    /* Insere 99 na posição 1 → 10 -> 99 -> 20 -> 30 */
    inserirPosicao(&lista, 99, 1);
    printf("Apos inserir 99 pos 1:  ");
    exibirLista(lista);

    /* Insere no início */
    inserirPosicao(&lista, 5, 0);
    printf("Apos inserir 5  pos 0:  ");
    exibirLista(lista);

    /* Insere no fim */
    inserirPosicao(&lista, 100, 5);
    printf("Apos inserir 100 pos 5: ");
    exibirLista(lista);

    /* Posição inválida */
    inserirPosicao(&lista, 999, 50);

    printf("\n=== PARTE 2: Busca por Valor ===\n\n");

    /* lista atual: 5 -> 10 -> 99 -> 20 -> 30 -> 100 */
    exibirLista(lista);

    int pos;
    pos = buscarValor(lista, 20);
    printf("Buscar 20:  posicao %d\n", pos);

    pos = buscarValor(lista, 5);
    printf("Buscar 5:   posicao %d\n", pos);

    pos = buscarValor(lista, 100);
    printf("Buscar 100: posicao %d\n", pos);

    pos = buscarValor(lista, 77);
    printf("Buscar 77:  posicao %d (nao encontrado)\n", pos);

    liberarLista(&lista);
    return 0;
}
