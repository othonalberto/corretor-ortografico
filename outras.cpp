#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

#include "trie.hpp"

using namespace std;

/*
 * Funcao que concentra as regras para um sugestão ser boa ou nao
 */

/*vector<string> boasSugestoes(string original, vector<string> sugestoes) {
    int erro,
        i,
        j,
        qtdIgual = 0,
        qtdDentro = 0,
        idxMenor = 0;

    vector<int> pontuacoes;
    vector<string> sugestoesAceitas;

    string menor,
           maior;

    if (original.empty() || sugestao.empty()) return sugestoesAceitas;

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

     * Este loop conta quantas letras da sugestao estão presente na original
     * Mesmo que fora de ordem
     * Exemplo:
     * Entrada = caasa; Sugestao = cara
     * Saída = 3
    for (i = 0; i < sugestao.size(); i++) {
        qtdDentro = 0;
        for (j = 0; j < original.size(); j++) {
            if (sugestao[i] == original[j])
                qtdDentro++;
        }

        if (qtdDentro > 0)
            qtdIgual++;
    }

     * Este loop comparada INDEX POR INDEX se as letras são iguais.
    qtdDentro = 0; // reutilizando variavel que nao seria mais usada
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
    return sugestoesAceitas;
}
*/

vector<string> boasSugestoes(string original, vector<string> sugestoes) {
/*
    vector<unsigned int> pontuacoes;
    vector<string> aceitas;

    unsigned int pontos,
                 // falta definir uma ponutacao mínima para que a sugestão seja boa
                 // não simplesmente a melhor delas
                 pontuacaoMaxima = 0;
    const unsigned int tamanhoEntrada = sugestoes.size();
    
    int i = 0;

    for (i = 0; i < tamanhoEntrada; i++) {
        // aqui dentro serao as pontuacoes
        // pontos = 
        //
        pontuacoes[i] = pontos;
        pontos = 0;
    }

    for (i = 0; i < tamanhoEntrada; i++) {
        if (pontuacoes[i] >= pontuacaoMaxima)
            aceitas.push_back(sugestoes[i]);
    }

    return aceitas;
    */

    return vector<string>();
}
