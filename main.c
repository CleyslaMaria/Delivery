#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"


int main() {
    // Estruturas principais do sistema
    FilaPedidos fila;
    NoHistorico *historico = NULL;
    Pedido *pedidoEmPreparo = NULL;

    int opcao;
    int id = 1; // ID inicial para os pedidos

    // Inicializa a fila de pedidos
    inicializarFila(&fila);

    // Loop principal - menu de opções
    do{
        printf("\n========== HAMBURGUERIA DELIVERY ==========\n");
        printf("1 - Adicionar pedido\n");
        printf("2 - Listar pedidos em espera\n");
        printf("3 - Preparar proximo pedido\n");
        printf("4 - Finalizar entrega do pedido\n");
        printf("5 - Cancelar ultimo pedido\n");
        printf("6 - Mostrar historico\n");
        printf("7 - Sair\n");
        printf("==========================================\n"); 
        printf("Escolha uma opcao:");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

    
        if (opcao == 1){
        // Adiciona um pedido à fila
            char cliente[50];
            char hamburguer[50];
            int quantidade;
            int escolha;

            printf("Digite o nome do cliente:");
            fgets(cliente, 50, stdin);
            cliente[strcspn(cliente, "\n")] = 0; 

            printf("===== CARDAPIO =====\n");
            printf("1 - Tradicional\n");
            printf("2 - X-bacon\n");
            printf("3 - X-Tudo\n");
            printf("4 - Egg Burguer\n");
            printf("5 - Big duplo\n"); 
            printf("===================\n");
            printf("Escolha o tipo de hamburguer:");
            scanf("%d", &escolha);
            getchar(); // Limpa o buffer

            switch (escolha) {
                case 1:
                    strcpy(hamburguer, "Tradicional");
                    break;
                case 2:
                    strcpy(hamburguer, "X-bacon");
                    break;
                case 3:
                    strcpy(hamburguer, "X-Tudo");
                    break;
                case 4:
                    strcpy(hamburguer, "Egg Burguer");
                    break;
                case 5:
                    strcpy(hamburguer, "Big duplo");
                    break;
                default:
                    printf("Opcao invalida. Definindo como Tradicional.\n");
                    strcpy(hamburguer, "Tradicional");
            }

            printf("Digite a quantidade:");
            scanf("%d", &quantidade);
            getchar(); // Limpa o buffer
            
            Pedido *novo = criarPedido(id++, cliente, hamburguer, quantidade);
            id++;
            enfileirar(&fila, novo);
            /*        
             - Criar o pedido usando malloc (criarPedido)
            - Definir status como EM_ESPERA
            - Inserir o pedido no final da fila
            - Armazenar referência para possível cancelamento
            */

            printf("Pedido adicionado: %s - %s x%d\n", cliente, hamburguer, quantidade);
        }
        else if (opcao == 2){
            printf("Pedidos em espera:\n)");
            // Lista pedidos em espera
            /* - Percorrer a fila e exibe os pedidos em espera
               - mostrar o número do pedido, nome do cliente, tipo de hambúrguer e quantidade
               - se a fila estiver vazia, informar que não há pedidos em espera
            */  
            listarFila(&fila);

        }
        else if (opcao == 3){
            // Preparar o próximo pedido
            /*
                - Verificar se já existe um pedido em preparo
                - Se existir, informar que é necessário finalizar antes
                - Verificar se há pedidos na fila
                - Se houver:
                    - Remover o primeiro pedido da fila
                    - Definir status como "Em preparo"
                    - Armazenar em uma estrutura separada
            */
           printf("Pedido em preparo...\n");  
        }
        else if (opcao == 4){
            //Finaliza a entrega do pedido
            /*
                - Verificar se existe pedido em preparo
                - Se existir:
                    - Alterar status para "Finalizado"
                    - Mover pedido para o histórico
                    - Liberar estrutura de pedido em preparo
                - Se não existir, informar que não há pedido em preparo
            */
           lliberarPedido(pedidoEmPreparo);
           printf("Entrega do pedido finalizado!\n");
        }
        else if (opcao == 5){
            // Cancelar último pedido
            /*    
                - Verificar se há pedidos na fila
                - Remover o último pedido inserido 
                - Liberar memória do pedido cancelado
                - Informar cancelamento ao usuário
            */
            liberarPedido(pedidoCancelado);
            printf("Ultimo pedido cancelado!\n");
        }
        else if (opcao == 6){
            // Mostrar histórico
            printf("===== Historico de pedidos finalizados ======\n");
            /*
                - Listar todos os pedidos finalizados
                - Mostrar cliente, hambúrguer e status
                - Caso não haja histórico, informar
            */
           liberarHistorico(historico);
        }
        else if (opcao == 7){
            printf("Saindo do programa.\n");
        }
        else{
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 7);

    /*
        FINALIZAÇÃO DO PROGRAMA
        - Liberar toda memória alocada (fila, histórico, pedido em preparo)
        - free() em todas as estruturas
    */

    liberarHistorico(historico);
    return 0;
}