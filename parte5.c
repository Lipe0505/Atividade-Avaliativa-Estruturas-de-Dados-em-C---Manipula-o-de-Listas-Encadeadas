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

/* ─── Funções auxiliares ───────────────────────────────── */

/* Cria um novo nó isolado e auto-circular */
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

/* ─── Funções obrigatórias ─────────────────────────────── */

/*
 * Adiciona uma música ao final da playlist.
 * Mantém a circularidade: último->prox = head e head->ant = último.
 */
void adicionarMusica(No **head, char *nome) {
    No *novo = criarNo(nome);

    if (*head == NULL) {
        *head = novo; /* lista vazia: nó aponta para si mesmo */
        return;
    }

    No *ultimo = (*head)->ant; /* head->ant sempre é o último nó */

    /* Encadeia novo nó entre 'ultimo' e 'head' */
    ultimo->prox = novo;
    novo->ant    = ultimo;
    novo->prox   = *head;
    (*head)->ant = novo;
}

/*
 * Avança para a próxima música.
 * Como a lista é circular, nunca há NULL.
 */
void proximaMusica(No **atual) {
    if (*atual == NULL) {
        printf("Playlist vazia.\n");
        return;
    }
    *atual = (*atual)->prox;
}

/*
 * Retrocede para a música anterior.
 */
void musicaAnterior(No **atual) {
    if (*atual == NULL) {
        printf("Playlist vazia.\n");
        return;
    }
    *atual = (*atual)->ant;
}

/*
 * Exibe todas as músicas da playlist.
 * Usa o head como âncora para detectar o fim do percurso
 * e evitar loop infinito.
 */
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

    /* Indica circularidade */
    printf(" <->\n");
    printf("          ^");
    /* Alinha a seta de volta ao início */
    No *tmp = head;
    int total = 0;
    do {
        total += (int)strlen(tmp->musica) + 5; /* [nome] + " <-> " */
        tmp = tmp->prox;
    } while (tmp != head);
    total -= 5; /* último não tem " <-> " extra antes do fechamento */
    for (int i = 0; i < total - 1; i++) printf("_");
    printf("|\n");
}

/*
 * Retorna a quantidade de músicas na playlist.
 */
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

/*
 * Remove uma música pelo nome.
 * Retorna 1 se removeu, 0 se não encontrou.
 */
int removerMusica(No **head, const char *nome) {
    if (*head == NULL) {
        return 0;
    }

    No *atual = *head;
    int total = totalMusicas(*head);

    for (int i = 0; i < total; i++) {
        if (strcmp(atual->musica, nome) == 0) {
            if (total == 1) {
                /* Único nó na lista */
                free(atual);
                *head = NULL;
                return 1;
            }

            /* Ajusta ponteiros dos vizinhos */
            atual->ant->prox = atual->prox;
            atual->prox->ant = atual->ant;

            /* Se estamos removendo o head, avança o head */
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

/*
 * Libera toda a memória da playlist.
 */
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

/* ─── Demonstração de navegação completa ──────────────── */

/*
 * Simula a reprodução de toda a playlist uma vez,
 * detectando quando voltou ao início para evitar loop infinito.
 */
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

/* ─── Testes ─────────────────────────────────────────── */

int main(void) {
    printf("=== PARTE 5: Playlist Circular Duplamente Encadeada ===\n\n");

    No *playlist = NULL;
    No *atual    = NULL;

    /* Adiciona músicas */
    adicionarMusica(&playlist, "Rock");
    adicionarMusica(&playlist, "Jazz");
    adicionarMusica(&playlist, "Pop");

    exibirPlaylist(playlist);
    printf("Total de musicas: %d\n\n", totalMusicas(playlist));

    /* Navegação para frente */
    printf("--- Navegacao para frente ---\n");
    atual = playlist;
    printf("Atual: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("Proxima: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("Proxima: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("Proxima (circular): %s\n\n", atual->musica);

    /* Navegação para trás */
    printf("--- Navegacao para tras ---\n");
    atual = playlist;
    printf("Atual: %s\n", atual->musica);
    musicaAnterior(&atual);
    printf("Anterior (circular): %s\n", atual->musica);
    musicaAnterior(&atual);
    printf("Anterior: %s\n\n", atual->musica);

    /* Reprodução completa com controle de percurso */
    printf("--- Reproducao completa ---\n");
    reproduzirPlaylist(playlist);

    /* Adiciona mais músicas */
    printf("\n--- Adicionando mais musicas ---\n");
    adicionarMusica(&playlist, "Blues");
    adicionarMusica(&playlist, "Classical");
    exibirPlaylist(playlist);
    printf("Total: %d\n\n", totalMusicas(playlist));

    /* Remove uma música */
    printf("--- Removendo 'Jazz' ---\n");
    int removido = removerMusica(&playlist, "Jazz");
    printf("Resultado: %s\n", removido ? "removido com sucesso" : "nao encontrado");
    exibirPlaylist(playlist);
    printf("Total: %d\n\n", totalMusicas(playlist));

    /* Remove música inexistente */
    printf("--- Removendo 'Samba' (inexistente) ---\n");
    removido = removerMusica(&playlist, "Samba");
    printf("Resultado: %s\n\n", removido ? "removido com sucesso" : "nao encontrado");

    /* Remove o head */
    printf("--- Removendo 'Rock' (head) ---\n");
    removerMusica(&playlist, "Rock");
    exibirPlaylist(playlist);
    printf("Total: %d\n\n", totalMusicas(playlist));

    /* Reprodução final */
    printf("--- Reproducao final ---\n");
    reproduzirPlaylist(playlist);

    liberarPlaylist(&playlist);
    printf("\nMemoria liberada. Playlist: %s\n",
           playlist == NULL ? "NULL (correto)" : "ERRO - memoria nao liberada");

    return 0;
}
