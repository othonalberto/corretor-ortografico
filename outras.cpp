#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

#include "trie.hpp"
#include "outras.hpp"

using namespace std;

vector<string> boasSugestoes(string original, vector<string> sugestoes) {
    vector<unsigned int> pontuacoes;
    vector<string> aceitas;

    unsigned int pontos,
                 // falta definir uma ponutacao mínima para que a sugestão seja boa
                 // não simplesmente a melhor delas
                 pontuacaoMaxima = 0;
    const unsigned int tamanhoEntrada = sugestoes.size();
    
    int i = 0;

    if (original.empty() || sugestoes.empty()) return vector<string>();

    for (i = 0; i < tamanhoEntrada; i++) {
        // aqui dentro serao as pontuacoes
        pontos = 0;

        if (regra1(original, sugestoes[i])) pontos++;
        if (regra2(original, sugestoes[i])) pontos++;
        if (regra3(original, sugestoes[i])) pontos++;

        if (pontos > pontuacaoMaxima) pontuacaoMaxima = pontos;

        pontuacoes.push_back(pontos);
    }

    for (i = 0; i < tamanhoEntrada; i++) {
        if (pontuacoes[i] >= pontuacaoMaxima)
            aceitas.push_back(sugestoes[i]);
    }

    return aceitas;
}

bool regra1(string original, string sugestao) {
    int erro = original.size() - sugestao.size();

    erro = abs(erro);

    if (erro < 2) return true;
    else return false;
}

bool regra2(string original, string sugestao) { 
    /* Este loop conta quantas letras da sugestao estão presente na original
     * Mesmo que fora de ordem
     * Exemplo:
     * Entrada = caasa; Sugestao = cara
     * Saída = 3
     */
    unsigned int qtdDentro = 0,
                 qtdIgual = 0;

    int i,
        j;

    for (i = 0; i < sugestao.size(); i++) {
        qtdDentro = 0;
        for (j = 0; j < original.size(); j++) {
            if (sugestao[i] == original[j])
                qtdDentro++;
        }

        if (qtdDentro > 0)
            qtdIgual++;
    }

    if ((sugestao.size() - qtdIgual) < 2 ) return true;
    else return false;
}

bool regra3(string original, string sugestao) {
    //Este loop comparada INDEX POR INDEX se as letras são iguais.
    unsigned int cont = 0,
                 idxMenor;
   
    int i;

    string menor,
           maior;
    
    if (original.size() > sugestao.size()) {
        maior = original;
        menor = sugestao;
        idxMenor = sugestao.size();
    } else {
        maior = sugestao;
        menor = original;
        idxMenor = original.size();
    }

    for (i = 0; i < idxMenor; i++) {
        if (menor[i] == maior[i])
            cont++;
        else
            if (i < idxMenor-1 && menor[i] == maior[i+1]) cont++;
    }

    if ((sugestao.size() - cont) < 2) return true;
    else return false;
}

/*
 if (erro < 2 &&
            (sugestao.size() - qtdIgual) < 2 &&
            (sugestao.size() - qtdDentro) < 2
            ) return true;
*/

