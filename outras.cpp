#include <iostream>
#include <fstream>
#include <string>

#include "trie.hpp"

#include <cassert>
#include <vector>

/*
 * Funcao que concentra as regras para um sugestão ser boa ou nao
 */
bool boaSugestao(std::string original, std::string sugestao) {
    int erro;

    if (original.empty() || sugestao.empty()) return false;

    erro = original.size() - sugestao.size();
    erro = abs(erro);

    /* próximo passo: alinhamento das strings
     * precisamos comparar caracter por caracter (O(n)) e achar um limite justo
     */
    if (erro < 2) return true;
    else return false;
}

