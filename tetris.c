
// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
// #include <stdio.h>
//
// // Desafio Tetris Stack
// // Tema 3 - Integração de Fila e Pilha
// // Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// // Use as instruções de cada nível para desenvolver o desafio.
// #define MAX 5  // tamanho fixo da fila
//
// // Struct que representa uma peça
// typedef struct {
//     char nome; // tipo da peça ('I', 'O', 'T', 'L')
//     int id;    // identificador único
// } Peca;
//
// // Fila circular
// typedef struct {
//     Peca itens[MAX];
//     int frente;
//     int tras;
//     int tamanho;
// } Fila;
//
// // Inicializa a fila
// void inicializarFila(Fila *f) {
//     f->frente = 0;
//     f->tras = -1;
//     f->tamanho = 0;
// }
//
// // Verifica se está cheia
// int cheia(Fila *f) {
//     return f->tamanho == MAX;
// }
//
// // Verifica se está vazia
// int vazia(Fila *f) {
//     return f->tamanho == 0;
// }
//
// // Gera uma peça automaticamente
// Peca gerarPeca(int id) {
//     char tipos[] = {'I', 'O', 'T', 'L'};
//     Peca p;
//     p.nome = tipos[rand() % 4]; // sorteia tipo
//     p.id = id;
//     return p;
// }
//
// // Insere peça no final (enqueue)
// void enqueue(Fila *f, Peca p) {
//     if (cheia(f)) {
//         printf("Fila cheia! Não é possível inserir.\n");
//         return;
//     }
//     f->tras = (f->tras + 1) % MAX;
//     f->itens[f->tras] = p;
//     f->tamanho++;
//     printf("Peça [%c %d] inserida!\n", p.nome, p.id);
// }
//
// // Remove peça da frente (dequeue)
// void dequeue(Fila *f) {
//     if (vazia(f)) {
//         printf("Fila vazia! Não há peça para jogar.\n");
//         return;
//     }
//     Peca p = f->itens[f->frente];
//     f->frente = (f->frente + 1) % MAX;
//     f->tamanho--;
//     printf("Peça [%c %d] jogada!\n", p.nome, p.id);
// }
//
// // Exibe estado atual da fila
// void exibirFila(Fila *f) {
//     printf("\nFila de peças:\n");
//     if (vazia(f)) {
//         printf("Fila vazia.\n");
//         return;
//     }
//     int i = f->frente;
//     for (int count = 0; count < f->tamanho; count++) {
//         Peca p = f->itens[i];
//         printf("[%c %d] ", p.nome, p.id);
//         i = (i + 1) % MAX;
//     }
//     printf("\n");
// }
//
// // =====================
// // Programa principal
// // =====================
// int main() {
//
//     // 🧩 Nível Novato: Fila de Peças Futuras
//     //
//     // - Crie uma struct Peca com os campos: tipo (char) e id (int).
//     // - Implemente uma fila circular com capacidade para 5 peças.
//     // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
//     // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
//     // - Exiba a fila após cada ação com uma função mostrarFila().
//     // - Use um menu com opções como:
//     //      1 - Jogar peça (remover da frente)
//     //      0 - Sair
//     // - A cada remoção, insira uma nova peça ao final da fila.
//     Fila fila;
//     inicializarFila(&fila);
//     srand(time(NULL));
//
//     // inicializa com 5 peças
//     for (int i = 0; i < MAX; i++) {
//         enqueue(&fila, gerarPeca(i));
//     }
//
//     int opcao, idCounter = MAX;
//
//     do {
//         exibirFila(&fila);
//         printf("\nOpções:\n");
//         printf("1 - Jogar peça (dequeue)\n");
//         printf("2 - Inserir nova peça (enqueue)\n");
//         printf("0 - Sair\n");
//         printf("Escolha: ");
//         scanf("%d", &opcao);
//
//         switch(opcao) {
//             case 1:
//                 dequeue(&fila);
//                 break;
//             case 2:
//                 enqueue(&fila, gerarPeca(idCounter++));
//                 break;
//             case 0:
//                 printf("Saindo...\n");
//                 break;
//             default:
//                 printf("Opção inválida!\n");
//         }
//     } while(opcao != 0);
// }


    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // capacidade fixa da fila
#define MAX_PILHA 3  // capacidade fixa da pilha

// Struct que representa uma peça
typedef struct {
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// Fila circular
typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Pilha linear
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// =====================
// Funções utilitárias
// =====================

// Inicializa fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Inicializa pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Verifica se fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == MAX_FILA;
}

// Verifica se fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Verifica se pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

// Verifica se pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Gera peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Enfileira peça
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

// Desenfileira peça
Peca dequeue(Fila *f) {
    Peca p = {'-', -1};
    if (filaVazia(f)) return p;
    p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return p;
}

// Empilha peça
void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível reservar.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = x;
    printf("Peça [%c %d] reservada!\n", x.nome, x.id);
}

// Desempilha peça
Peca pop(Pilha *p) {
    Peca x = {'-', -1};
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Não há peça reservada.\n");
        return x;
    }
    x = p->itens[p->topo];
    p->topo--;
    printf("Peça [%c %d] usada da reserva!\n", x.nome, x.id);
    return x;
}

// Exibir estado atual
void exibirEstado(Fila *f, Pilha *p) {
    printf("\n==== Estado Atual ====\n");
    printf("Fila de peças: ");
    if (filaVazia(f)) printf("vazia");
    else {
        int i = f->frente;
        for (int count = 0; count < f->tamanho; count++) {
            Peca x = f->itens[i];
            printf("[%c %d] ", x.nome, x.id);
            i = (i + 1) % MAX_FILA;
        }
    }
    printf("\nPilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) printf("vazia");
    else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}

// =====================
// Programa principal
// =====================
int main() {
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    srand(time(NULL));

    // inicializa fila com 5 peças
    int idCounter = 0;
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(idCounter++));
    }

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("Peça [%c %d] jogada!\n", jogada.nome, jogada.id);
                    enqueue(&fila, gerarPeca(idCounter++)); // mantém fila cheia
                } else {
                    printf("Fila vazia!\n");
                }
                break;
            }
            case 2: {
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    enqueue(&fila, gerarPeca(idCounter++)); // mantém fila cheia
                } else {
                    printf("Não foi possível reservar.\n");
                }
                break;
            }
            case 3: {
                pop(&pilha); // usa peça reservada
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


