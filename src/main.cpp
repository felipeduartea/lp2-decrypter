#include "password_cracker.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <chrono>

/**
 * Programa Principal de Quebra de Senhas
 *
 * Este programa implementa um sistema multiprocessado para quebrar
 * senhas criptografadas usando força bruta. Principais características:
 *
 * - Cria um processo filho para cada arquivo de senha
 * - Mede o tempo total de execução
 * - Gerencia a criação e finalização dos processos
 * - Organiza os arquivos de entrada e saída
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <diretorio_senhas>\n", argv[0]);
        return 1;
    }

    // Inicia contagem de tempo
    auto start_time = std::chrono::high_resolution_clock::now();

    struct timeval inicio, fim;
    gettimeofday(&inicio, nullptr);

    DIR *dir = opendir(argv[1]);
    if (!dir)
    {
        perror("Erro ao abrir diretório");
        return 1;
    }

    // Criar diretório de saída no diretório atual
    const char *outputDir = "output";

    // Tenta criar o diretório e verifica se foi bem sucedido
    if (mkdir(outputDir, 0755) != 0 && errno != EEXIST)
    {
        perror("Erro ao criar diretório de saída");
        closedir(dir);
        return 1;
    }

    // Verifica se o diretório existe e é acessível
    DIR *outdir = opendir(outputDir);
    if (outdir == NULL)
    {
        perror("Erro ao acessar diretório de saída");
        closedir(dir);
        return 1;
    }
    closedir(outdir);

    printf("Gerando processos para processar arquivos...\n");
    printf("Arquivos descriptografados serão salvos em: %s/\n", outputDir);

    struct dirent *entry;
    int processos_criados = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".txt") == NULL)
        {
            continue;
        }

        char inputPath[256];
        char outputPath[256];
        char baseName[256];
        strncpy(baseName, entry->d_name, strlen(entry->d_name) - 4);
        baseName[strlen(entry->d_name) - 4] = '\0';

        snprintf(inputPath, sizeof(inputPath), "%s/%s", argv[1], entry->d_name);
        snprintf(outputPath, sizeof(outputPath), "%s/dec_%s.txt", outputDir, baseName);

        printf("Processando arquivo: %s\n", entry->d_name);

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Erro ao criar processo");
            continue;
        }
        if (pid == 0)
        { // Processo filho
            quebrarSenha(inputPath, outputPath);
            exit(0);
        }
        processos_criados++;
    }

    closedir(dir);

    if (processos_criados == 0)
    {
        printf("Nenhum arquivo .txt encontrado em %s\n", argv[1]);
        return 1;
    }

    printf("[Aguardando término da força bruta - %d processos]\n", processos_criados);

    while (wait(nullptr) > 0)
        ;

    printf("[Fim dos processos descendentes]\n");

    gettimeofday(&fim, nullptr);
    const long tempo_ms = (fim.tv_sec - inicio.tv_sec) * 1000 +
                          (fim.tv_usec - inicio.tv_usec) / 1000;
    printf("Tempo total de execução: %ldms\n", tempo_ms);

    // Calcula e exibe o tempo total de execução
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    printf("Tempo total de execução: %lldms\n", duration.count());

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.