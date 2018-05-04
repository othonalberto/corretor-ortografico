#include <iostream>
#include <fstream>
#include <string>

#include "trie.hpp"

#include <cassert>
#include <vector>


#define TAM_LINHA 500 
using namespace std;

int main (int argc, char* argv[]){

	fstream dicIn;
    string nameFile = "pequena.txt",
    //string nameFile = "lista.txt",
           linhaAux,
           input;

    bool entrada = true;

    int erro,
        i;
        
    unsigned int qtd,
        tamanhoOriginal;

	char* linha = (char*)malloc(sizeof(char) * TAM_LINHA);

    trie<string> arvore;

	dicIn.open(nameFile, std::fstream::in);
	if(dicIn.fail()){
		cout << "Problema entrada" << endl;
	}

	nameFile.clear();
	nameFile = "lista_saida.txt";

    cout << "População da Trie iniciada." << endl;

	while( !(dicIn.eof()) ){
		dicIn.getline(linha, TAM_LINHA);
		linhaAux.append(linha);

        arvore.insert(linha);

        linhaAux.clear();
	}


    cout << "Dicionário carregado. Quantidade: " << arvore.size() << endl;

    while (entrada) {
        cout << "";
        cin >> linha;
        linhaAux.append(linha);
         
        if (linhaAux == "0") {
            entrada = false;
        } else {
            if (arvore.has(linhaAux)) cout << linhaAux << endl;
            else {
                auto original = linhaAux;
                tamanhoOriginal = original.size();
                erro = arvore.ondeErro(linhaAux);
                //erro--;
                qtd = 0;
                //auto ponteirosCandidatos = arvore.complete(linhaAux);

                cout << erro << endl;
               
                auto correcoes = arvore.possiveisCandidatos(original, erro);
                qtd = correcoes.size();
                /*do {
                    linhaAux = original.substr(0, erro);
                    cout << "Nova string: " << linhaAux << endl;
                    ponteirosCandidatos = arvore.complete(linhaAux);
                    qtd = ponteirosCandidatos.size();
                    
                    if (qtd < 1) {
                        erro--;
                    }

                } while (qtd < 1 && erro != 0); // se nao tiver nenhuma sugestao, ou a substring acabar
                */

                if (qtd == 0) {
                    linhaAux = original.substr(1, tamanhoOriginal);
                    correcoes = arvore.complete(linhaAux);
                    qtd = correcoes.size();
                    if (qtd == 0) cout << "Não foi possível corrigir a palavra" << endl;
                    else {
                        for (i = 0; i < qtd; i++) {
                            erro = abs(
                                    tamanhoOriginal - (*correcoes[i]).size());
                            if (erro < 2)
                                cout << "Sugestão: " << *correcoes[i] << endl;
                        }
                    }
                } else {
                    for (i = 0; i < qtd; i++) {
                        erro = abs(
                                tamanhoOriginal - (*correcoes[i]).size());
                        if (erro < 2) { // se só tiver um caracter a mais ou a menos em relaçao a string original
                            cout << "Sugestão: " << *correcoes[i] << endl;
                        }
                    }
                }
            }
    
        linhaAux.clear();
        
        }
    }

	dicIn.close();

	return 0;
}
