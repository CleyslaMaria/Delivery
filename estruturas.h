#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>

/*
    Enumeração que define os possíveis estados de um pedido.
    Facilita o controle e a leitura do status ao longo do sistema.
*/
typedef enum {
    EM_ESPERA,     // Pedido aguardando atendimento na fila
    EM_PREPARO,    // Pedido sendo preparado
    FINALIZADO,    // Pedido entregue
    CANCELADO      // Pedido cancelado
} StatusPedido;

/*
    Estrutura que representa um pedido da hamburgueria.
*/
typedef struct Pedido {
    int id;                     // Identificador único do pedido
    char cliente[50];           // Nome do cliente
    char hamburguer[50];        // Tipo de hambúrguer escolhido
    int quantidade;             // Quantidade solicitada
    StatusPedido status;        // Status atual do pedido
} Pedido;

/*
    Nó da fila encadeada de pedidos em espera.
*/
typedef struct NoFila {
    Pedido *pedido;             // Ponteiro para o pedido
    struct NoFila *prox;        // Ponteiro para o próximo nó
} NoFila;

/*
    Estrutura da fila de pedidos.
*/
typedef struct {
    NoFila *inicio;             // Primeiro pedido da fila
    NoFila *fim;                // Último pedido da fila
} FilaPedidos;

/*
    Nó da pilha que armazena o histórico de pedidos.
*/
typedef struct NoHistorico {
    Pedido *pedido;             // Ponteiro para o pedido finalizado ou cancelado
    struct NoHistorico *prox;   // Próximo nó da pilha
} NoHistorico;

/* === Protótipos das funções === */

// Pedido
Pedido* criarPedido(int id, char *cliente, char *hamburguer, int quantidade);
void liberarPedido(Pedido *p);

// Fila
void inicializarFila(FilaPedidos *fila);
int filaVazia(FilaPedidos *fila);
void enfileirar(FilaPedidos *fila, Pedido *p);
Pedido* desenfileirar(FilaPedidos *fila);
Pedido* desenfileirarUltimo(FilaPedidos *fila);
void listarFila(FilaPedidos *fila);

// Histórico
void empilharHistorico(NoHistorico **topo, Pedido *p);
void listarHistorico(NoHistorico *topo);
void liberarHistorico(NoHistorico *topo);

// Utilidades
int existePedidoEmPreparo(Pedido *p);
const char* statusParaTexto(StatusPedido status);

#endif
