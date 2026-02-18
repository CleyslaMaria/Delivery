#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>

/* === Status do Pedido === */
typedef enum {
    EM_ESPERA,
    EM_PREPARO,
    FINALIZADO,
    CANCELADO
} StatusPedido;

/* === Pedido === */
typedef struct Pedido {
    int id;
    char cliente[50];
    char hamburguer[50];
    int quantidade;
    StatusPedido status;
} Pedido;

/* === Fila de Pedidos === */
typedef struct NoFila {
    Pedido *pedido;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaPedidos;

/* === Histórico (Pilha) === */
typedef struct NoHistorico {
    Pedido *pedido;
    struct NoHistorico *prox;
} NoHistorico;

/* === Protótipos === */

/* Pedido */
Pedido* criarPedido(int id, char *cliente, char *hamburguer, int quantidade);
void liberarPedido(Pedido *p);

/* Fila */
void inicializarFila(FilaPedidos *fila);
int filaVazia(FilaPedidos *fila);
void enfileirar(FilaPedidos *fila, Pedido *p);
Pedido* desenfileirar(FilaPedidos *fila);
Pedido* desenfileirarUltimo(FilaPedidos *fila);
void listarFila(FilaPedidos *fila);

/* Histórico */
void empilharHistorico(NoHistorico **topo, Pedido *p);
void listarHistorico(NoHistorico *topo);
void liberarHistorico(NoHistorico *topo);

/* Utilidades */
int existePedidoEmPreparo(Pedido *p);
const char* statusParaTexto(StatusPedido status);

#endif
