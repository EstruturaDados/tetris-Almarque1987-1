#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// // Desafio Tetris Stack
// // Tema 3 - Integração de Fila e Pilha
// // Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// // Use as instruções de cada nível para desenvolver o desafio.

//      🧩 Nível Novato: Fila de Peças Futuras
//  
//    - Crie uma struct Peca com os campos: tipo (char) e id (int).
//     - Implemente uma fila circular com capacidade para 5 peças.
//     - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
//     - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
//      - Exiba a fila após cada ação com uma função mostrarFila().
//     - Use um menu com opções como:
//         1 - Jogar peça (remover da frente)
//         0 - Sair
//      - A cada remoção, insira uma nova peça ao final da fila.
//


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
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int filaCheia(Fila *f) { return f->tamanho == MAX_FILA; }
int filaVazia(Fila *f) { return f->tamanho == 0; }
int pilhaCheia(Pilha *p) { return p->topo == MAX_PILHA - 1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

Peca dequeue(Fila *f) {
    Peca p = {'-', -1};
    if (filaVazia(f)) return p;
    p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return p;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível reservar.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = x;
    printf("Peça [%c %d] reservada!\n", x.nome, x.id);
}

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

// Troca peça da frente da fila com o topo da pilha
void trocarAtual(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Não é possível trocar.\n");
        return;
    }
    Peca temp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("Troca realizada entre frente da fila e topo da pilha!\n");
}

// Troca múltipla: 3 primeiras da fila com 3 da pilha
void trocarBloco(Fila *f, Pilha *p) {
    if (f->tamanho < 3 || p->topo < 2) {
        printf("Não há peças suficientes para troca múltipla.\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idxFila = (f->frente + i) % MAX_FILA;
        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;
    }
    printf("Troca múltipla realizada!\n");
}

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

    int idCounter = 0;
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(idCounter++));
    }

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        printf("\nOpções:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("Peça [%c %d] jogada!\n", jogada.nome, jogada.id);
                    enqueue(&fila, gerarPeca(idCounter++));
                }
                break;
            }
            case 2: {
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    enqueue(&fila, gerarPeca(idCounter++));
                }
                break;
            }
            case 3: {
                pop(&pilha);
                break;
            }
            case 4: {
                trocarAtual(&fila, &pilha);
                break;
            }
            case 5: {
                trocarBloco(&fila, &pilha);
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


