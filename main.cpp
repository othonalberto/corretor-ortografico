#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

#include "trie.hpp"
#include "outras.hpp"

#define TAM_LINHA 500
using namespace std;

int main (int argc, char* argv[]) {

	fstream dicIn;

    string nameFile = "listautf8.txt",
           linhaAux,
           input;

    int erro,
        i,
        qtdSugestoes = 0,
        qtd;

    unsigned int tamanhoOriginal;
                 
    vector<string> todasSugestoes,
                   sugestoesFinais;

	char* linha = (char*)malloc(sizeof(char) * TAM_LINHA);

    trie<string> arvore;

	dicIn.open(nameFile, std::fstream::in);
	if (dicIn.fail()) {
		cout << "Problema no arquivo de entrada" << endl;
        return 0;
	}

    cout << "CORRETOR ORTOGRÁFICO" << endl;

	while (!(dicIn.eof())) {
		dicIn.getline(linha, TAM_LINHA);
		linhaAux.append(linha);

        arvore.insert(linha);

        linhaAux.clear();
	}

    cout << "Pronto para uso. Para sair, CTRL+C" << endl;

    while (true) {
        cout << "";
        cin >> linha;
        linhaAux.append(linha);
        std::transform(linhaAux.begin(), linhaAux.end(), linhaAux.begin(), ::tolower);

        if (arvore.has(linhaAux)) 
            cout << linhaAux << endl;
        else {
            qtdSugestoes = 0;
            auto original = linhaAux;
            tamanhoOriginal = original.size();
            erro = arvore.ondeErro(linhaAux);
            erro--;

            while (qtdSugestoes == 0 && erro > 0) {
                auto correcoes = arvore.possiveisCandidatos(original, erro);
                qtd = correcoes.size();
                
                for (i = 0; i < qtd; i++) {
                    todasSugestoes.push_back((*correcoes[i]));
                }
                
                sugestoesFinais = boasSugestoes(original, todasSugestoes);
                qtdSugestoes = sugestoesFinais.size();
                erro--;
            }

            if (qtdSugestoes == 0) {
                // aqui entra a questão do "Wedro"
                string nova = arvore.substituicao(original);
                if (nova != string())
                    cout << "> " << nova << endl;
                else 
                    cout << "Não foi possível corrigir a palavra \"" << original << "\"" << endl;
            } else {
                while (qtdSugestoes > 0) {
                    qtdSugestoes--;
                    cout << "> " << sugestoesFinais[qtdSugestoes] << endl;
                }
            }
        }

        linhaAux.clear();
        todasSugestoes.clear();
    }

	dicIn.close();

	return 0;
}
