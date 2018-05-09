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
    string nameFile = "pequena.txt",
    //string nameFile = "listautf8.txt",
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
    cout << "Para sair, digitar out" << endl;

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
 
        if (linhaAux == "out") {
            entrada = false;
        } else {
            if (arvore.has(linhaAux)) 
                cout << linhaAux << endl;
            else {
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
                            if (boaSugestao(original, (*correcoes[i])))
                                cout << "Sugestão: " << *correcoes[i] << endl;
                        }
                    }
                } else {
                    for (i = 0; i < qtd; i++) {
                        if (boaSugestao(original, (*correcoes[i]))) { // se só tiver um caracter a mais ou a menos em relaçao a string original
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
