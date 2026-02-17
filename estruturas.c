#include "estruturas.h"
#include <string.h>

/* === Pedido === */
Pedido* criarPedido(int id, char *cliente, char *hamburguer, int quantidade) {
    Pedido *p = malloc(sizeof(Pedido));
    if (!p) return NULL;

    p->id = id;
    strcpy(p->cliente, cliente);
    strcpy(p->hamburguer, hamburguer);
    p->quantidade = quantidade;
    p->status = EM_ESPERA;

    return p;
}

void liberarPedido(Pedido *p) {
    if (p) free(p);
}

/* === Fila === */
void inicializarFila(FilaPedidos *fila) {
    fila->inicio = fila->fim = NULL;
}

int filaVazia(FilaPedidos *fila) {
    return fila->inicio == NULL;
}

void enfileirar(FilaPedidos *fila, Pedido *p) {
    NoFila *novo = malloc(sizeof(NoFila));
    novo->pedido = p;
    novo->prox = NULL;

    if (filaVazia(fila)) {
        fila->inicio = fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

Pedido* desenfileirar(FilaPedidos *fila) {
    if (filaVazia(fila)) return NULL;

    NoFila *aux = fila->inicio;
    Pedido *p = aux->pedido;

    fila->inicio = aux->prox;
    if (fila->inicio == NULL)
        fila->fim = NULL;

    free(aux);
    return p;
}

Pedido* desenfileirarUltimo(FilaPedidos *fila) {
    if (filaVazia(fila)) return NULL;

    NoFila *cur = fila->inicio;
    NoFila *prev = NULL;
    while (cur->prox) {
        prev = cur;
        cur = cur->prox;
    }

    Pedido *p = cur->pedido;
    if (prev == NULL) { // única entrada
        fila->inicio = fila->fim = NULL;
    } else {
        prev->prox = NULL;
        fila->fim = prev;
    }
    free(cur);
    return p;
}

void listarFila(FilaPedidos *fila) {
    NoFila *aux = fila->inicio;
    if (!aux) {
        printf("Fila vazia.\n");
        return;
    }

    while (aux) {
        printf("Pedido %d - %s (%s) x%d\n",
               aux->pedido->id,
               aux->pedido->cliente,
               aux->pedido->hamburguer,
               aux->pedido->quantidade);
        aux = aux->prox;
    }
}

/* === Histórico === */
void empilharHistorico(NoHistorico **topo, Pedido *p) {
    NoHistorico *novo = malloc(sizeof(NoHistorico));
    novo->pedido = p;
    novo->prox = *topo;
    *topo = novo;
}

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

void liberarHistorico(NoHistorico *topo) {
    while (topo) {
        NoHistorico *aux = topo;
        topo = topo->prox;
        liberarPedido(aux->pedido);
        free(aux);
    }
}

const char* statusParaTexto(StatusPedido status) {
    switch (status) {
        case EM_ESPERA: return "Em espera";
        case EM_PREPARO: return "Em preparo";
        case FINALIZADO: return "Finalizado";
        case CANCELADO: return "Cancelado";
        default: return "Desconhecido";
    }
}

int existePedidoEmPreparo(Pedido *p) {
    return p != NULL;
}
