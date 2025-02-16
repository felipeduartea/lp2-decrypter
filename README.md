# Quebrador de Senhas Multi-Processo

Este é um programa em C++ que implementa um sistema de quebra de senhas criptografadas usando força bruta de forma multi-processada.

## Como Funciona

O programa recebe um diretório contendo arquivos de texto com senhas criptografadas e tenta descobrir as senhas originais através de força bruta. Para isso:

1. Cria um processo filho para cada arquivo de senha encontrado
2. Cada processo testa todas as combinações possíveis de 4 letras maiúsculas (A-Z)
3. As senhas descobertas são salvas em arquivos separados no diretório "output"
4. O programa mede e exibe o tempo total de execução

## Uso

```bash
make
./quebra_senhas <diretorio_senhas>
```

