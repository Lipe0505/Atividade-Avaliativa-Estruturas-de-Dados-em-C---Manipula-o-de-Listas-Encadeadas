#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

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

void exibirLista(No *head) {
    No *atual = head;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void liberarLista(No **head) {
    No *atual = *head;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *head = NULL;
}

void inverterLista(No **head) {
    No *anterior = NULL;
    No *atual = *head;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;  
        atual->prox = anterior;
        anterior = atual;        
        atual = proximo;        
    }

    *head = anterior;
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
    
    while (rapido->prox != NULL && rapido->prox->prox != NULL) {
        lento = lento->prox;
        rapido = rapido->prox->prox;
    }

    *lista1 = head;          
    *lista2 = lento->prox;   
    lento->prox = NULL;      
}

int main(void) {
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

    No *unitaria = criarNo(42);
    printf("\nLista unitaria antes: ");
    exibirLista(unitaria);
    inverterLista(&unitaria);
    printf("Lista unitaria apos:  ");
    exibirLista(unitaria);
    free(unitaria);

    liberarLista(&lista);

    printf("\n=== PARTE 4: Dividir Lista em Duas ===\n\n");

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
