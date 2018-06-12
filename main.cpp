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

    string nameFile = "listaMinusculas.txt",
           linhaAux,
           input;

    int erro,
        i,
        qtdSugestoes = 0,
        qtd;

    vector<string> todasSugestoes,
                   sugestoesFinais;

    vector<const string*> correcoes;

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
        input.append(linha);

        std::transform(linhaAux.begin(), linhaAux.end(), linhaAux.begin(), ::tolower);

        if (arvore.has(linhaAux)) 
            cout << input << endl;
        else {
            qtdSugestoes = 0;
            auto original = linhaAux;
            erro = arvore.ondeErro(linhaAux);
            //if (erro > 0) erro--;
            //erro--;

            while (qtdSugestoes == 0 && erro >= 0) {
                correcoes = arvore.possiveisCandidatos(original, erro);
                qtd = correcoes.size();
                cout << qtd << endl;
                getchar();

                for (i = 0; i < qtd; i++) {
                    todasSugestoes.push_back((*correcoes[i]));
                }

                sugestoesFinais = boasSugestoes(original, todasSugestoes);
                qtdSugestoes = sugestoesFinais.size();
                
                erro--;
                
                todasSugestoes.clear();
                correcoes.clear();
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
        input.clear();
        todasSugestoes.clear();
    }

	dicIn.close();

	return 0;
}
