#include <stdio.h>   // Biblioteca (printf, scanf)
#include <stdlib.h>  // Biblioteca (rand, srand)
#include <time.h>    // Biblioteca tempo (time)

// Tmanho máximo da fila de peças
#define MAX 5

// ---------- Estruturas ----------

// Estrutura das peças
typedef struct {
    char nome; 
    int id;    
} Peca;

// Estrutura da fila, no caso circular
typedef struct {
    Peca pecas[MAX]; 
    int inicio;
    int fim;       
    int qtd;         
} Fila;

// Controle da fila

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

// Retorna 1 ou 0 dependendo se a fila está cheia ou não
int filaCheia(Fila *f) {
    return f->qtd == MAX;
}

// Retorna 1 ou 0 dependendo se a fila está cheia ou não
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Insere uma nova peça
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n⚠️  A fila está cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    // Coloca a peça na posição 'fim', atualiza o indice e a quantidade de elementos
    f->pecas[f->fim] = p;
      f->fim = (f->fim + 1) % MAX;
    f->qtd++;
}

// Retorna a peça do início da fila
Peca dequeue(Fila *f) {
        Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("\n⚠️  A fila está vazia! Nenhuma peça para jogar.\n");
        return removida;
    }
    // Armazena a peça do início
    removida = f->pecas[f->inicio];
      f->inicio = (f->inicio + 1) % MAX;
        f->qtd--;
      return removida;
}

// Exibe todas as peças da fila
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");
    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }
    int i, pos;
    // Percorre a fila a partir do início
    for (i = 0, pos = f->inicio; i < f->qtd; i++) {
        printf("[%c %d] ", f->pecas[pos].nome, f->pecas[pos].id);
           pos = (pos + 1) % MAX;
    }
    printf("\n");
}

//Função para gerar novas peças

Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'}; 
    nova.nome = tipos[rand() % 4];       
    nova.id = id;                        
    return nova;
}

int main() {
    Fila fila;            
    inicializarFila(&fila); 
    srand(time(NULL));    

    int opcao, contadorId = 0;


    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(contadorId++));
    }

   
    do {
        exibirFila(&fila);
        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { 
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("➡️  Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                }
                break;
            }
            case 2: { 
                if (!filaCheia(&fila)) {
                    enqueue(&fila, gerarPeca(contadorId++));
                } else {
                    printf("⚠️  Fila cheia. Jogue uma peça antes!\n");
                }
                break;
            }
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0); // Repete até o usuário escolher sair

    return 0;
}
