# Estruturas de Dados em C — Manipulação de Listas Encadeadas

Atividade avaliativa de Estruturas de Dados (2º Bimestre).  
Implementação de um gerenciador de inteiros com listas simplesmente encadeadas e de uma playlist com lista circular duplamente encadeada.

---

## Estrutura do Repositório

```
.
├── parte1_2.c   — Inserção em posição específica + Busca por valor
├── parte3_4.c   — Inverter lista + Dividir lista em duas
├── parte5.c     — Playlist com lista circular duplamente encadeada
└── README.md
```

---

## Compilação e Execução

Requer apenas um compilador C (gcc, clang etc.) e as bibliotecas padrão.

```bash
# Partes 1 e 2
gcc -Wall -Wextra -o parte1_2 parte1_2.c
./parte1_2

# Partes 3 e 4
gcc -Wall -Wextra -o parte3_4 parte3_4.c
./parte3_4

# Parte 5
gcc -Wall -Wextra -o parte5 parte5.c
./parte5
```

---

## Parte 1 — Inserção em Posição Específica

**Assinatura:** `void inserirPosicao(No **head, int valor, int posicao);`

### Solução

A função percorre a lista até o nó **anterior** à posição desejada e redireciona os ponteiros para encaixar o novo nó.

| Caso | Comportamento |
|------|---------------|
| Lista vazia | Insere normalmente na posição 0 |
| Início (`pos = 0`) | Novo nó passa a ser o `head` |
| Meio | Percorre até `pos - 1` e encaixa o nó |
| Fim | Percorre até o último nó e anexa |
| Posição inválida | Mensagem de erro, nenhuma alteração |

```
inserir 99 na posição 1:
  Antes:  10 -> 20 -> 30 -> NULL
  Depois: 10 -> 99 -> 20 -> 30 -> NULL
```

**Complexidade:** O(n) no pior caso (inserção no fim).

---

## Parte 2 — Busca por Valor

**Assinatura:** `int buscarValor(No *head, int valor);`

### Solução

Percorre a lista com um contador de posição. Retorna a posição na primeira ocorrência encontrada, ou `-1` se o valor não existir. Não usa vetor auxiliar.

```
Lista: 10 -> 20 -> 30 -> NULL
buscarValor(lista, 20)  →  1
buscarValor(lista, 99)  → -1
```

**Complexidade:** O(n).

---

## Parte 3 — Inverter Lista

**Assinatura:** `void inverterLista(No **head);`

### Solução

Algoritmo de inversão *in-place* com três ponteiros auxiliares (`anterior`, `atual`, `proximo`). A cada iteração o ponteiro `prox` do nó corrente é redirecionado para o nó anterior, "desviando" o sentido da lista.

```
Iteração 1: NULL  ←  10  →  20  →  30
Iteração 2: NULL  ←  10  ←  20  →  30
Iteração 3: NULL  ←  10  ←  20  ←  30
```

Ao final, `head` é atualizado para o último nó visitado (que era o último da lista original).

```
Antes:  10 -> 20 -> 30 -> NULL
Depois: 30 -> 20 -> 10 -> NULL
```

**Complexidade:** O(n) tempo, O(1) espaço.

---

## Parte 4 — Dividir Lista em Duas

**Assinatura:** `void dividirLista(No *head, No **lista1, No **lista2);`

### Solução

Usa a técnica do **ponteiro rápido/lento** (algoritmo de Floyd):

- `lento` avança **1 nó** por vez.
- `rapido` avança **2 nós** por vez.

Quando `rapido` atinge o fim, `lento` está no meio da lista. O nó seguinte a `lento` inicia a segunda metade; `lento->prox` é anulado para separar as listas.

Se o número de elementos for ímpar, a primeira lista recebe o elemento a mais (comportamento natural do algoritmo).

```
Original (5 elementos): 10 -> 20 -> 30 -> 40 -> 50 -> NULL
Lista 1: 10 -> 20 -> 30 -> NULL
Lista 2: 40 -> 50 -> NULL

Original (4 elementos): 1 -> 2 -> 3 -> 4 -> NULL
Lista 1: 1 -> 2 -> NULL
Lista 2: 3 -> 4 -> NULL
```

**Complexidade:** O(n) tempo, O(1) espaço.

---

## Parte 5 — Playlist com Lista Circular Duplamente Encadeada

### Estrutura

```c
typedef struct No {
    char musica[100];
    struct No *prox;   /* próximo nó (sentido horário)        */
    struct No *ant;    /* nó anterior (sentido anti-horário)  */
} No;
```

### Invariantes mantidos em todo momento

- `head->ant` aponta sempre para o **último** nó.
- `ultimo->prox` aponta sempre para o **head**.
- Cada nó tem `prox` e `ant` sempre preenchidos (nunca `NULL`).

```
[Rock] <-> [Jazz] <-> [Pop]
  ^_________________________|
```

### Funções implementadas

| Função | Descrição |
|--------|-----------|
| `adicionarMusica` | Insere ao final; atualiza `ultimo->prox = head` e `head->ant = novo` |
| `proximaMusica` | Avança `*atual = (*atual)->prox` (circular, nunca NULL) |
| `musicaAnterior` | Recua `*atual = (*atual)->ant` (circular, nunca NULL) |
| `exibirPlaylist` | Percorre usando o `head` como âncora para detectar o fim |
| `totalMusicas` | Conta nós com laço `do-while` usando `head` como sentinela |
| `removerMusica` | Remove por nome; ajusta vizinhos e atualiza `head` se necessário |
| `liberarPlaylist` | Libera todos os nós com `do-while`; anula `*head` |
| `reproduzirPlaylist` | Reproduz exatamente `totalMusicas()` vezes — evita loop infinito |

### Controle de percurso (prevenção de loop infinito)

Em todas as funções que percorrem a lista circular, o critério de parada é **sempre baseado no `head`** como sentinela ou em um contador derivado de `totalMusicas()`. Nunca se compara com `NULL`, pois nenhum nó aponta para `NULL` nessa estrutura.

```c
/* Exemplo em exibirPlaylist */
do {
    printf("[%s]", atual->musica);
    atual = atual->prox;
} while (atual != head);  /* para ao dar a volta completa */
```

---

## Requisitos Atendidos

- [x] Apenas `stdio.h` e `stdlib.h`
- [x] Sem vetores auxiliares em nenhuma função
- [x] Memória gerenciada com `malloc`/`free`
- [x] Sem variáveis globais
- [x] Indentação consistente (estilo K&R)
- [x] Todos os casos extremos tratados (lista vazia, único elemento, posição inválida)
