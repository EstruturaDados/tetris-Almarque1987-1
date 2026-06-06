#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // tamanho fixo da fila

// Struct que representa uma peça
typedef struct {
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// Fila circular
typedef struct {
    Peca itens[MAX];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Verifica se está cheia
int cheia(Fila *f) {
    return f->tamanho == MAX;
}

// Verifica se está vazia
int vazia(Fila *f) {
    return f->tamanho == 0;
}

// Gera uma peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4]; // sorteia tipo
    p.id = id;
    return p;
}

// Insere peça no final (enqueue)
void enqueue(Fila *f, Peca p) {
    if (cheia(f)) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    f->tras = (f->tras + 1) % MAX;
    f->itens[f->tras] = p;
    f->tamanho++;
    printf("Peça [%c %d] inserida!\n", p.nome, p.id);
}

// Remove peça da frente (dequeue)
void dequeue(Fila *f) {
    if (vazia(f)) {
        printf("Fila vazia! Não há peça para jogar.\n");
        return;
    }
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;
    printf("Peça [%c %d] jogada!\n", p.nome, p.id);
}

// Exibe estado atual da fila
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");
    if (vazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    int i = f->frente;
    for (int count = 0; count < f->tamanho; count++) {
        Peca p = f->itens[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// =====================
// Programa principal
// =====================
int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    // inicializa com 5 peças
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(i));
    }

    int opcao, idCounter = MAX;

    do {
        exibirFila(&fila);
        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(idCounter++));
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}
