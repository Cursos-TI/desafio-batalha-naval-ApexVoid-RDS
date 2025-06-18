#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("=== TABULEIRO BATALHA NAVAL ===\n\n");
    // Imprime os números das colunas para melhor visualização
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Imprime os números das linhas
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o posicionamento de um navio é válido (limites e sobreposição)
// Retorna 1 se for válido, 0 se for inválido
int validarPosicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    // Validação de limites
    if (orientacao == 'H') { // Horizontal
        if (coluna + tamanho > TAMANHO_TABULEIRO) {
            return 0; // Fora dos limites
        }
    } else if (orientacao == 'V') { // Vertical
        if (linha + tamanho > TAMANHO_TABULEIRO) {
            return 0; // Fora dos limites
        }
    } else if (orientacao == 'D') { // Diagonal crescente (linha e coluna aumentam)
        if (linha + tamanho > TAMANHO_TABULEIRO || coluna + tamanho > TAMANHO_TABULEIRO) {
            return 0; // Fora dos limites
        }
    } else if (orientacao == 'A') { // Diagonal decrescente (linha aumenta, coluna diminui)
        if (linha + tamanho > TAMANHO_TABULEIRO || coluna - tamanho < -1) { // -1 para considerar coluna 0
            return 0; // Fora dos limites
        }
    }

    // Validação de sobreposição
    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') {
            if (tabuleiro[linha][coluna + i] == VALOR_NAVIO) return 0;
        } else if (orientacao == 'V') {
            if (tabuleiro[linha + i][coluna] == VALOR_NAVIO) return 0;
        } else if (orientacao == 'D') {
            if (tabuleiro[linha + i][coluna + i] == VALOR_NAVIO) return 0;
        } else if (orientacao == 'A') {
            if (tabuleiro[linha + i][coluna - i] == VALOR_NAVIO) return 0;
        }
    }
    return 1; // Posição válida
}

// Função para posicionar um navio no tabuleiro
// Retorna 1 se o navio foi posicionado, 0 se não foi (por ser inválido)
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    if (!validarPosicao(tabuleiro, linha, coluna, tamanho, orientacao)) {
        printf("Erro: Não foi possível posicionar o navio de orientação '%c' nas coordenadas [%d][%d] (fora dos limites ou sobreposição).\n", orientacao, linha, coluna);
        return 0; // Não conseguiu posicionar
    }

    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') { // Horizontal
            tabuleiro[linha][coluna + i] = VALOR_NAVIO;
        } else if (orientacao == 'V') { // Vertical
            tabuleiro[linha + i][coluna] = VALOR_NAVIO;
        } else if (orientacao == 'D') { // Diagonal crescente
            tabuleiro[linha + i][coluna + i] = VALOR_NAVIO;
        } else if (orientacao == 'A') { // Diagonal decrescente
            tabuleiro[linha + i][coluna - i] = VALOR_NAVIO;
        }
    }
    return 1; // Navio posicionado com sucesso
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // --- Posicionamento dos navios ---
    // Navio 1: Horizontal
    posicionarNavio(tabuleiro, 2, 1, TAMANHO_NAVIO, 'H');

    // Navio 2: Vertical
    posicionarNavio(tabuleiro, 5, 8, TAMANHO_NAVIO, 'V');

    // Navio 3: Diagonal crescente (linha e coluna aumentam)
    posicionarNavio(tabuleiro, 1, 1, TAMANHO_NAVIO, 'D');

    // Navio 4: Diagonal decrescente (linha aumenta, coluna diminui)
    posicionarNavio(tabuleiro, 6, 8, TAMANHO_NAVIO, 'A');

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}