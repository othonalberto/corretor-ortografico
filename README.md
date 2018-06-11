# Corretor gramatical baseado em Trie.

[Implementação da Trie utilizada](https://github.com/r-lyeh-archived/trie)

(o que se encontra neste repositório é um muito pequeno, apenas para testes)

Alunos: [Leandro Chesini](https://github.com/chesini), [Lucas Paris](https://github.com/lucasrv8), [Matheus Scaketti](https://github.com/scaketti), [Pedro Botelho](https://github.com/bwpedro) e [Othon Alberto](https://github.com/othonalberto)

## Questões a resolver:

- [ ] A complexidade está ruim. Precisamos achar os gargálos e tentar
  resolve-los.
- [ ] - Processar todas as palavras duma vez
    - Retornar somente as melhores dentre elas
    - Sistema de pontuação

- [x] - No caso do "wedro" abaixo, quando chega no index 0 sem nenhuma palavra
boa, começa a trocar a primeira letra

Exemplos de entrada de devem ser melhoradas:

    - debro
    - wedro
    - tatauga
    - pwdro

## Para compilar e rodar

`` make ``

`` ./a.out ``

## Para compilar e rodar no Windows

- Instalar o MinGW (http://www.mingw.org/) [Instalar mingw32-base e mingw32-gcc-g++]
- Instalar o gnu-mcu (https://gnu-mcu-eclipse.github.io/windows-build-tools/install/) [Embora no site não seja recomendado configurar a variável de ambiente PATH no Windows, é a maneira mais fácil de deixar 'make' e 'rm' disponíveis no Prompt de Comando.]
- Alterar no arquivo Makefile a variável OUTPUT_NAME para nomeDoArquivo.exe

`` make ``

`` a.exe ``
