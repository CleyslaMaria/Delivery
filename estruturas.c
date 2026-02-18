#include "estruturas.h"
#include <string.h>

/* ================= PEDIDO ================= */

/*
    Cria um novo pedido dinamicamente.
*/
Pedido* criarPedido(int id, char *cliente, char *hamburguer, int quantidade) {
    Pedido *p = malloc(sizeof(Pedido));

    // Verifica falha de alocação
    if (!p) {
        printf("Erro ao alocar memoria para o pedido.\n");
        return NULL;
    }

    // Inicializa os dados do pedido
    p->id = id;
    strcpy(p->cliente, cliente);
    strcpy(p->hamburguer, hamburguer);
    p->quantidade = quantidade;
    p->status = EM_ESPERA;

    return p;
}

/*
    Libera a memória ocupada por um pedido.
*/
void liberarPedido(Pedido *p) {
    if (p)
        free(p);
}

/* ================= FILA ================= */

/*
    Inicializa a fila de pedidos.
*/
void inicializarFila(FilaPedidos *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

/*
    Verifica se a fila está vazia.
*/
int filaVazia(FilaPedidos *fila) {
    return fila->inicio == NULL;
}

/*
    Insere um pedido no final da fila (FIFO).
*/
void enfileirar(FilaPedidos *fila, Pedido *p) {
    NoFila *novo = malloc(sizeof(NoFila));

    if (!novo) {
        printf("Erro ao alocar memoria para a fila.\n");
        return;
    }

    novo->pedido = p;
    novo->prox = NULL;

    // Caso a fila esteja vazia
    if (filaVazia(fila)) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

/*
    Remove o primeiro pedido da fila.
*/
Pedido* desenfileirar(FilaPedidos *fila) {
    if (filaVazia(fila))
        return NULL;

    NoFila *aux = fila->inicio;
    Pedido *p = aux->pedido;

    fila->inicio = aux->prox;

    // Caso a fila fique vazia
    if (!fila->inicio)
        fila->fim = NULL;

    free(aux);
    return p;
}

/*
    Remove o último pedido da fila (usado para cancelamento).
*/
Pedido* desenfileirarUltimo(FilaPedidos *fila) {
    if (filaVazia(fila))
        return NULL;

    NoFila *atual = fila->inicio;
    NoFila *anterior = NULL;

    while (atual->prox) {
        anterior = atual;
        atual = atual->prox;
    }

    Pedido *p = atual->pedido;

    if (!anterior) {
        fila->inicio = fila->fim = NULL;
    } else {
        anterior->prox = NULL;
        fila->fim = anterior;
    }

    free(atual);
    return p;
}

/*
    Lista todos os pedidos em espera na fila.
*/
void listarFila(FilaPedidos *fila) {
    if (filaVazia(fila)) {
        printf("Fila de pedidos vazia.\n");
        return;
    }

    NoFila *aux = fila->inicio;
    while (aux) {
        printf("Pedido %d - %s (%s) x%d [%s]\n",
               aux->pedido->id,
               aux->pedido->cliente,
               aux->pedido->hamburguer,
               aux->pedido->quantidade,
               statusParaTexto(aux->pedido->status));
        aux = aux->prox;
    }
}

/* ================= HISTÓRICO (PILHA) ================= */

/*
    Insere um pedido no topo da pilha de histórico.
*/
void empilharHistorico(NoHistorico **topo, Pedido *p) {
    NoHistorico *novo = malloc(sizeof(NoHistorico));

    if (!novo) {
        printf("Erro ao alocar memoria para o historico.\n");
        return;
    }

    novo->pedido = p;
    novo->prox = *topo;
    *topo = novo;
}

/*
    Lista os pedidos do histórico (LIFO).
*/
void listarHistorico(NoHistorico *topo) {
    if (!topo) {
        printf("Historico vazio.\n");
        return;
    }

    while (topo) {
        printf("Pedido %d - %s (%s) [%s]\n",
               topo->pedido->id,
               topo->pedido->cliente,
               topo->pedido->hamburguer,
               statusParaTexto(topo->pedido->status));
        topo = topo->prox;
    }
}

/*
    Libera toda a pilha de histórico.
*/
void liberarHistorico(NoHistorico *topo) {
    while (topo) {
        NoHistorico *aux = topo;
        topo = topo->prox;
        liberarPedido(aux->pedido);
        free(aux);
    }
}

/* ================= UTILIDADES ================= */

/*
    Verifica se existe um pedido em preparo.
*/
int existePedidoEmPreparo(Pedido *p) {
    return p != NULL;
}

/*
    Converte o status do pedido para texto.
*/
const char* statusParaTexto(StatusPedido status) {
    switch (status) {
        case EM_ESPERA: return "Em espera";
        case EM_PREPARO: return "Em preparo";
        case FINALIZADO: return "Finalizado";
        case CANCELADO: return "Cancelado";
        default: return "Desconhecido";
    }
}
