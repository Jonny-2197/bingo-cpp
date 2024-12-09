#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

const int BINGO_MIN = 1;
const int BINGO_MAX = 75;
const int ROWS = 5;
const int COLS = 5;

// Função para verificar se um número já está no cartão
bool numeroJaExiste(int cartao[ROWS][COLS], int numero) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (cartao[i][j] == numero) {
                return true;
            }
        }
    }
    return false;
}

// Função para gerar um cartão de Bingo
void gerarCartao(int cartao[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == 2 && j == 2) { // Espaço "FREE"
                cartao[i][j] = 0;
            } else {
                int numero;
                do {
                    numero = BINGO_MIN + rand() % (BINGO_MAX - BINGO_MIN + 1);
                } while (numeroJaExiste(cartao, numero));
                cartao[i][j] = numero;
            }
        }
    }
}

// Função para exibir um cartão de Bingo
void exibirCartao(int cartao[ROWS][COLS]) {
    std::cout << " B   I   N   G   O\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (cartao[i][j] == 0) {
                std::cout << "  X ";
            } else {
                std::cout << std::setw(3) << cartao[i][j] << " ";
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Função para verificar se um número já foi sorteado
bool numeroJaSorteado(int numerosSorteados[], int totalSorteados, int numero) {
    for (int i = 0; i < totalSorteados; ++i) {
        if (numerosSorteados[i] == numero) {
            return true;
        }
    }
    return false;
}

// Função para verificar se o cartão tem Bingo
bool verificarBingo(int cartao[ROWS][COLS], int numerosSorteados[], int totalSorteados) {
    // Verificar linhas
    for (int i = 0; i < ROWS; ++i) {
        bool linhaCompleta = true;
        for (int j = 0; j < COLS; ++j) {
            if (cartao[i][j] != 0 && !numeroJaSorteado(numerosSorteados, totalSorteados, cartao[i][j])) {
                linhaCompleta = false;
                break;
            }
        }
        if (linhaCompleta) return true;
    }

    // Verificar colunas
    for (int j = 0; j < COLS; ++j) {
        bool colunaCompleta = true;
        for (int i = 0; i < ROWS; ++i) {
            if (cartao[i][j] != 0 && !numeroJaSorteado(numerosSorteados, totalSorteados, cartao[i][j])) {
                colunaCompleta = false;
                break;
            }
        }
        if (colunaCompleta) return true;
    }

    // Verificar diagonais
    bool diagonalPrincipal = true, diagonalSecundaria = true;
    for (int i = 0; i < ROWS; ++i) {
        if (cartao[i][i] != 0 && !numeroJaSorteado(numerosSorteados, totalSorteados, cartao[i][i])) {
            diagonalPrincipal = false;
        }
        if (cartao[i][ROWS - 1 - i] != 0 && !numeroJaSorteado(numerosSorteados, totalSorteados, cartao[i][ROWS - 1 - i])) {
            diagonalSecundaria = false;
        }
    }

    return diagonalPrincipal || diagonalSecundaria;
}

int main() {
    srand(time(0));
    int quantidadeCartoes;

    std::cout << "Quantos cartoes de Bingo voce deseja gerar? ";
    std::cin >> quantidadeCartoes;

    int cartoes[quantidadeCartoes][ROWS][COLS];
    for (int i = 0; i < quantidadeCartoes; ++i) {
        gerarCartao(cartoes[i]);
        std::cout << "\nCartao #" << i + 1 << ":\n";
        exibirCartao(cartoes[i]);
    }

    int numerosSorteados[BINGO_MAX] = {0};
    int totalSorteados = 0;
    bool bingo = false;

    std::cout << "\nIniciando o sorteio dos numeros...\n";

    while (!bingo) {
        int numero;
        do {
            numero = BINGO_MIN + rand() % (BINGO_MAX - BINGO_MIN + 1);
        } while (numeroJaSorteado(numerosSorteados, totalSorteados, numero));
        numerosSorteados[totalSorteados++] = numero;

        std::cout << "Numero sorteado: " << numero << '\n';

        for (int i = 0; i < quantidadeCartoes; ++i) {
            if (verificarBingo(cartoes[i], numerosSorteados, totalSorteados)) {
                std::cout << "\nBINGO! O cartao #" << i + 1 << " venceu!\n";
                exibirCartao(cartoes[i]);
                bingo = true;
                break;
            }
        }

        if (totalSorteados == BINGO_MAX) {
            std::cout << "Todos os numeros foram sorteados e nenhum Bingo foi encontrado.\n";
            break;
        }
    }

    return 0;
}
