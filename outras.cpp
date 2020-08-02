#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

#include "trie.hpp"
#include "outras.hpp"

#define MAX_INICIAL 5
#define ERRO_MIN_ACEITO 2

using namespace std;

vector<string> boasSugestoes(string original, vector<string> sugestoes) {
    vector<unsigned int> pontuacoes;
    vector<string> aceitas;

    unsigned int pontos;
    unsigned int pontuacaoMaxima = MAX_INICIAL;

    if (original.empty() || sugestoes.empty()) return vector<string>();

    for (int i = 0; i < sugestoes.size(); i++) {
        pontos = 0;

        if (regra1(original, sugestoes[i])) pontos++;
        if (regra2(original, sugestoes[i])) pontos++;
        if (regra3(original, sugestoes[i])) pontos++;
        if (regra4(original, sugestoes[i])) pontos = pontos + 4; // tem que ter um peso alto, pois a probabilidade de ser a palavra certa é enorme
        if (regra5(sugestoes[i])) pontos++;
        if (regra6(original, sugestoes[i])) pontos++;
        
        if (pontos > pontuacaoMaxima) pontuacaoMaxima = pontos;

        
        pontuacoes.push_back(pontos);
    }

    for (int i = 0; i < sugestoes.size(); i++) {
        if (pontuacoes[i] >= pontuacaoMaxima) {
            aceitas.push_back(sugestoes[i]);
        }
    }

    return aceitas;
}

bool regra1(string original, string sugestao) {
    int erro = original.size() - sugestao.size();

    return (abs(erro) < ERRO_MIN_ACEITO);
}

bool regra2(string original, string sugestao) {
    /* Este loop conta quantas letras da sugestao estão presente na original
     * Mesmo que fora de ordem
     * Exemplo:
     * Entrada = caasa; Sugestao = cara
     * Saída = 3
     */
    unsigned int qtdIgual = 0;

    for (int i = 0; i < sugestao.size(); i++) {

        unsigned int repetido = 0;

        for (int j = 0; j < original.size(); j++) {
            if (sugestao[i] == original[j])
                repetido++;
        }

        if (repetido > 0) {
            qtdIgual++;
        }

    }

    return ((sugestao.size() - qtdIgual) < ERRO_MIN_ACEITO );
}

//Este loop comparada INDEX POR INDEX (+1 para frente) se as letras são iguais.
bool regra3(string original, string sugestao) {
    unsigned int cont = 0;
    unsigned int idxMenor;

    string menor;
    string maior;

    if (original.size() > sugestao.size()) {
        maior = original;
        menor = sugestao;
        idxMenor = sugestao.size();
    } else {
        maior = sugestao;
        menor = original;
        idxMenor = original.size();
    }

    for (int i = 0; i < idxMenor; i++) {
        if (menor[i] == maior[i]) {
            cont++;
        } else if (i < idxMenor-1 && menor[i] == maior[i+1]) {
            cont++;
        }
    }

    return ((sugestao.size() - cont) < ERRO_MIN_ACEITO);
}

// remove 2 letras repetidas em sequencia e compara
bool regra4(string original, string sugestao) {
    int i = 0;

    string palavraLimpa;

    while (i < original.size()) {
       palavraLimpa.push_back(original[i]);

       if (original[i+1] == original[i]) {
           i = i +2;
       } else {
           i++;
       }
    }

    return (palavraLimpa == sugestao);
}

// procura se tem ponto final. Em geral, nao se espera sugestao com ponto final
bool regra5(string original) {
    for (int i = 0; i < original.size(); i++) {
        if (original[i] == '.')
            return false;
    }

    return true;
}

// mesmo tamanho
bool regra6(string original, string sugestao) {
    return (original.size() == sugestao.size());
}
