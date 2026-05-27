/*
 * Parte 3: Inverter Lista
 * Parte 4: Dividir Lista em Duas
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

/* Cria um novo nó */
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

/* Insere no final da lista */
void inserirFim(No **head, int valor) {
    No *novo = criarNo(valor);
    if (*head == NULL) {
        *head = novo;
        return;
    }
    No *atual = *head;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;
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
 * Parte 3 — Inverter Lista
 * Inverte a lista in-place usando apenas três ponteiros auxiliares.
 * Não usa vetor nem cria nova lista.
 *
 * Algoritmo: a cada iteração, o ponteiro 'prox' do nó atual
 * é redirecionado para o nó anterior, avançando pelos três ponteiros.
 */
void inverterLista(No **head) {
    No *anterior = NULL;
    No *atual = *head;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;   /* guarda o próximo antes de sobrescrever */
        atual->prox = anterior;  /* inverte o ponteiro                     */
        anterior = atual;        /* avança 'anterior'                      */
        atual = proximo;         /* avança 'atual'                         */
    }

    *head = anterior; /* novo head é o último nó visitado */
}

/*
 * Parte 4 — Dividir Lista em Duas
 * Usa a técnica do ponteiro rápido/lento (Floyd):
 *   - lento avança 1 nó por vez
 *   - rapido avança 2 nós por vez
 * Quando 'rapido' chega ao fim, 'lento' está no meio.
 * Se ímpar, a primeira lista recebe o elemento a mais.
 */
void dividirLista(No *head, No **lista1, No **lista2) {
    if (head == NULL) {
        *lista1 = NULL;
        *lista2 = NULL;
        return;
    }

    No *lento = head;
    No *rapido = head;

    /*
     * Avança 'rapido' dois passos e 'lento' um passo.
     * Condição: rapido->prox e rapido->prox->prox devem existir.
     * Isso faz 'lento' parar no nó do meio (favorecendo a primeira metade
     * quando o total é ímpar).
     */
    while (rapido->prox != NULL && rapido->prox->prox != NULL) {
        lento = lento->prox;
        rapido = rapido->prox->prox;
    }

    *lista1 = head;          /* primeira metade começa no início   */
    *lista2 = lento->prox;   /* segunda metade começa após o meio  */
    lento->prox = NULL;      /* corta a ligação entre as metades   */
}

/* ─── Testes ─────────────────────────────────────────── */

int main(void) {
    /* ── Parte 3 ── */
    printf("=== PARTE 3: Inverter Lista ===\n\n");

    No *lista = NULL;
    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);

    printf("Antes: ");
    exibirLista(lista);

    inverterLista(&lista);

    printf("Apos:  ");
    exibirLista(lista);

    /* Lista com um elemento */
    No *unitaria = criarNo(42);
    printf("\nLista unitaria antes: ");
    exibirLista(unitaria);
    inverterLista(&unitaria);
    printf("Lista unitaria apos:  ");
    exibirLista(unitaria);
    free(unitaria);

    liberarLista(&lista);

    /* ── Parte 4 ── */
    printf("\n=== PARTE 4: Dividir Lista em Duas ===\n\n");

    /* Caso par: 5 elementos → 3 + 2 */
    No *base = NULL;
    inserirFim(&base, 10);
    inserirFim(&base, 20);
    inserirFim(&base, 30);
    inserirFim(&base, 40);
    inserirFim(&base, 50);

    printf("Original (5 elementos): ");
    exibirLista(base);

    No *l1 = NULL, *l2 = NULL;
    dividirLista(base, &l1, &l2);

    printf("Lista 1: ");
    exibirLista(l1);
    printf("Lista 2: ");
    exibirLista(l2);

    liberarLista(&l1);
    liberarLista(&l2);

    /* Caso par: 4 elementos → 2 + 2 */
    No *par = NULL;
    inserirFim(&par, 1);
    inserirFim(&par, 2);
    inserirFim(&par, 3);
    inserirFim(&par, 4);

    printf("\nOriginal (4 elementos): ");
    exibirLista(par);

    No *p1 = NULL, *p2 = NULL;
    dividirLista(par, &p1, &p2);

    printf("Lista 1: ");
    exibirLista(p1);
    printf("Lista 2: ");
    exibirLista(p2);

    liberarLista(&p1);
    liberarLista(&p2);

    /* Caso: 1 elemento */
    No *solo = criarNo(99);
    printf("\nOriginal (1 elemento):  ");
    exibirLista(solo);

    No *s1 = NULL, *s2 = NULL;
    dividirLista(solo, &s1, &s2);

    printf("Lista 1: ");
    exibirLista(s1);
    printf("Lista 2: ");
    exibirLista(s2);

    liberarLista(&s1);
    liberarLista(&s2);

    return 0;
}
