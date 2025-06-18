#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

int main() {
    // === Declaração do tabuleiro ===
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // === Inicializa todas as posições com 0 (água) ===
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // === Declaração dos navios (valores irrelevantes, só usados para tamanho) ===
    int navioHorizontal[TAMANHO_NAVIO] = {3, 3, 3};
    int navioVertical[TAMANHO_NAVIO] = {3, 3, 3};

    // === Coordenadas iniciais (definidas no código) ===
    int linhaHorizontal = 2;
    int colunaHorizontal = 4;

    int linhaVertical = 5;
    int colunaVertical = 7;

    // === Verificação de limites e sobreposição ===
    if (colunaHorizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        linhaVertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {

        // === Posiciona o navio horizontal (linha fixa, coluna varia) ===
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaHorizontal][colunaHorizontal + i] = VALOR_NAVIO;
        }

        // === Posiciona o navio vertical (coluna fixa, linha varia) ===
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Verifica se a posição já está ocupada (evita sobreposição)
            if (tabuleiro[linhaVertical + i][colunaVertical] == VALOR_AGUA) {
                tabuleiro[linhaVertical + i][colunaVertical] = VALOR_NAVIO;
            } else {
                printf("Erro: sobreposição de navios na posição [%d][%d]\n", linhaVertical + i, colunaVertical);
                return 1;
            }
        }

        // === Exibe o tabuleiro ===
        printf("=== TABULEIRO BATALHA NAVAL ===\n\n");
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
                printf("%d ", tabuleiro[i][j]);
            }
            printf("\n");
        }

    } else {
        printf("Erro: coordenadas inválidas (navios fora dos limites do tabuleiro).\n");
    }

    return 0;
}