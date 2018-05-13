#include <iostream>
#include <fstream>
#include <string>

#include "trie.hpp"
#include "outras.hpp"

#include <cassert>
#include <vector>


#define TAM_LINHA 500
using namespace std;

int main (int argc, char* argv[]){

	fstream dicIn;
    //string nameFile = "pequena.txt",
    string nameFile = "listautf8.txt",
           linhaAux,
           input;

    int erro,
        i,
        qtdEncontradas = 0;

    unsigned int qtd,
                 tamanhoOriginal;
                 
    vector<string> encontradas;

	char* linha = (char*)malloc(sizeof(char) * TAM_LINHA);

    trie<string> arvore;

	dicIn.open(nameFile, std::fstream::in);
	if(dicIn.fail()){
		cout << "Problema entrada" << endl;
	}

	nameFile.clear();
	nameFile = "lista_saida.txt";

    cout << "CORRETOR ORTOGRÁFICO" << endl;

	while( !(dicIn.eof()) ){
		dicIn.getline(linha, TAM_LINHA);
		linhaAux.append(linha);

        arvore.insert(linha);

        linhaAux.clear();
	}

    cout << "Pronto para uso. " << endl;

    while (true) {
        cout << "";
        cin >> linha;
        linhaAux.append(linha);
 
        if (arvore.has(linhaAux)) 
            cout << linhaAux << endl;
        else {
            qtdEncontradas = 0;
            auto original = linhaAux;
            tamanhoOriginal = original.size();
            erro = arvore.ondeErro(linhaAux);
            erro--;

            auto correcoes = arvore.possiveisCandidatos(original, erro);
            qtd = correcoes.size();
                
            if (qtd == 0) {
                linhaAux = original.substr(1, tamanhoOriginal); // funcao substr: copia uma string de a até b
                correcoes = arvore.complete(linhaAux);
                qtd = correcoes.size();
                if (qtd == 0) cout << "Não foi possível corrigir a palavra" << endl;
                else {
                    for (i = 0; i < qtd; i++) {
                        if (boaSugestao(original, (*correcoes[i]))) {
                            qtdEncontradas++;
                            encontradas.push_back((*correcoes[i]));
                        }
                    }
                }
                        
            } else {
                for (i = 0; i < qtd; i++) {
                    if (boaSugestao(original, (*correcoes[i]))) { // se só tiver um caracter a mais ou a menos em relaçao a string original
                        qtdEncontradas++;
                        encontradas.push_back((*correcoes[i]));
                    }
                }
            }
  

            if (qtdEncontradas == 0)
                cout << "Não foi possível corrigir a palavra" << endl;
            else {
                while (qtdEncontradas > 0) {
                    qtdEncontradas--;
                    cout << "> " << encontradas[qtdEncontradas] << endl;
                }
            }
        }

        linhaAux.clear();
        encontradas.clear();
    }

	dicIn.close();

	return 0;
}
