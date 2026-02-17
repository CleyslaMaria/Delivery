#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>

// Enum para status do pedido
typedef enum {
    EM_ESPERA,
    EM_PREPARO,
    FINALIZADO,
    CANCELADO
} StatusPedido;

typedef struct Pedido {
    int id;
    char cliente[50];
    char hamburguer[50];
    int quantidade;
    StatusPedido status; 
} Pedido;

// Estrutura da fila 
typedef struct NoFila {
    Pedido *pedido;       // ponteiro para o pedido
    struct NoFila *prox;  // próximo nó
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaPedidos;


// Estrutura do historico de pedidos finalizados
typedef struct NoHistorico {
    Pedido *pedido;                  // ponteiro para o pedido finalizado
    struct NoHistorico *prox;         // próximo nó da pilha
} NoHistorico;


// Protótipos de funções

/* === Pedido === */
Pedido* criarPedido(int id, char *cliente, char *hamburguer, int quantidade);
void liberarPedido(Pedido *p);

/* === Fila === */
void inicializarFila(FilaPedidos *fila);
int filaVazia(FilaPedidos *fila);
void enfileirar(FilaPedidos *fila, Pedido *p);
Pedido* desenfileirar(FilaPedidos *fila);
Pedido* desenfileirarUltimo(FilaPedidos *fila);
void listarFila(FilaPedidos *fila);

/* === Pedido em preparo === */
int existePedidoEmPreparo(Pedido *p);

/* ===Histórico === */
void empilharHistorico(NoHistorico **topo, Pedido *p);
void listarHistorico(NoHistorico *topo);
void liberarHistorico(NoHistorico *topo);

/* === Utilidades === */
const char* statusParaTexto(StatusPedido status);

#endif