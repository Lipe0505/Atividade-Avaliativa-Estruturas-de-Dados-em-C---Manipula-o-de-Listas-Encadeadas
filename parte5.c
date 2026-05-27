/*
 * Parte 5: Playlist com Lista Circular Duplamente Encadeada
 *
 * Estrutura:
 *   head->ant  aponta para o ÚLTIMO nó  (sentido horário)
 *   ultimo->prox aponta para head       (sentido anti-horário)
 *
 * Visualização:
 *   [Rock] <-> [Jazz] <-> [Pop]
 *      ^________________________|   (último->prox = head)
 *      |________________________|   (head->ant    = último)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char musica[100];
    struct No *prox;
    struct No *ant;
} No;

static No *criarNo(const char *nome) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        exit(1);
    }
    strncpy(novo->musica, nome, sizeof(novo->musica) - 1);
    novo->musica[sizeof(novo->musica) - 1] = '\0';
    novo->prox = novo;
    novo->ant  = novo;
    return novo;
}

void adicionarMusica(No **head, char *nome) {
    No *novo = criarNo(nome);

    if (*head == NULL) {
        *head = novo; 
        return;
    }

    No *ultimo = (*head)->ant; 

    ultimo->prox = novo;
    novo->ant    = ultimo;
    novo->prox   = *head;
    (*head)->ant = novo;
}

void proximaMusica(No **atual) {
    if (*atual == NULL) {
        printf("Playlist vazia.\n");
        return;
    }
    *atual = (*atual)->prox;
}

void musicaAnterior(No **atual) {
    if (*atual == NULL) {
        printf("Playlist vazia.\n");
        return;
    }
    *atual = (*atual)->ant;
}

void exibirPlaylist(No *head) {
    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    No *atual = head;
    printf("Playlist: ");
    do {
        printf("[%s]", atual->musica);
        if (atual->prox != head) {
            printf(" <-> ");
        }
        atual = atual->prox;
    } while (atual != head);

    printf(" <->\n");
    printf("          ^");

    No *tmp = head;
    int total = 0;
    do {
        total += (int)strlen(tmp->musica) + 5; 
        tmp = tmp->prox;
    } while (tmp != head);
    total -= 5; 
    for (int i = 0; i < total - 1; i++) printf("_");
    printf("|\n");
}

int totalMusicas(No *head) {
    if (head == NULL) {
        return 0;
    }

    int count = 0;
    No *atual = head;
    do {
        count++;
        atual = atual->prox;
    } while (atual != head);

    return count;
}

int removerMusica(No **head, const char *nome) {
    if (*head == NULL) {
        return 0;
    }

    No *atual = *head;
    int total = totalMusicas(*head);

    for (int i = 0; i < total; i++) {
        if (strcmp(atual->musica, nome) == 0) {
            if (total == 1) {
                free(atual);
                *head = NULL;
                return 1;
            }

            atual->ant->prox = atual->prox;
            atual->prox->ant = atual->ant;

            if (atual == *head) {
                *head = atual->prox;
            }

            free(atual);
            return 1;
        }
        atual = atual->prox;
    }

    return 0;
}

void liberarPlaylist(No **head) {
    if (*head == NULL) {
        return;
    }

    No *atual = *head;
    No *inicio = *head;

    do {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    } while (atual != inicio);

    *head = NULL;
}

void reproduzirPlaylist(No *head) {
    if (head == NULL) {
        printf("Playlist vazia, nada a reproduzir.\n");
        return;
    }

    int total = totalMusicas(head);
    No *atual = head;

    printf("▶ Reproduzindo playlist (%d musica(s)):\n", total);
    for (int i = 0; i < total; i++) {
        printf("  %d. %s\n", i + 1, atual->musica);
        atual = atual->prox;
    }
    printf("↺ Voltando ao inicio: %s\n", atual->musica);
}

int main(void) {
    printf("=== PARTE 5: Playlist Circular Duplamente Encadeada ===\n\n");

    No *playlist = NULL;
    No *atual    = NULL;

    adicionarMusica(&playlist, "Rock");
    adicionarMusica(&playlist, "Jazz");
    adicionarMusica(&playlist, "Pop");

    exibirPlaylist(playlist);
    printf("Total de musicas: %d\n\n", totalMusicas(playlist));

    printf("--- Navegacao para frente ---\n");
    atual = playlist;
    printf("Atual: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("Proxima: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("Proxima: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("Proxima (circular): %s\n\n", atual->musica);

    printf("--- Navegacao para tras ---\n");
    atual = playlist;
    printf("Atual: %s\n", atual->musica);
    musicaAnterior(&atual);
    printf("Anterior (circular): %s\n", atual->musica);
    musicaAnterior(&atual);
    printf("Anterior: %s\n\n", atual->musica);

    printf("--- Reproducao completa ---\n");
    reproduzirPlaylist(playlist);

    printf("\n--- Adicionando mais musicas ---\n");
    adicionarMusica(&playlist, "Blues");
    adicionarMusica(&playlist, "Classical");
    exibirPlaylist(playlist);
    printf("Total: %d\n\n", totalMusicas(playlist));

    printf("--- Removendo 'Jazz' ---\n");
    int removido = removerMusica(&playlist, "Jazz");
    printf("Resultado: %s\n", removido ? "removido com sucesso" : "nao encontrado");
    exibirPlaylist(playlist);
    printf("Total: %d\n\n", totalMusicas(playlist));
    
    printf("--- Removendo 'Samba' (inexistente) ---\n");
    removido = removerMusica(&playlist, "Samba");
    printf("Resultado: %s\n\n", removido ? "removido com sucesso" : "nao encontrado");

    printf("--- Removendo 'Rock' (head) ---\n");
    removerMusica(&playlist, "Rock");
    exibirPlaylist(playlist);
    printf("Total: %d\n\n", totalMusicas(playlist));

    printf("--- Reproducao final ---\n");
    reproduzirPlaylist(playlist);

    liberarPlaylist(&playlist);
    printf("\nMemoria liberada. Playlist: %s\n",
           playlist == NULL ? "NULL (correto)" : "ERRO - memoria nao liberada");

    return 0;
}
