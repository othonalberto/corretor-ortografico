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
    int erro,
        i,
        j,
        qtdIgual = 0,
        qtdDentro = 0,
        idxMenor = 0;

    std::string menor,
                maior;

    if (original.empty() || sugestao.empty()) return false;

    erro = original.size() - sugestao.size();
    
    if (erro > -1){
        idxMenor = sugestao.size();
        menor = sugestao;
        maior = original;
    } else {
        idxMenor = original.size();
        menor = original;
        maior = sugestao;
    }

    erro = abs(erro);

    /*
     * Este loop conta quantas letras da sugestao estão presente na original
     * Mesmo que fora de ordem
     * Exemplo:
     * Entrada = caasa; Sugestao = cara
     * Saída = 3
     */
    for (i = 0; i < sugestao.size(); i++) {
        qtdDentro = 0;
        for (j = 0; j < original.size(); j++) {
            if (sugestao[i] == original[j])
                qtdDentro++; 
        }

        if (qtdDentro > 0)
            qtdIgual++;
    }


    /*
     * Este loop comparada INDEX POR INDEX se as letras são iguais.
     */
    qtdDentro = 0; // reutilizando variavel que seria mais usada
    for (i = 0; i < idxMenor; i++) {
        if (menor[i] == maior[i])
            qtdDentro++;
        else
            if (i < idxMenor-1 && menor[i] == maior[i+1]) qtdDentro++;
    }


    if (erro < 2 &&
            (sugestao.size() - qtdIgual) < 2 &&
            (sugestao.size() - qtdDentro) < 2
            ) return true;
    else return false;
}

