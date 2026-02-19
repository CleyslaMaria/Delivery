# Hamburgueria Delivery - Estruturas de Dados em C
Turma 01 - Estruturas de Dados 

#### Equipe
* Cesai Marinho de Carvalho
* Cleysla Maria Santos Ferreira
* Samyr Teles Sales Silva

### Tema escolhido
O tema escolhido para este projeto foi um sistema de Delivery de Hamburgueria.

---

## Objetivo do sistema
O objetivo principal deste sistema é gerenciar o fluxo de uma hamburgueria delivery de forma organizada e eficiente. O software resolve problemas comuns de prioridade de atendimento, garantindo que "quem pede primeiro, recebe primeiro", além de manter um registro detalhado de todas as transações, incluindo vendas concluídas e cancelamentos.

## Funcionalidades
O software implementa um fluxo funcional completo através de um menu interativo no terminal:
- Cadastro e Inserção: Registro de novos pedidos com ID único, nome do cliente, tipo de hambúrguer e quantidade.
- Gerenciamento de Fila: Controle rigoroso da ordem de pedidos em espera (FIFO).
- Processamento de Preparo: Sistema que garante que apenas um pedido seja preparado por vez, impedindo a sobreposição de tarefas na cozinha.
- Cancelamento Dinâmico: Função especial para remover e cancelar o último pedido inserido na fila.
- Histórico LIFO: Armazenamento de pedidos finalizados e cancelados em uma pilha para consulta posterior.
- Encerramento Seguro: Rotina de limpeza que percorre todas as estruturas para liberar a memória alocada dinamicamente.

## Implementação das estruturas obrigatórias
Conforme os requisitos técnicos , todas as estruturas foram implementadas da seguinte maneira:
- Struct: Utilizada para modelar a entidade Pedido e os nós das estruturas encadeadas (NoFila e NoHistorico).
- Array (Vetor): Aplicado no armazenamento estático dos nomes de clientes e tipos de hambúrgueres dentro da struct de pedidos.
- Ponteiros e Alocação Dinâmica: Uso obrigatório de malloc e free para criar e destruir pedidos e nós durante a execução, garantindo flexibilidade de memória.
- Lista Encadeada: Base para a construção da fila e da pilha, permitindo a inserção e remoção de elementos de forma dinâmica.
- Fila (Queue - FIFO): Empregada para representar a ordem de atendimento dos clientes.
- Pilha (Stack - LIFO): Utilizada para o histórico, onde o pedido concluído mais recentemente é o primeiro a ser visualizado.
- Enumerações: Uso de StatusPedido para gerenciar os estados (Em espera, Preparo, Finalizado, Cancelado) de forma semântica e segura

## Organização e modulação
A implementação do sistema foi organizada de maneira modular, dividida em três pilares principais:

### 1. Definição de tipos e interfaces (estruturas.h)
Aqui definimos todas as estruturas fundamentais do sistema e o que é um "Pedido". Cada pedido possui:
- Um identificador único (ID);
- Nome do cliente;
- Tipo de hambúrguer escolhido;
- Quantidade solicitada;
- Status do pedido.

O status é representado por um tipo enumerado (enum), com os valores: Em espera, Em preparo, Finalizado
e Cancelado. O uso de enum torna o código mais legível, organizado e menos suscetível a erros,
substituindo valores numéricos por constantes semanticamente significativas.
Além disso, foram definidas estruturas auxiliares: *NoFila*, utilizada para implementar a fila de pedidos em
espera; e *NoHistorico*, utilizada para implementar a pilha de histórico de pedidos. Essas estruturas utilizam
ponteiros para permitir a ligação dinâmica entre os dados, sem a necessidade de alocação fixa ou vetores de
tamanho limitado

### 2. Lógica de manipulação (estruturas.c)
Este arquivo funciona como o "motor" do sistema, contendo as implementações das funções responsáveis por manipular as estruturas de dados de forma dinâmica.

