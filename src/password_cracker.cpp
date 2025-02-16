/**
 * Sistema de Quebra de Senhas
 *
 * Este arquivo contém as funções principais para realizar
 * um ataque de força bruta em senhas criptografadas.
 */

#include "password_cracker.h"
#include "constants.h"
#include "encrypt.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Função Recursiva de Geração de Senhas
 *
 * Gera todas as combinações possíveis de senhas de 4 letras
 * maiúsculas (A-Z) e testa cada uma contra a senha criptografada.
 *
 * @param senha - Array onde a senha atual está sendo construída
 * @param posicao - Posição atual sendo preenchida (0 a 3)
 * @param senhaEncriptada - Senha criptografada que estamos tentando quebrar
 * @param output - Arquivo onde as senhas descobertas serão salvas
 */
void gerarSenha(char *senha, int posicao, const char *senhaEncriptada, FILE *output)
{
    const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Caso base: senha completa
    if (posicao == TAMANHO_SENHA)
    {
        // Tenta criptografar a senha gerada
        char *resultado = encrypt(senha);
        if (resultado != NULL)
        {
            // Se a criptografia bater com a senha que procuramos, salvamos
            if (strcmp(resultado, senhaEncriptada) == 0)
            {
                fprintf(output, "%s\n", senha);
                fflush(output);
            }
            free(resultado);
        }
        return;
    }

    // Testa todas as letras possíveis na posição atual
    for (int i = 0; i < NUM_LETRAS; i++)
    {
        senha[posicao] = letras[i];
        gerarSenha(senha, posicao + 1, senhaEncriptada, output);
    }
}

/**
 * Função Principal de Quebra de Senha
 *
 * Processa um arquivo de senhas criptografadas e tenta
 * descobrir as senhas originais através de força bruta.
 *
 * @param inputPath - Caminho do arquivo com as senhas criptografadas
 * @param outputPath - Caminho onde serão salvas as senhas descobertas
 */
void quebrarSenha(const char *inputPath, const char *outputPath)
{
    // Abre arquivo de entrada
    FILE *input = fopen(inputPath, "r");
    if (!input)
    {
        perror("Erro ao abrir arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    // Abre arquivo de saída
    FILE *output = fopen(outputPath, "w");
    if (!output)
    {
        perror("Erro ao criar arquivo de saída");
        fclose(input);
        exit(EXIT_FAILURE);
    }

    char senhaEncriptada[TAMANHO_SENHA + 1];
    char tentativaSenha[TAMANHO_SENHA + 1] = {0};

    // Informa início do processo
    printf("Processo PID %d: Quebrando senhas de %s\n", getpid(), inputPath);

    // Processa cada senha do arquivo
    while (fscanf(input, "%s", senhaEncriptada) == 1)
    {
        gerarSenha(tentativaSenha, 0, senhaEncriptada, output);
    }

    // Informa conclusão do processo
    printf("Processo PID %d: Senhas quebradas salvas em %s\n", getpid(), outputPath);

    fclose(input);
    fclose(output);
}