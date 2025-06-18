#include <stdio.h>
#include <stdlib.h> // Para a função abs()

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5 // Novo valor para áreas afetadas por habilidades

// Tamanho das matrizes de habilidade (devem ser ímpares para ter um centro)
#define TAMANHO_HABILIDADE_CONE 7
#define TAMANHO_HABILIDADE_CRUZ 5
#define TAMANHO_HABILIDADE_OCTAEDRO 5

// --- Funções Auxiliares (mantidas dos níveis anteriores) ---

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }
}

// Função para exibir o tabuleiro (modificada para incluir VALOR_HABILIDADE)
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
            // Usa caracteres diferentes para melhor visualização
            if (tabuleiro[i][j] == VALOR_AGUA) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == VALOR_NAVIO) {
                printf("N "); // Navio
            } else if (tabuleiro[i][j] == VALOR_HABILIDADE) {
                printf("X "); // Habilidade
            } else {
                printf("%d ", tabuleiro[i][j]); // Outros valores (caso haja)
            }
        }
        printf("\n");
    }
}

// Função para verificar se o posicionamento de um navio é válido (limites e sobreposição)
// Retorna 1 se for válido, 0 se for inválido
int validarPosicaoNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    // Validação de limites
    if (orientacao == 'H') { // Horizontal
        if (coluna + tamanho > TAMANHO_TABULEIRO) return 0;
    } else if (orientacao == 'V') { // Vertical
        if (linha + tamanho > TAMANHO_TABULEIRO) return 0;
    } else if (orientacao == 'D') { // Diagonal crescente (linha e coluna aumentam)
        if (linha + tamanho > TAMANHO_TABULEIRO || coluna + tamanho > TAMANHO_TABULEIRO) return 0;
    } else if (orientacao == 'A') { // Diagonal decrescente (linha aumenta, coluna diminui)
        if (linha + tamanho > TAMANHO_TABULEIRO || coluna - (tamanho - 1) < 0) return 0;
    }

    // Validação de sobreposição de navios
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
    if (!validarPosicaoNavio(tabuleiro, linha, coluna, tamanho, orientacao)) {
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

// --- Novas Funções para Habilidades Especiais ---

// Função para criar a matriz de habilidade em formato de Cone
void criarHabilidadeCone(int matrizHabilidade[TAMANHO_HABILIDADE_CONE][TAMANHO_HABILIDADE_CONE]) {
    int centro = TAMANHO_HABILIDADE_CONE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE_CONE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CONE; j++) {
            matrizHabilidade[i][j] = 0; // Inicializa com 0 (não afetado)
            // Lógica para o cone: quanto mais para baixo (i maior), mais largo o cone
            // O cone aponta para baixo, então a base está na parte inferior da matriz.
            // A largura do cone aumenta com a distância do topo (i).
            // abs(j - centro) <= i define a largura do cone para cada linha 'i'.
            if (abs(j - centro) <= i) {
                matrizHabilidade[i][j] = 1; // Posição afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de Cruz
void criarHabilidadeCruz(int matrizHabilidade[TAMANHO_HABILIDADE_CRUZ][TAMANHO_HABILIDADE_CRUZ]) {
    int centro = TAMANHO_HABILIDADE_CRUZ / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE_CRUZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CRUZ; j++) {
            matrizHabilidade[i][j] = 0; // Inicializa com 0 (não afetado)
            // Lógica para a cruz: linha ou coluna central
            if (i == centro || j == centro) {
                matrizHabilidade[i][j] = 1; // Posição afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de Octaedro (Losango)
void criarHabilidadeOctaedro(int matrizHabilidade[TAMANHO_HABILIDADE_OCTAEDRO][TAMANHO_HABILIDADE_OCTAEDRO]) {
    int centro = TAMANHO_HABILIDADE_OCTAEDRO / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE_OCTAEDRO; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_OCTAEDRO; j++) {
            matrizHabilidade[i][j] = 0; // Inicializa com 0 (não afetado)
            // Lógica para o losango: a soma das distâncias absolutas do centro (manhattan distance)
            // deve ser menor ou igual ao raio (centro).
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matrizHabilidade[i][j] = 1; // Posição afetada
            }
        }
    }
}

// Função para sobrepor a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int matrizHabilidade[][TAMANHO_HABILIDADE_CONE], // Usamos a maior dimensão para o tipo
                       int tamanhoHabilidade, int centroLinhaTab, int centroColunaTab) {

    int offset = tamanhoHabilidade / 2; // Deslocamento para centralizar a matriz de habilidade

    for (int i = 0; i < tamanhoHabilidade; i++) {
        for (int j = 0; j < tamanhoHabilidade; j++) {
            // Calcula as coordenadas reais no tabuleiro
            int tabuleiroLinha = centroLinhaTab - offset + i;
            int tabuleiroColuna = centroColunaTab - offset + j;

            // Verifica se a posição calculada está dentro dos limites do tabuleiro
            if (tabuleiroLinha >= 0 && tabuleiroLinha < TAMANHO_TABULEIRO &&
                tabuleiroColuna >= 0 && tabuleiroColuna < TAMANHO_TABULEIRO) {

                // Se a posição na matriz de habilidade for 1 (afetada), e não for um navio, marca no tabuleiro
                // Não queremos sobrescrever um navio com a marca de habilidade para fins de visualização do desafio,
                // mas sim, que a habilidade "afete" o navio sem mudar sua representação.
                // Aqui, o requisito é marcar a área afetada, então marcaremos tudo que não é navio.
                if (matrizHabilidade[i][j] == 1 && tabuleiro[tabuleiroLinha][tabuleiroColuna] != VALOR_NAVIO) {
                    tabuleiro[tabuleiroLinha][tabuleiroColuna] = VALOR_HABILIDADE;
                }
            }
        }
    }
}


int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // --- Inicialização do Tabuleiro ---
    inicializarTabuleiro(tabuleiro);

    // --- Posicionamento dos Navios (do nível anterior) ---
    posicionarNavio(tabuleiro, 2, 1, TAMANHO_NAVIO, 'H');
    posicionarNavio(tabuleiro, 5, 8, TAMANHO_NAVIO, 'V');
    posicionarNavio(tabuleiro, 1, 1, TAMANHO_NAVIO, 'D');
    posicionarNavio(tabuleiro, 6, 8, TAMANHO_NAVIO, 'A');

    // --- Criação das Matrizes de Habilidade ---
    int habilidadeCone[TAMANHO_HABILIDADE_CONE][TAMANHO_HABILIDADE_CONE];
    criarHabilidadeCone(habilidadeCone);

    int habilidadeCruz[TAMANHO_HABILIDADE_CRUZ][TAMANHO_HABILIDADE_CRUZ];
    criarHabilidadeCruz(habilidadeCruz);

    int habilidadeOctaedro[TAMANHO_HABILIDADE_OCTAEDRO][TAMANHO_HABILIDADE_OCTAEDRO];
    criarHabilidadeOctaedro(habilidadeOctaedro);

    // --- Definição dos Pontos de Origem das Habilidades no Tabuleiro ---
    // Ponto de origem do Cone (centro aproximado no tabuleiro)
    int centroConeLinha = 3;
    int centroConeColuna = 4;

    // Ponto de origem da Cruz (centro aproximado no tabuleiro)
    int centroCruzLinha = 7;
    int centroCruzColuna = 2;

    // Ponto de origem do Octaedro (centro aproximado no tabuleiro)
    int centroOctaedroLinha = 4;
    int centroOctaedroColuna = 7;

    // --- Aplicação das Habilidades ao Tabuleiro ---
    printf("\nAplicando habilidade Cone em [%d][%d]...\n", centroConeLinha, centroConeColuna);
    aplicarHabilidade(tabuleiro, (int (*)[TAMANHO_HABILIDADE_CONE])habilidadeCone, TAMANHO_HABILIDADE_CONE, centroConeLinha, centroConeColuna);

    printf("Aplicando habilidade Cruz em [%d][%d]...\n", centroCruzLinha, centroCruzColuna);
    aplicarHabilidade(tabuleiro, (int (*)[TAMANHO_HABILIDADE_CRUZ])habilidadeCruz, TAMANHO_HABILIDADE_CRUZ, centroCruzLinha, centroCruzColuna);

    printf("Aplicando habilidade Octaedro em [%d][%d]...\n", centroOctaedroLinha, centroOctaedroColuna);
    aplicarHabilidade(tabuleiro, (int (*)[TAMANHO_HABILIDADE_OCTAEDRO])habilidadeOctaedro, TAMANHO_HABILIDADE_OCTAEDRO, centroOctaedroLinha, centroOctaedroColuna);

    // --- Exibição do Tabuleiro Final ---
    exibirTabuleiro(tabuleiro);

    return 0;
}