- Fila de Pedidos (FIFO - First In, First Out): A fila gerencia os pedidos em espera, garantindo que a ordem de chegada seja respeitada para o preparo.
  - enfileirar: Adiciona um novo pedido ao final da fila utilizando alocação dinâmica. Se a fila estiver vazia, o novo nó torna-se o início e o fim; caso contrário, ele é conectado após o atual fim.
  - desenfileirar: Remove o primeiro pedido da fila (o que está há mais tempo esperando) para que ele siga para a cozinha. A memória do nó auxiliar é liberada imediatamente após a extração do pedido.

- Cancelamento Estruturado:
  - desenfileirarUltimo: Uma função customizada que permite remover o último pedido inserido na fila.
Diferente do desenfileirar padrão, esta função percorre a lista até encontrar o penúltimo elemento para atualizar o ponteiro de fim, permitindo o cancelamento de uma desistência recente.
- Pilha de Histórico (LIFO - Last In, First Out)
Toda vez que um pedido é finalizado ou cancelado, ele é armazenado em uma pilha, onde o último evento ocorrido é o primeiro a ser visualizado no topo do histórico.
  - empilharHistorico: Insere o pedido no topo da pilha. O novo nó aponta para o antigo topo, e o ponteiro de controle da pilha passa a apontar para este novo elemento.

### 3.Controle de fluxo e interface (main.c)
O arquivo main.c atua como o orquestrador do sistema, gerenciando a lógica de negócio e a comunicação com o usuário.
- Menu Interativo: Utiliza um laço do-while que mantém o programa em execução até que a opção de saída seja selecionada.
- Tratamento de Entradas: Implementa leitura segura com fgets para strings e limpeza de buffer, evitando erros comuns de captura de dados no terminal.
- Controle de Estado: Gerencia o ponteiro pedidoEmPreparo, garantindo a regra de negócio de que apenas um pedido pode ser processado pela cozinha por vez.
- Instanciação Dinâmica: Realiza a chamada das funções de criação, passando os dados capturados para a memória dinâmica antes de inseri-los nas estruturas lineares.

## Gestão de memória e encerramento seguro
Um requisito fundamental do projeto é o uso obrigatório de malloc e free. O sistema garante a integridade da memória através de uma rotina de encerramento que limpa todas as estruturas ativas:
- Pedido em Preparo: Se houver um item sendo preparado, sua memória é liberada.
- Esvaziamento da Fila: O programa percorre a fila de espera, removendo e liberando cada nó e pedido restante.
- Limpeza do Histórico: A pilha de histórico é percorrida integralmente, garantindo que nenhum dado finalizado permaneça alocado.

## Instrução de compilação e execução
O projeto utiliza um Makefile para automatizar o processo de construção e garantir que todos os módulos (main.c e estruturas.c) sejam ligados corretamente.

🐧 No Linux / macOS (Terminal)
Os sistemas Unix já possuem suporte nativo aos comandos utilizados no Makefile
1. Compilar
```
make
```
2. Executar
```
make run
```
3. Limpar arquivos temporários
```
make clean
```
Este comando utiliza rm -f para remover os arquivos .o e o executável.

🪟 No Windows (CMD / PowerShell)
No Windows, o comando para o make pode variar dependendo da sua instalação do GCC (MinGW).
1. Compilar
```
mingw32-make
```
(Caso tenha instalado o Make separadamente, o comando pode ser apenas make).
2. Executar
```
mingw32-make run
```
3. Limpar arquivos temporários
```
make clean
```
Nota: No Windows, recomenda-se o uso do terminal Git Bash para compatibilidade total com o comando rm do Makefile.

### Requisitos Técnicos
- Compilador: GCC (GNU Compiler Collection).
- Flags de Compilação: O projeto utiliza -Wall -Wextra -g para garantir que todos os avisos sejam exibidos e permitir a depuração do código.
- Target: O nome do executável gerado é hamburgueria.
