#include <cstdlib>
#include <cstdio>
#include "constants.h"

/**
 * Função de Criptografia
 *
 * Esta função implementa um algoritmo de criptografia que:
 * - Recebe uma string de 4 caracteres maiúsculos (A-Z)
 * - Aplica uma transformação matemática em cada caractere
 * - Usa números coprimos e deslocamentos únicos para cada posição
 *
 * A fórmula de criptografia para cada caractere é:
 * valor = ((letra - 65) * COPRIMO + DESLOCAMENTO) % 26 + 65
 */
char *encrypt(const char *str)
{
    // Verifica se a string de entrada é válida
    if (!str)
    {
        perror("Erro: String de entrada é nula");
        return nullptr;
    }

    // Aloca memória para a string resultante
    const auto str_result = static_cast<char *>(malloc(sizeof(char) * (TAMANHO_SENHA + 1)));
    if (!str_result)
    {
        perror("Erro ao alocar memória");
        return nullptr;
    }

    // Processa cada caractere da senha
    for (int i = 0; i < TAMANHO_SENHA; i++)
    {
        // Verifica se o caractere é uma letra maiúscula válida
        if (const char c = str[i]; c >= 'A' && c <= 'Z')
        {
            // Aplica a transformação matemática
            int val = c - ASCII_A;
            val = ((val * COPRIMES[i]) + SHIFTS[i]) % NUM_LETRAS;
            str_result[i] = static_cast<char>(val + ASCII_A);
        }
        else
        {
            // Libera memória e retorna erro se encontrar caractere inválido
            free(str_result);
            perror("Erro: String contém caracteres inválidos.");
            return nullptr;
        }
    }

    // Finaliza a string e retorna
    str_result[TAMANHO_SENHA] = '\0';
    return str_result;
}