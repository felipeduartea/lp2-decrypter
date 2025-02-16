#ifndef PASSWORD_CRACKER_H
#define PASSWORD_CRACKER_H

#include <cstdio>

void gerarSenha(char *senha, int posicao, const char *senhaEncriptada, FILE *output);
void quebrarSenha(const char *inputPath, const char *outputPath);

#endif